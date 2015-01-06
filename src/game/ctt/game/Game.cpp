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
#include <graphics/renderer/UIRenderContext.h>

#include "Game.h"
#include "environment/Environment.h"

#include <io/Config.h>

#include <core/WDynString.h>
#include <core/WString.h>

#include <core/console/Console.h>

#include <graphics/ui/UIManager.h>
#include <graphics/ui/UIView.h>
#include <graphics/ui/controls/UIControl.h>
#include <graphics/ui/controls/UIButton.h>

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
public:
	SpawnCommand() : Console::ICommand(L"spawn", L"Spawns an entity")
	{

	}

	void onExecute(const WDynString& params)
	{
		if (params.getLength() > 0)
		{
			if (params == L"box")
			{
				BoxEntity * box = new BoxEntity();
				box->setPosition(Vector3(0, 10, 0));
				Game::get()->getScene().addEntity(box);

				if (m_console)
					m_console->output(Console::MessageType::Info, WString<128>(L"Spawned box (%d)!", box->getUID()));
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
	: Controllable(ControllableType::Engine), m_renderer(0), m_window(0), m_scene(0), m_physicsWorld(0), m_config(0), m_console(new Console()), m_ui(0), m_box(0)
{
	m_console->addCommand(new ConsoleQuitCommand());
	m_console->addCommand(new SpawnCommand());

	s_instance = this;
}

Game::~Game()
{
	m_box = 0;
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

	if (m_ui)
	{
		delete m_ui;
		m_ui = 0;
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

	s_instance = 0;
}

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

	// Create main menu
	m_ui = new UI::Manager();

	UI::View* view = m_ui->createView("game.main_menu");

	UI::Button* button = new UI::Button("spawn_box_button", Vector2(100.0f, 100.0f), Vector2(200.0f, 50.0f));
	button->setText(L"Spawn box");
	button->onPressSubscribe(this, &Game::spawnBox);

	view->attach(button);

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

	// EVERYTHING FROM ENGINE IS INITIALIZED WE CAN SETUP EVERYTHING BELLOW

	/*Entity *entity = new Entity(EntityType::Dummy);	
	m_scene->addEntity(entity);

	CrossroadEntity * crossroad = new CrossroadEntity();
	m_scene->addEntity(crossroad);

	crossroad = new CrossroadEntity();
	crossroad->setPosition(Vector3(37.153f, 0, 0));
	m_scene->addEntity(crossroad);

	crossroad = new CrossroadEntity();
	crossroad->setPosition(Vector3(-37.153f, 0, 0));
	m_scene->addEntity(crossroad);

	crossroad = new CrossroadEntity();
	crossroad->setPosition(Vector3(0, 0, 37.153f));
	m_scene->addEntity(crossroad);

	crossroad = new CrossroadEntity();
	crossroad->setPosition(Vector3(0, 0, -37.153f));
	m_scene->addEntity(crossroad);
	*/
	BoxEntity *testEntity = 0;
	for (int i = 0; i < 10; ++i)
	{
		testEntity = new BoxEntity();		
		testEntity->setPosition(Vector3(0, testEntity->getHeight() + (i * (testEntity->getHeight() + 0.5f)), 0));
		m_scene->addEntity(testEntity);
	}

	/*m_box = new CrossroadEntity();
	m_box->setPosition(Vector3(0,0,0));
	m_scene->addEntity(m_box);*/

	Environment::get()->setSunPosition(Vector3(30.0f, 10.0f, 0.0f));

	gFont = new Font("fonts/MSMHei-Bold.ttf", 15);

	Sound *sound = SoundManager::get()->createSound(SoundType::Effect);

	if (!sound->load("sounds/test.wav"))
	{
		return false;
	}

	sound->setVolume(0.1f);
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
}

void Game::spawnBox()
{
	BoxEntity * box = new BoxEntity();
	box->setPosition(Vector3(0, 10, 0));
	Game::get()->getScene().addEntity(box);

	if (m_console)
		m_console->output(Console::MessageType::Info, WString<128>(L"Spawned box (%d)!", box->getUID()));
}

void Game::update(double deltaTime)
{
	if (Camera::current)
	{
		Camera::current->update(float(deltaTime));

		/*if (!((EditorFreeCamera *)Camera::current)->isMoving())
		{
			int32 x, y;
			SDL_GetMouseState(&x, &y);

			Vector3 pos = glm::unProject(glm::vec3(x, m_renderer->getViewportAsVector().w - y, 1), glm::mat4() * Camera::current->getViewMatrix(), m_renderer->getProjectionMatrix(), m_renderer->getViewportAsVector());

			Vector3 res;
			m_physicsWorld->rayTest(Camera::current->getPosition(), pos, &res);

			m_box->setPosition(res);
		}*/
	}

	m_physicsWorld->pulse(float(deltaTime));

	Environment::get()->pulse();
}

void Game::render()
{
	if (m_renderer)
	{
		m_renderer->preFrame();

		if (m_scene)
			m_scene->render();

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

			glm::vec3 labelPos = glm::vec3(0, 2, 0);
			glm::vec3 pos = glm::project(labelPos, glm::mat4()* Camera::current->getViewMatrix(), m_renderer->getProjectionMatrix(), m_renderer->getViewportAsVector());
			pos.y = m_renderer->getViewportAsVector().w - pos.y;

			// dot (viewDirection, cameraToPointDirection)
			float dot = glm::dot(glm::normalize(Camera::current->getTarget() - Camera::current->getPosition()), glm::normalize(glm::vec3(0, 5, 0) - Camera::current->getPosition()));
			if (dot > 0) // Make sure if we are looking at that point.
			{
				gFont->render(L"#FF0000City #00FF00Transport #0000FFTycoon", Rect(pos.x + 1, pos.y + 1, 10, 10), Color(0.0f, 0.0f, 0.0f, 0.6f), Font::DrawFlags::NoClip | Font::DrawFlags::DisableColorCodding, Vector2(1,1));
				gFont->render(L"#FF0000City #00FF00Transport #0000FFTycoon", Rect(pos.x, pos.y, 10, 10), Color(1.0f, 1.0f, 1.0f, 1.0f), Font::DrawFlags::NoClip, Vector2(1,1));
			}		
		}

		// Draw UI
		if (m_ui)
		{
			UIRenderContext context;
			m_ui->render(context);
		}

		// Draw console
		if (m_console)
		{
			m_console->render(m_renderer);
		}

		m_renderer->postFrame();
	}
}

void Game::onKeyEvent(Key::Type key, bool state)
{
	if (key == Key::SCANCODE_ESCAPE)	
		m_isRunning = false;	
}

void Game::onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y)
{
	static uint64 press = 0;

	if (input()->isLocked())
		return;

	// Shotting
	if (button == 1 && ((EditorFreeCamera *)Camera::current)->isMoving())
	{
		if (state)
		{
			press = OS::getMicrosecondsCount();
		}
		else
		{
			float force = (OS::getMicrosecondsCount() - press) / 10000.f;
			Vector3 a = Camera::current->getPosition();
			Vector3 b = Camera::current->getTarget();

			Vector3 diff = glm::normalize(b - a);
			Vector3 velocity = diff;
			velocity *= force * 2.f;

			BallEntity * ball = new BallEntity();
			ball->setPosition(a + diff*5.f);
			ball->setLinearVelocity(velocity);
			m_scene->addEntity(ball);
		}
	}
}

PhysicsWorld& Game::getPhysicsWorld()
{
	return *m_physicsWorld;
}

UI::Manager& Game::getUI()
{
	return *m_ui;
}

Scene& Game::getScene()
{
	return *m_scene;
}

Game * Game::get()
{
	return s_instance;
}
