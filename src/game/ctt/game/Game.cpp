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

#include <cstring>

#include "Game.h"

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

#include "environment/Environment.h"

#include <physics/PhysicsWorld.h>

#include <input/Input.h>

#include <game/scene/entities/types/CrossroadEntity.h>
#include <game/scene/entities/types/BoxEntity.h>
#include <game/scene/entities/types/BallEntity.h>

#include <graphics/fonts/Font.h>

Game::Game()
	: m_isRunning(false), m_isInitialized(false), m_renderer(0), m_window(0), m_scene(0), m_physicsWorld(0)
{
	for (unsigned int i = 0; i < 4; ++i)
		controlls[i] = false;

	distance = 40.f;
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
}

Font *gFont = 0;

bool Game::init()
{
	if (m_isInitialized)
		return false;

	// Time
	OS::initTime();

	m_time = double(OS::getMicrosecondsCount() / 1000000);
	m_accumulator = 0.0;
	m_deltaTime = 1 / 60.0f;

	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Setup file system
	FileSystem::get()->registerFileSystem(new Stdio::FileSystem());
	FileSystem::get()->setBaseDirectory(FilePath("%s../../data/",OS::getAppPath()));

	// Setup home directory
	char szHomePath[MAX_PATH] = { 0 };
	strcpy(szHomePath, OS::initHomePath("Engine"));

	Logger::init(FilePath("%sgame.log", szHomePath), false);

	// create image loader
	ImageLoader::get()->registerLoader(new BMP::ImageLoader());

	// create sound loader
	SoundLoader::get()->registerLoader(new WAV::SoundLoader());

	// Create game window
	m_window = new Window();
	m_window->setup("Engine", 1280, 768, false);

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
	float x = -34.0f;
	int stack = 0;
	for (int i = 0; i < 100; ++i)
	{
		testEntity = new BoxEntity();		
		float y = 0;

		testEntity->setPosition(Vector3(x, y + stack * (testEntity->getHeight() + 0.3f), 0));
		m_scene->addEntity(testEntity);

		if (++stack >= 10)
		{
			x += 5.f;
			stack = 0;
		}
	}

	Camera::current->setPosition(Vector3(0.0f, -1.0f, 6.0f));
	Camera::current->setTarget(Vector3());

	Environment::get()->setSunPosition(Vector3(30.0f, 10.0f, 0.0f));

	gFont = new Font("../../data/fonts/tahoma.ttf", 12, Font::CreationFlags::Bold);

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
		if (m_physicsWorld)
			m_physicsWorld->pulse(m_deltaTime);

#ifdef PROFILER
		Info("profiler", "Physics: %fs", (OS::getMicrosecondsCount() - start) / 1000000.f);
#endif
		Environment::get()->pulse();

		if (Camera::current)
		{
			static float mov = 0.0f;
			glm::vec3 pos = Camera::current->getPosition();

			if (vertical != 0)
			{
				if (vertical > 0)
					distance -= 1.f;
				else if (vertical < 0)
					distance += 1.f;
				vertical = 0;
			}

			pos.x = sinf(mov) * distance;
			pos.z = cosf(mov) * distance;

			if (controlls[2])
				mov += 0.01f;
			else if (controlls[3])
				mov -= 0.01f;

			if (controlls[0])
				pos.y += 1.f;

			if (controlls[1])
				pos.y -= 1.f;

			Camera::current->setPosition(pos);
		}

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
			gFont->render("Test", Rect(0, 0, 10, 10), Color(1.0f, 1.0f, 1.0f, 1.0f), Font::DrawFlags::NoClip);

		m_renderer->postFrame();
	}

#ifdef PROFILER
	Info("profiler", "GFX: %fs", (OS::getMicrosecondsCount() - start) / 1000000.f);
#endif
	Timer::frameEnd();

#ifdef PROFILER
	Info("profiler", "FPS: %f", Timer::getFPS());
#endif
	return m_isRunning;
}

// TODO: GameEvent
uint64 press = 0;
void Game::onKeyEvent(int key, bool state)
{
	if (key == 'a')
		controlls[2] = state;
	else if (key == 'd')
		controlls[3] = state;
	else if (key == 'w')
		controlls[0] = state;
	else if (key == 's')
		controlls[1] = state;

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
			diff.y += 2;
			diff.x *= 2;
			diff.z *= 2;

			BallEntity * ball = new BallEntity();
			ball->setPosition(a + diff);
			ball->setLinearVelocity(velocity);
			m_scene->addEntity(ball);
		}
	}

	//printf("%c / %s\n", key, state ? "press" : "release");
}

void Game::onMouseScroll(int horizontal, int vertical)
{
	this->vertical = vertical;
}

PhysicsWorld * Game::getPhysicsWorld()
{
	return m_physicsWorld;
}