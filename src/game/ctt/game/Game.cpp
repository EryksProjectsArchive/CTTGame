//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/Game.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <math/Rect.h>

#include <core/Logger.h>
#include <core/Timer.h>

#include <os/OS.h>

#include <graphics/Window.h>
#include <graphics/Model.h>
#include <graphics/renderer/Renderer.h>
#include <graphics/renderer/RenderContext.h>
#include <graphics/Camera.h>
#include <graphics/EditorFreeCamera.h>

#include <io/fs/FileSystem.h>
#include <io/fs/stdio/StdioFileSystem.h>

#include <sound/SoundManager.h>

#include <game/scene/Scene.h>

#include <game/scene/entities/Entity.h>

#include <resources/ImageLoader.h>
#include <resources/images/bmp/BMPImageLoader.h>
#include <resources/images/png/PNGImageLoader.h>
#include <resources/images/jpeg/JPEGImageLoader.h>
#include <resources/images/dds/DDSImageLoader.h>
#include <resources/SoundLoader.h>
#include <resources/sounds/wav/WAVSoundLoader.h>
#include <resources/sounds/ogg/OGGSoundLoader.h>

#include <physics/PhysicsWorld.h>

#include <input/Input.h>

#include <game/scene/entities/types/CrossroadEntity.h>
#include <game/scene/entities/types/BoxEntity.h>
#include <game/scene/entities/types/BallEntity.h>

#include <graphics/fonts/Font.h>

#include "Game.h"
#include "environment/Environment.h"

#include <io/Config.h>

#include <core/WDynString.h>
#include <core/WString.h>

#include <core/console/Console.h>

#include <graphics/ui/UISkin.h>
#include <graphics/ui/UIManager.h>
#include <graphics/ui/controls/UIView.h>
#include <graphics/ui/controls/UIControl.h>
#include <graphics/ui/controls/UIButton.h>
#include <graphics/ui/controls/UILabel.h>

#include <core/performance/Profiler.h>

Profiler g_sceneDrawProfiler;
Profiler g_lastUpdateProfiler;
extern Profiler g_physicsUpdateProfiler;
extern Profiler g_frameProfiler;
Profiler g_uiDrawProfiler;

Game * Game::s_instance = 0;
Font *gFont = 0;

class ConsoleQuitCommand : public Console::ICommand
{
public:
	ConsoleQuitCommand() : Console::ICommand(L"quit", L"Quits game")
	{

	}

	void onExecute(const WDynString& params)
	{
		wprintf(L"Parameters: %s\n", params.get());
		Game::get()->shutdown();
	}
};

class SpawnCommand : public Console::ICommand
{
private:
	Game * m_game;
public:
	SpawnCommand(Game * game) : Console::ICommand(L"spawn", L"Spawns an entity")
	{
		m_game = game;
	}

	void onExecute(const WDynString& params)
	{
		if (params.getLength() > 0)
		{
			if (params == L"box")
			{
				m_game->spawnBox();
			}
			else 
			{
				if (m_console)
					m_console->output(Console::MessageType::Warning, L"Invalid item name");
			}
		}
		else 
		{
			if (m_console)
				m_console->output(Console::MessageType::Info, L"Type: spawn [item_name]");
		}
	}
};


Game::Game()
	: Controllable(ControllableType::Engine), m_renderer(0), m_window(0), m_scene(0), m_physicsWorld(0), m_config(0), m_console(new Console()), m_ui(0)
{
	m_console->addCommand(new ConsoleQuitCommand());
	m_console->addCommand(new SpawnCommand(this));
	m_currentPickedEntity = 0;
	m_activeMoveAxis = ActiveMoveAxis::None;
	m_rotate = false;

	s_instance = this;
}

Game::~Game()
{
	if (m_ui)
	{
		delete m_ui;
		m_ui = 0;
	}

	if (m_skin)
	{
		delete m_skin;
		m_skin = 0;
	}

	if (gFont)
	{
		delete gFont;
		gFont = 0;
	}

	if (m_scene)
	{
		delete m_scene;
		m_scene = 0;
	}

	if (m_physicsWorld)
	{
		delete m_physicsWorld;
		m_physicsWorld = 0;
	}

	if (m_renderer)
	{
		delete m_renderer;
		m_renderer = 0;
	}

	if (m_window)
	{
		delete m_window;
		m_window = 0;
	}	

	if (m_config)
	{
		File *file = FileSystem::get()->open("home/config.json", FileOpenMode::Write | FileOpenMode::Extra);
		m_config->serialize(file);
		FileSystem::get()->close(file);

		delete m_config;
		m_config = 0;
	}

	if (m_console)
	{
		delete m_console;
		m_console = 0;
	}

	File *_file = FileSystem::get()->open("home/inputBinds.json", FileOpenMode::Write | FileOpenMode::Extra);
	Input::get()->serializeBinds(_file);
	FileSystem::get()->close(_file);

	s_instance = 0;
}
Sound *sound = 0;

bool Game::init()
{
	if (!Application::init())
		return false;

	// Create config object
	m_config = new Config();

	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Setup home directory
	OS::initHomePath(GAME_NAME);

	// Setup file system
	FileSystem::get()->setHomePath(OS::getHomePath());
	FileSystem::get()->registerFileSystem(new Stdio::FileSystem());
	FileSystem::get()->setBaseDirectory(FilePath("%s../../data/", OS::getAppPath().get()));

	// setup logger
	Logger::init(FilePath("%sgame.log", OS::getHomePath().get()), false);
	File *file = FileSystem::get()->open("home/config.json", FileOpenMode::Read | FileOpenMode::Extra);
	m_config->deserialize(file);
	FileSystem::get()->close(file);

	// create image loader
	ImageLoader::get()->registerLoader(new BMP::ImageLoader());
	ImageLoader::get()->registerLoader(new PNG::ImageLoader());
	ImageLoader::get()->registerLoader(new JPEG::ImageLoader());
	ImageLoader::get()->registerLoader(new DDS::ImageLoader());

	// create sound loader
	SoundLoader::get()->registerLoader(new WAV::SoundLoader());
	SoundLoader::get()->registerLoader(new OGG::SoundLoader());

	// Create game window
	m_window = new Window();
	m_window->setup("Engine "PLATFORM_NAME" ("ARCH_NAME")", Config::get()["graphics"]["resolution"]["width"].getInteger(1280), Config::get()["graphics"]["resolution"]["height"].getInteger(720), Config::get()["graphics"]["fullscreen"].getBool(false));

	m_renderer = new Renderer();
	if (!m_renderer->setup(m_window))
	{
		Error("game", "Cannot setup renderer.");
		return false;
	}

	// Bind escape key
	Input::get()->bind(L"keyboard.escape", true, L"quit");

	File *inputFile = FileSystem::get()->open("home/inputBinds.json", FileOpenMode::Read | FileOpenMode::Extra);
	Input::get()->deserializeBinds(inputFile);
	FileSystem::get()->close(inputFile);

	// Set camera manager to use free editor cam
	CameraManager::get()->setCurrent(CAMERA_TYPE_EDITOR_FREE);

	// Create main menu
	m_skin = new UI::Skin("skin_1");
	m_ui = new UI::Manager(m_skin);

	UI::View* view = m_ui->createView("game.main_menu");

	UI::Button* button = new UI::Button("spawn_box_button", Vector2(0, 100.0f), Vector2(150.0f, 30.0f));
	view->addChild(button);

	button->setText(L"Spawn box");
	button->onPressSubscribe(this, &Game::spawnBox);

	view->addChild(button);

	button = new UI::Button("spawn_busstop_button", Vector2(0, 131.0f), Vector2(150.0f, 30.0f));
	view->addChild(button);
	button->setText(L"Spawn bus stop");
	button->onPressSubscribe(this, &Game::spawnBusStop);

	UI::Label* label = new UI::Label("spawn_items", Vector2(0, 70.f), Vector2(100.0f, 30.0f));
	view->addChild(label);

	label->setText(L"Items:");
	label->setShadow(true);
	label->setShadowOffset(Vector2(2, 2));
	label->setFont("Tahoma", 20);
	label->setAlignment(ALIGNMENT_VERTICAL_CENTER);
	label->setShadowColor(Color(0, 0, 0, 1));
	label->setTextColor(Color(1, 1, 1, 1));

	m_profilerInfo = new UI::Label("profiler_info", Vector2(1, 170.f), Vector2(500, 500.f));
	view->addChild(m_profilerInfo);
	m_profilerInfo->setText(L"Profiler info");
	m_profilerInfo->setShadow(true);
	m_profilerInfo->setFont("Tahoma", 20);
	m_profilerInfo->setTextColor(Color(1, 1, 1, 1));

	m_ui->setCurrentView("game.main_menu");

	// create game sound mgr

	if (!SoundManager::get()->setup())
	{
		Error("game", "Cannot setup SoundMgr!");
		return false;
	}

	// Setup physics
	m_physicsWorld = new PhysicsWorld();
	if (!m_physicsWorld || !m_physicsWorld->init())
	{
		Error("game", "Cannot initialize physics world!");
		return false;
	}

	// Create scene
	m_scene = new Scene();
	if (!m_scene)
	{
		Error("game", "Cannot initialize scene!");
		return false;
	}

	// setup console
	if (Config::get()["engine"]["console"].getBool(false))	
		m_console->init();

#if 0
	BoxEntity *testEntity = 0;
	for (int i = 0; i < 10; ++i)
	{
		testEntity = new BoxEntity();		
		testEntity->setPosition(Vector3(0, testEntity->getHeight() + (i * (testEntity->getHeight() + 0.5f)), 0));
		m_scene->addEntity(testEntity);
	}
#endif

	Environment::get()->setSunPosition(Vector3(30.0f, 10.0f, 0.0f));

	gFont = new Font("fonts/MSMHei-Bold.ttf", 15);

	sound = SoundManager::get()->createSound(SoundType::Effect);

	if (!sound->load("sounds/test.wav"))
	{
		return false;
	}

	sound->setPosition(Vector3(0, 1, 0));
	sound->setVolume(0.2f);
	sound->play(false);
	
	m_isInitialized = true;
	m_isRunning = true;
	return true;
}

void Game::updateWindow()
{
	if (m_window)
	{
		if (!m_window->processMessages())
		{
			m_isRunning = false;
		}
	}

	if (m_ui)
		m_ui->handleInput();
}

void Game::spawnBox()
{
	BoxEntity * box = new BoxEntity();
	box->setPosition(Vector3(0, 10, 0));
	m_scene->addEntity(box);

	if (m_console)
		m_console->output(Console::MessageType::Info, WString<128>(L"Spawned box (%d)!", box->getUID()));
}

#include "scene/entities/types/BusStopEntity.h"
void Game::spawnBusStop()
{
	Vector3 a = CameraManager::get()->getCurrent()->getPosition();
	Vector3 b = CameraManager::get()->getCurrent()->getTarget();

	Vector3 diff = glm::normalize(b - a);

	BusStopEntity * busstop = new BusStopEntity();
	busstop->setPosition(a + (diff * 3.f));
	m_scene->addEntity(busstop);

	if (m_console)
		m_console->output(Console::MessageType::Info, WString<128>(L"Spawned bus stop (%d)!", busstop->getUID()));
}

void Game::update(double deltaTime)
{
	g_lastUpdateProfiler.start();
	Camera * currentCamera = CameraManager::get()->getCurrent();

	if (currentCamera)
	{
		currentCamera->update(float(deltaTime));

		// Editor stuffs
		{		
			EditorFreeCamera * camera = CameraManager::get()->getByType<EditorFreeCamera>(CAMERA_TYPE_EDITOR_FREE);
			if (camera->isActive())
			{
				sound->setListenerPosition(camera->getPosition());
				sound->setListenerOrientation(camera->getTarget(), Vector3(0.0f, 1.0f, 0.0f));

				bool resetPosition = false;
				int32 x, y;
				if (camera->isMoving())
				{
					x = m_window->getWidth() / 2;
					y = m_window->getHeight() / 2;
				}
				else
				{
					SDL_GetMouseState(&x, &y);

					if ((m_moveObject || m_rotateObject) && m_currentPickedEntity && m_activeAxis != None)
					{
						if (x >= m_window->getWidth() - 1)
						{
							SDL_WarpMouseInWindow(m_window->_window, 0, y);
							x = 0;
							resetPosition = true;
						}
						else if (x < 1)
						{
							SDL_WarpMouseInWindow(m_window->_window, m_window->getWidth(), y);
							x = m_window->getWidth();
							resetPosition = true;
						}

						if (y >= m_window->getHeight() - 1)
						{
							SDL_WarpMouseInWindow(m_window->_window, x, 0);
							y = 0;
							resetPosition = true;
						}
						else if (y < 1)
						{
							SDL_WarpMouseInWindow(m_window->_window, x, m_window->getHeight());
							y = m_window->getHeight();
							resetPosition = true;
						}
					}
				}

				if (!m_action)
				{
					Vector3 pos = glm::unProject(glm::vec3(x, m_renderer->getViewportAsVector().w - y, 1), glm::mat4() * camera->getViewMatrix(), m_renderer->getProjectionMatrix(), m_renderer->getViewportAsVector());

					if (!camera->isMoving() && Input::get()->isMouseBtnPressed(MOUSE_BUTTON_LEFT) /*&& !m_currentPickedEntity*/)
					{
						PhysicalEntity *entity = 0;
						Vector3 res;
						if (m_physicsWorld->rayTest(camera->getPosition(), pos, &res, &entity))
						{
							if (entity)
							{
								m_currentPickedEntity = entity;
							}
						}
					}
				}

				if (Input::get()->isKeyDown(Key::SCANCODE_LSHIFT) && m_currentPickedEntity)
				{
					m_currentPickedEntity = 0;
					m_moveObject = false;
					m_rotateObject = false;
					m_action = false;
					m_activeAxis = ActiveAxis::None;
				}
				if (Input::get()->isMouseBtnPressed(MOUSE_BUTTON_LEFT) && m_currentPickedEntity && m_action)
				{
					m_activeAxis = ActiveAxis::None;
				}

				Matrix4x4 persp = glm::perspective(glm::radians(45.0f), m_window->getAspectRatio(), 0.1f, 100.0f);

				Vector3 _world = glm::unProject(
					glm::vec3(x, m_renderer->getViewportAsVector().w - y, 1),
					camera->getViewMatrix(),
					persp,
					m_renderer->getViewportAsVector());

				Vector3 world;
				if (!resetPosition)
					world = _world - m_lastMouseWorldPos;
				m_lastMouseWorldPos = _world;

				if (m_currentPickedEntity && !camera->isMoving())
				{
					if (m_moveObject && (m_activeAxis != ActiveAxis::None))
					{
						Matrix4x4 matrix = m_currentPickedEntity->getMatrix();
		
						float mp = 0.2f;
						if (Input::get()->isKeyDown(Key::SCANCODE_LCTRL)) {
							mp = 0.05f;
						}
						Vector4 world4(world.x, world.y, world.z, 1.f);
						world4 = glm::mat4_cast(Quaternion(glm::inverse(matrix))) * world4;

						Vector4 _pos(0.f, 0.f, 0.f, 1.f);
						float mp = 0.2f;
						if (Input::get()->isKeyDown(Key::SCANCODE_LCTRL))
							mp = 0.05f;

						switch (m_activeAxis)
						{
						case ActiveAxis::X:
							{
								_pos.x += world4.x * mp;
							} break;
						case ActiveAxis::Y:
							{
								_pos.y += world4.y * mp;
							} break;
						case ActiveAxis::Z:
							{
								_pos.z += world4.z * mp;
							} break;
						};

						Vector4 pos4 = matrix * _pos;

						Vector3 newPosition = Vector3(pos4.x, pos4.y, pos4.z) / pos4.w;
						m_currentPickedEntity->setPosition(newPosition);

						sound->setPosition(newPosition);
					}
				}
			}
		}
	}

	m_physicsWorld->pulse(float(deltaTime));

	Environment::get()->pulse();
	g_lastUpdateProfiler.end();
}

void Game::render()
{
	if (m_renderer)
	{
		m_renderer->preFrame();

		g_sceneDrawProfiler.start();

		// Shadows
		m_renderer->beginShadowPass();

		if (m_scene)
			m_scene->render();

		m_renderer->endShadowPass();

		// Deferred
		m_renderer->beginDeferredPass();

		if (m_scene)
			m_scene->render();

		if (m_currentPickedEntity)
		{
			Matrix4x4 modelMatrix;
			modelMatrix = glm::translate(modelMatrix, m_currentPickedEntity->getPosition());

			switch (m_activeMoveAxis)
			{
			case ActiveMoveAxis::X:
				{
					m_renderer->drawLine3D(Vector3(-100,0,0), Vector3(100, 0, 0), Color(1, 0, 0, 1), modelMatrix);
				} break;
			case ActiveMoveAxis::Y:
				{
					m_renderer->drawLine3D(Vector3(0,-100,0), Vector3(0, 100, 0), Color(0, 1, 0, 1), modelMatrix);
				} break;
			case ActiveMoveAxis::Z:
				{
					m_renderer->drawLine3D(Vector3(0, 0, -100), Vector3(0, 0, 100), Color(0, 0, 1, 1), modelMatrix);
				} break;
			default:
				{
					m_renderer->drawLine3D(Vector3(), Vector3(3, 0, 0), Color(1, 0, 0, 1), modelMatrix);
					m_renderer->drawLine3D(Vector3(), Vector3(0, 3, 0), Color(0, 1, 0, 1), modelMatrix);
					m_renderer->drawLine3D(Vector3(), Vector3(0, 0, 3), Color(0, 0, 1, 1), modelMatrix);
				} break;
			};
		}

		m_renderer->endDeferredPass();

		g_sceneDrawProfiler.end();
		g_uiDrawProfiler.start();

		if (gFont)
		{
			if (Config::get()["engine"]["fpsCounter"].getBool(false))
			{
				float fps = Timer::getFPS();
				widechar color[10] = { 0 };

				if (fps < 25.f)
				{
					wcscpy(color, L"#FF0000");
				}
				else if (fps >= 25.f && fps < 60)
				{
					wcscpy(color, L"#FF8000");
				}
				else
				{
					wcscpy(color, L"#00FF00");
				}

				gFont->render(WString<256>(L"#FFFFFFFPS: %s%.1f", color, fps), Rect(1, 1, 10, 10), Color(0.0f, 0.0f, 0.0f, 0.6f), Font::DrawFlags::NoClip | Font::DrawFlags::DisableColorCodding);
				gFont->render(WString<256>(L"#FFFFFFFPS: %s%.1f", color, fps), Rect(0, 0, 10, 10), Color(1.0f, 1.0f, 1.0f, 1.0f), Font::DrawFlags::NoClip);
			}

			/*
			glm::vec3 labelPos = glm::vec3(0, 2, 0);
			glm::vec3 pos = glm::project(labelPos, glm::mat4()* Camera::current->getViewMatrix(), m_renderer->getProjectionMatrix(), m_renderer->getViewportAsVector());
			pos.y = m_renderer->getViewportAsVector().w - pos.y;

			// dot (viewDirection, cameraToPointDirection)
			float dot = glm::dot(glm::normalize(Camera::current->getTarget() - Camera::current->getPosition()), glm::normalize(glm::vec3(0, 5, 0) - Camera::current->getPosition()));
			if (dot > 0) // Make sure if we are looking at that point.
			{
				gFont->render(L"#FF0000City #00FF00Transport #0000FFTycoon", Rect(pos.x + 1, pos.y + 1, 10, 10), Color(0.0f, 0.0f, 0.0f, 0.6f), Font::DrawFlags::NoClip | Font::DrawFlags::DisableColorCodding, Vector2(1, 1));
				gFont->render(L"#FF0000City #00FF00Transport #0000FFTycoon", Rect(pos.x, pos.y, 10, 10), Color(1.0f, 1.0f, 1.0f, 1.0f), Font::DrawFlags::NoClip, Vector2(1,1));
			}
			*/	
		}

		// Draw UI
		if (m_ui)
		{
			RenderContext context;
			m_ui->render(context);
		}

		// Draw console
		if (m_console)
		{
			m_console->render(m_renderer);
		}

		g_uiDrawProfiler.end();

		RenderStatistics stats = m_renderer->stats();
		m_profilerInfo->setText(WString<256>(L"Profiler(s):\nScene draw: %.02fms\nUI Draw: %.02fms\nPhysics update: %.02fms\nFrame: %.02fms\nLast update: %.02fms\nPhysical ticks: %d\nFPS: %.0f\nRenderer: DC: %d VC: %llu", 
			g_sceneDrawProfiler.getTime() / 1000.f, g_uiDrawProfiler.getTime() / 1000.f, g_physicsUpdateProfiler.getTime() / 1000.f, g_frameProfiler.getTime() / 1000.f, g_lastUpdateProfiler.getTime() / 1000.f, m_physicsTicks, Timer::getFPS(), stats.m_drawCalls, stats.m_verticesProcessed));

		m_renderer->postFrame();
	}
}

bool Game::onKeyEvent(Key::Type key, bool state)
{
	if (key == Key::SCANCODE_ESCAPE)	
		m_isRunning = false;	

	if (key == Key::SCANCODE_LALT)
		m_rotate = state;

	if (state)
	{
		if (key == Key::SCANCODE_X)
			m_activeMoveAxis = ActiveMoveAxis::X;
		else if (key == Key::SCANCODE_Y)
			m_activeMoveAxis = ActiveMoveAxis::Y;
		else if (key == Key::SCANCODE_Z)
			m_activeMoveAxis = ActiveMoveAxis::Z;
	}
	else if (!state && ((key == Key::SCANCODE_X) || (key == Key::SCANCODE_Y) || (key == Key::SCANCODE_Z)))
	{
		m_activeMoveAxis = ActiveMoveAxis::None;
	}
	return false;
}

bool Game::onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y)
{
	static uint64 press = 0;

	if (input()->isLocked())
		return false;

	// Shotting
	if (button == 1 && CameraManager::get()->getByType<EditorFreeCamera>(CAMERA_TYPE_EDITOR_FREE)->isMoving())
	{
		if (state)
		{
			press = OS::getMicrosecondsCount();
		}
		else
		{
			float force = (OS::getMicrosecondsCount() - press) / 10000.f;
			Vector3 a = CameraManager::get()->getCurrent()->getPosition();
			Vector3 b = CameraManager::get()->getCurrent()->getTarget();

			Vector3 diff = glm::normalize(b - a);
			Vector3 velocity = diff;
			velocity *= force * 2.f;

			BallEntity * ball = new BallEntity();
			ball->setPosition(a + diff*5.f);
			ball->setLinearVelocity(velocity);
			m_scene->addEntity(ball);
		}
	}
	return false;
}

bool Game::onMouseScroll(sint32 horizontal, sint32 vertical)
{	
	if (!m_currentPickedEntity)
		return false;

	if (m_rotate)
	{
		Quaternion rotation = m_currentPickedEntity->getRotation();

		float v = 0;
		if (vertical > 0)
			v = 1;
		else if (vertical < 0)
			v = -1;
	

		m_currentPickedEntity->setRotation(glm::rotate(rotation, v/10, Vector3(0,1,0)));
	}
	return false;
}

PhysicsWorld* Game::getPhysicsWorld()
{
	return m_physicsWorld;
}

UI::Manager* Game::getUI()
{
	return m_ui;
}

Scene* Game::getScene()
{
	return m_scene;
}

Game * Game::get()
{
	return s_instance;
}
