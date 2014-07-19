//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/Game.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <video/Window.h>

#include <video/renderer/opengl/OpenGLRenderer.h>

class Game
{
private:
	bool mRunning;
	bool mInitialized;

	IWindow * mWindow;
	IRenderer * mRenderer;
public:
	Game();
	~Game();

	bool init();

	bool pulse();
};