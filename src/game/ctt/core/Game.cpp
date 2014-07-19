//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/Game.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <cstring>

#include "Game.h"
#include "Logger.h"

#include <os/OS.h>

Game::Game()
{
	this->mRunning = false;
	this->mInitialized = false;
	this->mWindow = 0;
	this->mRenderer = 0;
}

Game::~Game()
{

}

bool Game::init()
{
	if (this->mInitialized)
	{
		return false;
	}

	// Initialize sounds mgr, assets mgr etc

	// Setup home directory
	char szHomePath[256] = { 0 };
	strcpy(szHomePath, OS::initHomePath("City Transport Tycoon"));

	char szLogPath[256] = { 0 };
	strcpy(szLogPath, szHomePath);
	strcat(szLogPath, "game.log");

	Logger::init(szLogPath, false);

	// Create game window
	this->mWindow = OS::createWindowInstance();
	this->mWindow->setup("City Transport Tycoon", 1360, 768, true);

	this->mRenderer = IRenderer::create(RENDERER_API_OPENGL);
	if (!this->mRenderer->setup(this->mWindow))
	{
		Error("game", "Cannot setup renderer.");
		return false;
	}

	this->mInitialized = true;
	this->mRunning = true;
	return true;
}

bool Game::pulse()
{
	if (this->mWindow)
	{
		if (!this->mWindow->processMessages())
		{
			this->mRunning = false;
		}
	}
 
	if (this->mRenderer)
	{
		this->mRenderer->preFrame();

		this->mRenderer->postFrame();
	}

	return this->mRunning;
}