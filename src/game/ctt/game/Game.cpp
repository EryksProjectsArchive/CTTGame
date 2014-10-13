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

#include <io/fs/FileSystem.h>
#include <io/fs/stdio/StdioFileSystem.h>

#include <sound/SoundManager.h>

#include <game/scene/Scene.h>

#include <game/scene/entities/Entity.h>

#include <resources/ImageLoader.h>
#include <resources/images/bmp/BMPImageLoader.h>
#include <resources/SoundLoader.h>
#include <resources/sounds/wav/WAVsoundLoader.h>

#include <physics/PhysicsWorld.h>

#include <input/Input.h>

#include <game/scene/entities/types/CrossroadEntity.h>
#include <game/scene/entities/types/BoxEntity.h>
#include <game/scene/entities/types/BallEntity.h>

#include <graphics/fonts/Font.h>

#include "Game.h"
#include "environment/Environment.h"

#include <io/Config.h>

Game * Game::s_singleton = 0;

Game::Game()
	: m_isRunning(false), m_isInitialized(false), m_renderer(0), m_window(0), m_scene(0), m_physicsWorld(0), m_config(0)
{
	s_singleton = this;
}

Game::~Game()
{
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

	s_singleton = 0;
}

Font *gFont = 0;

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

	// create sound loader
	SoundLoader::get()->registerLoader(new WAV::SoundLoader());

	// Create game window
	m_window = new Window();
	m_window->setup("Engine", Config::get()["graphics"]["resolution"]["width"].getInteger(1280), Config::get()["graphics"]["resolution"]["height"].getInteger(720), Config::get()["graphics"]["fullscreen"].getBool(false));

	m_renderer = new Renderer();
	if (!m_renderer->setup(m_window))
	{
		Error("game", "Cannot setup renderer.");
		return false;
	}

	// create game sound mgr

	if (!SoundManager::get()->setup())
	{
		Error("game", "Cannot setup SoundMgr!");
		return false;
	}

	Sound *sound = SoundManager::get()->createSound(SoundType::Effect);

	if (!sound->load("sounds/test.wav"))
	{
		return false;
	}

	sound->setVolume(0.1f);
	sound->play(false);

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


	Entity *entity = new Entity(EntityType::Dummy);	
	m_scene->addEntity(entity);

	CrossroadEntity * crossroad = new CrossroadEntity();
	m_scene->addEntity(crossroad);

	crossroad = new CrossroadEntity();
	crossroad->setPosition(Vector3(26, 0, 0));
	m_scene->addEntity(crossroad);


	crossroad = new CrossroadEntity();
	crossroad->setPosition(Vector3(-26, 0, 0));
	m_scene->addEntity(crossroad);

	crossroad = new CrossroadEntity();
	crossroad->setPosition(Vector3(0, 0, 26));
	m_scene->addEntity(crossroad);

	crossroad = new CrossroadEntity();
	crossroad->setPosition(Vector3(0, 0, -26));
	m_scene->addEntity(crossroad);

	BoxEntity *testEntity = 0;
	for (int i = 0; i < 10; ++i)
	{
		testEntity = new BoxEntity();		
		testEntity->setPosition(Vector3(0, i * (testEntity->getHeight()+0.5f), 0));
		m_scene->addEntity(testEntity);
	}

	Environment::get()->setSunPosition(Vector3(30.0f, 10.0f, 0.0f));

	gFont = new Font("fonts/tahoma.ttf", 25, Font::CreationFlags::Bold);

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
			Camera::current->update(float(m_deltaTime));

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
			gFont->render(String<128>("Testujemy renderowanie tekstu, jest coraz lepiej :D\nDruga linia :)\nMamy sporo FPS'ów: %.1f", Timer::getFPS()), Rect(22, 22, 10, 10), Color(0.0f, 0.0f, 0.0f, 0.5f), Font::DrawFlags::NoClip);
			gFont->render(String<128>("Testujemy renderowanie tekstu, jest coraz lepiej :D\nDruga linia :)\nMamy sporo FPS'ów: %.1f", Timer::getFPS()), Rect(20, 20, 10, 10), Color(1.0f, 1.0f, 1.0f, 1.0f), Font::DrawFlags::NoClip);
		}

		m_renderer->postFrame();
	}

#ifdef PROFILER
	Info("profiler", "GFX: %fs", (OS::getMicrosecondsCount() - start) / 1000000.f);
#endif
	Timer::frameEnd();
	return m_isRunning;
}

// TODO: GameEvent
uint64 press = 0;
void Game::onKeyEvent(int key, bool state)
{
	if (Camera::current)
		Camera::current->onKeyEvent(key, state);

	if (key == 0x1B)	
		m_isRunning = false;	

	// Shooting
	if (key == ' ')
	{
		if (state)
		{
			press = OS::getMicrosecondsCount();
		}
		else 
		{
			float force = (OS::getMicrosecondsCount() - press) / 999999.f;
			Vector3 a = Camera::current->getPosition();
			Vector3 b = Camera::current->getTarget();

			Vector3 diff = glm::normalize(b - a);
			Vector3 velocity = diff;
			velocity *= force * 90;

			BallEntity * ball = new BallEntity();
			ball->setPosition(a + diff*2.f);
			ball->setLinearVelocity(velocity);
			m_scene->addEntity(ball);
		}
	}
}

void Game::onMouseScroll(int horizontal, int vertical)
{
	if (Camera::current)
		Camera::current->onMouseScroll(horizontal, vertical); 
}

void Game::onMouseMove(int x, int y, int relx, int rely)
{
	if (Camera::current)
		Camera::current->onMouseMove(x, y, relx, rely);
}

PhysicsWorld * Game::getPhysicsWorld()
{
	return m_physicsWorld;
}

Game * Game::get()
{
	return s_singleton;
}