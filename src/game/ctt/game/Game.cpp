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

#include <sound/SoundMgr.h>

#include <game/scene/Scene.h>

#include <game/scene/entities/Entity.h>

#include <resources/ImageLoader.h>
#include <resources/images/bmp/BMPImageLoader.h>

Model * road = 0;
Model *simpleBox = 0;
#define FREE_MODEL(mdl)\
	mdl->free();\
	delete mdl;\
	mdl = 0;

Game::Game()
	: m_isRunning(false), m_isInitialized(false), m_renderer(0), m_window(0), m_soundMgr(0), m_scene(0)
{
	for (unsigned int i = 0; i < 4; ++i)
		controlls[i] = false;

	distance = 28.f;
}

Game::~Game()
{
	FREE_MODEL(road);
	FREE_MODEL(simpleBox);

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

	if (m_soundMgr)
	{
		delete m_soundMgr;
		m_soundMgr = 0;
	}

	if (m_scene)
	{
		delete m_scene;
		m_scene = 0;
	}
}

bool Game::init()
{
	if (m_isInitialized)
	{
		return false;
	}

	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Setup file system
	FileSystem::get()->registerFileSystem(new Stdio::FileSystem());
	FileSystem::get()->setBaseDirectory(OS::getAppPath());

	// Setup home directory
	char szHomePath[MAX_PATH] = { 0 };
	strcpy(szHomePath, OS::initHomePath("City Transport Tycoon"));

	Logger::init(FilePath("%sgame.log", szHomePath), false);

	// create image loader
	ImageLoader::get()->registerLoader(new BMP::ImageLoader());

	// Create game window
	m_window = new Window();
	m_window->setup("City Transport Tycoon", 1240, 780);

	m_renderer = new Renderer();
	if (!m_renderer->setup(m_window))
	{
		Error("game", "Cannot setup renderer.");
		return false;
	}

	// create game sound mgr
	m_soundMgr = ISoundMgr::create(SoundAPI::OpenAL);

	if (!m_soundMgr->setup())
	{
		Error("game", "Cannot setup SoundMgr!");
		return false;
	}

	/*ISound *sound = m_soundMgr->createSound(SoundType::Effect);

	if (!sound->load("../../data/sounds/test.wav"))
	{
		return false;
	}

	sound->play();*/

	// Create scene
	m_scene = new Scene();

	Entity *entity = new Entity("building");
	
	m_scene->addEntity(entity);

	Camera::current->setPosition(Vector3(0.0f, 4.0f, 6.0f));
	Camera::current->setTarget(Vector3());

	road = new Model("../../data/models/road.mdl");
	road->acquire();

	simpleBox = new Model("../../data/models/simpleBox.mdl");
	simpleBox->acquire();

	m_isInitialized = true;
	m_isRunning = true;
	return true;
}

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

	if (Camera::current)
	{
		static float mov = 0.0f;
		glm::vec3 pos = Camera::current->getPosition();

		
		pos.x = sinf(mov) * distance;
		pos.z = cosf(mov) * distance;

		if (controlls[2])
			mov += 0.05f * Timer::getDeltaTimef();
		else if (controlls[3])
			mov -= 0.05f * Timer::getDeltaTimef();

		if (controlls[0])
			pos.y += 1.0f * Timer::getDeltaTimef();

		if (controlls[1])
			pos.y -= 1.0f * Timer::getDeltaTimef();

		Camera::current->setPosition(pos);
	}

	if (m_scene)
		m_scene->updatePhysics();
 
	if (m_renderer)
	{
		m_renderer->preFrame();

		if (m_scene)
			m_scene->render();

		{
			RenderContext ctx;
			road->render(ctx);
			simpleBox->render(ctx);
		}

		m_renderer->postFrame();
	}

	Timer::frameEnd();
	return m_isRunning;
}

// TODO: GameEvent
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
	//printf("%c / %s\n", key, state ? "press" : "release");
}

void Game::onMouseScroll(int horizontal, int vertical)
{
	if (vertical > 0)
		distance -= 1.0f * Timer::getDeltaTimef();
	else
		distance += 1.0f * Timer::getDeltaTimef();
}