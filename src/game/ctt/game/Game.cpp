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
#include <core/SharedPtr.h>

#include <os/OS.h>

#include <graphics/Model.h>
#include <graphics/Graphics.h>

Game::Game()
	: m_isRunning(false), m_isInitialized(false)
{
}

Game::~Game()
{
	if (m_window)
	{
		delete m_window;
		m_window = 0;
	}

	if (m_renderer)
	{
		delete m_renderer;
		m_renderer = 0;
	}

	if (m_soundMgr)
	{
		delete m_soundMgr;
		m_soundMgr = 0;
	}
}

SharedPtr<Model> g_sampleModel;

bool Game::init()
{
	if (m_isInitialized)
	{
		return false;
	}

	// Initialize sounds mgr, assets mgr etc

	// Setup home directory
	char szHomePath[MAX_PATH] = { 0 };
	strcpy(szHomePath, OS::initHomePath("City Transport Tycoon"));

	Logger::init(FilePath("%sgame.log", szHomePath), false);

	// Create game window
	m_window = OS::createWindowInstance();
	m_window->setup("City Transport Tycoon", 800, 600);

	m_renderer = Graphics::createRenderer(Graphics::RendererAPIs::OPENGL);
	if (!m_renderer->setup(m_window))
	{
		Error("game", "Cannot setup renderer.");
		return false;
	}

	g_sampleModel = SharedPtr<Model>(new Model());
	g_sampleModel->load("data/models/bus.mdl");

	// create game sound mgr
	m_soundMgr = ISoundMgr::create(SOUND_API_OPENAL);

	if (!m_soundMgr->setup())
	{
		Error("game", "Cannot setup SoundMgr!");
		return false;
	}

	m_isInitialized = true;
	m_isRunning = true;
	return true;
}

bool Game::pulse()
{
	if (m_window)
	{
		if (!m_window->processMessages())
		{
			m_isRunning = false;
		}
	}

	// TODO: update physics here
 
	if (m_renderer)
	{
		m_renderer->preFrame();

		if (g_sampleModel)
			g_sampleModel->render(m_renderer);

		m_renderer->postFrame();
	}

	return m_isRunning;
}