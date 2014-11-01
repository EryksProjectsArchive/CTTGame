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
#include <resources/sounds/wav/WAVsoundLoader.h>
#include <resources/sounds/ogg/OGGsoundLoader.h>

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

#include <core/console/Console.h>\

#include <graphics/ui/UIManager.h>
#include <graphics/ui/UIView.h>
#include <graphics/ui/controls/UIControl.h>

Game * Game::s_instance = 0;
Font *gFont = 0;

Game::Game()
	: Controllable(ControllableType::Engine), m_renderer(0), m_window(0), m_scene(0), m_physicsWorld(0), m_config(0), m_console(new Console()), m_ui(0)
{
	s_instance = this;
}

Game::~Game()
{
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
	if (m_isInitialized)
		return false;

	// Create config object
	m_config = new Config();

	// Time
	OS::initTime();
	
	m_time = double(OS::getMicrosecondsCount() / 1000000);
	m_accumulator = 0.0;
	m_deltaTime = 1 / 60.0f;

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
	m_window->setup("Engine", Config::get()["graphics"]["resolution"]["width"].getInteger(1280), Config::get()["graphics"]["resolution"]["height"].getInteger(720), Config::get()["graphics"]["fullscreen"].getBool(false));

	m_renderer = new Renderer();
	if (!m_renderer->setup(m_window))
	{
		Error("game", "Cannot setup renderer.");
		return false;
	}

	// Create main menu
	m_ui = new UI::Manager();

	UI::View* view = m_ui->createView("game.main_menu");

	UI::Control* button = new UI::Control("button1", Vector2(0.0f, 0.0f), Vector2(100.0f, 50.0f));

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
		testEntity->setPosition(Vector3(0, i * (testEntity->getHeight()+0.5f), 0));
		m_scene->addEntity(testEntity);
	}

	m_box = new CrossroadEntity();
	m_box->setPosition(Vector3(0,0,0));
	m_scene->addEntity(m_box);

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

//#define PROFILER

bool Game::pulse()
{
	Timer::frameStart();

	// Main loop - whole magic is done here \o/
	if (m_window)
	{
		if (!m_window->processMessages())
		{
			m_isRunning = false;
		}
	}

	double time = double(OS::getMicrosecondsCount() / 1000000.f);
	double frameTime = time - m_time;
	if (frameTime > 0.25)
		frameTime = 0.25;
	m_time = time;

	m_accumulator += frameTime;

#ifdef PROFILER
	uint64 start = OS::getMicrosecondsCount();
#endif

	while (m_accumulator >= m_deltaTime)
	{
		if (Camera::current)
		{
			Camera::current->update(float(m_deltaTime));

			
			if (!((EditorFreeCamera *)Camera::current)->isMoving())
			{
				int32 x, y;
				SDL_GetMouseState(&x, &y);

				Vector3 pos = glm::unProject(glm::vec3(x, m_renderer->getViewportAsVector().w - y, 1), glm::mat4() * Camera::current->getViewMatrix(), m_renderer->getProjectionMatrix(), m_renderer->getViewportAsVector());
				m_console->output(Console::MessageType::Info, WString<64>(L"%f, %f, %f", pos.x, pos.y, pos.z));
				
				Vector3 res;
				m_physicsWorld->rayTest(Camera::current->getPosition(), pos, &res);

				m_box->setPosition(res);
			}
		}

		if (m_physicsWorld)
			m_physicsWorld->pulse(float(m_deltaTime));

#ifdef PROFILER
		Info("profiler", "Physics: %fs", (OS::getMicrosecondsCount() - start) / 1000000.f);
#endif
		Environment::get()->pulse();

		m_accumulator -= m_deltaTime;
	}



#ifdef PROFILER	
	start = OS::getMicrosecondsCount();
#endif
	if (m_renderer)
	{
		m_renderer->preFrame();

		if(m_scene)
			m_scene->render();

		if (gFont)
		{
			gFont->render(WString<256>(L"#64A5F2Testujemy renderowanie tekstu, jest coraz lepiej :D\n#00FF00Druga linia :)\n#216422Mamy sporo FPS'ów: #FF0000%.1f\n#FF8000łóść чертовски сука шлюха こんにちは", Timer::getFPS()), Rect(21, 21, 10, 10), Color(0.0f, 0.0f, 0.0f, 0.6f), Font::DrawFlags::NoClip | Font::DrawFlags::DisableColorCodding);
			gFont->render(WString<256>(L"#64A5F2Testujemy renderowanie tekstu, jest coraz lepiej :D\n#00FF00Druga linia :)\n#216422Mamy sporo FPS'ów: #FF0000%.1f\n#FF8000łóść чертовски сука шлюха こんにちは", Timer::getFPS()), Rect(20, 20, 10, 10), Color(1.0f, 1.0f, 1.0f, 1.0f), Font::DrawFlags::NoClip);
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

#ifdef PROFILER
	Info("profiler", "GFX: %fs", (OS::getMicrosecondsCount() - start) / 1000000.f);
#endif
	Timer::frameEnd();
	return m_isRunning;
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
	if (button == 1)
	{
		if (state)
		{
			press = OS::getMicrosecondsCount();
		}
		else
		{
			float force = (OS::getMicrosecondsCount() - press) / 100000.f;
			Vector3 a = Camera::current->getPosition();
			Vector3 b = Camera::current->getTarget();

			Vector3 diff = glm::normalize(b - a);
			Vector3 velocity = diff;
			velocity *= force * 90;

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

Game * Game::get()
{
	return s_instance;
}
