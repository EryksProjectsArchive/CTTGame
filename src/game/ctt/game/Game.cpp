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

#include <sound/SoundManager.h>

#include <game/scene/Scene.h>

#include <game/scene/entities/Entity.h>

#include <resources/ImageLoader.h>
#include <resources/images/bmp/BMPImageLoader.h>
#include <resources/SoundLoader.h>
#include <resources/sounds/wav/WAVsoundLoader.h>

#include "environment/Environment.h"

#include <game/scene/entities/types/CrossroadEntity.h>

#include <freetype.h>
#include <ftglyph.h>

Model *simpleBox = 0;
#define FREE_MODEL(mdl)\
	mdl->free();\
	delete mdl;\
	mdl = 0;

Game::Game()
	: m_isRunning(false), m_isInitialized(false), m_renderer(0), m_window(0), m_scene(0)
{
	for (unsigned int i = 0; i < 4; ++i)
		controlls[i] = false;

	distance = 28.f;
}

Game::~Game()
{
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
	FileSystem::get()->setBaseDirectory(FilePath("%s../../data/",OS::getAppPath()));

	/* Init free type
	// TODO: Font engine
	FT_Library ftLibrary;
	FT_Init_FreeType(&ftLibrary);

	FT_Face face;
	FT_New_Face(ftLibrary, "../../fonts/tahoma.ttf", 0, &face);

	int size = 12 << 6; // ft size = 1/64th of pixel
	FT_Set_Char_Size(face, size, size, 96, 96);

	unsigned int glyphWidth = 1024;
	unsigned int glyphHeight = 1024;
	unsigned char *texture = new unsigned char[2 * glyphWidth * glyphHeight];
	for (uint8 i = 0; i < 255; ++i)
	{
		FT_Load_Glyph(face, FT_Get_Char_Index(face, i), FT_LOAD_DEFAULT);
		
		FT_Glyph glyph;
		FT_Get_Glyph(face->glyph, &glyph);

		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);

		FT_BitmapGlyph bmGlyph = (FT_BitmapGlyph)glyph;

		FT_Bitmap& bm = bmGlyph->bitmap;

		for (uint32 x = 0; x < bm.width; ++x)
		{
			for (uint32 y = 0; y < bm.rows; ++y)
			{
				texture[2 * (x + y * bm.width)] = bm.buffer[x + bm.width * y];
				texture[2 * (x + y * bm.width) + 1] = bm.buffer[x + bm.width * y + 1];
			}
		}
	}*/


	// Setup home directory
	char szHomePath[MAX_PATH] = { 0 };
	strcpy(szHomePath, OS::initHomePath("City Transport Tycoon"));

	Logger::init(FilePath("%sgame.log", szHomePath), false);

	// create image loader
	ImageLoader::get()->registerLoader(new BMP::ImageLoader());

	// create sound loader
	SoundLoader::get()->registerLoader(new WAV::SoundLoader());

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

	sound->setVolume(0.3f);
	sound->play(true);

	// Create scene
	m_scene = new Scene();

	Entity *entity = new Entity("building");
	
	m_scene->addEntity(entity);

	CrossroadEntity * crossroad = new CrossroadEntity();

	m_scene->addEntity(crossroad);

	Camera::current->setPosition(Vector3(0.0f, 4.0f, 6.0f));
	Camera::current->setTarget(Vector3());

	simpleBox = new Model("../../data/models/simpleBox.mdl");
	simpleBox->acquire();

	Environment::get()->setSunPosition(Vector3(30.0f, 10.0f, 0.0f));

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

	Environment::get()->pulse();

	if (Camera::current)
	{
		static float mov = 0.0f;
		glm::vec3 pos = Camera::current->getPosition();

		
		pos.x = sinf(mov) * distance;
		pos.z = cosf(mov) * distance;

		if (controlls[2])
			mov += 0.05f * Timer::getDeltaTime();
		else if (controlls[3])
			mov -= 0.05f * Timer::getDeltaTime();

		if (controlls[0])
			pos.y += 1.0f * Timer::getDeltaTime();

		if (controlls[1])
			pos.y -= 1.0f * Timer::getDeltaTime();

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
		distance -= 1.0f * Timer::getDeltaTime();
	else
		distance += 1.0f * Timer::getDeltaTime();
}