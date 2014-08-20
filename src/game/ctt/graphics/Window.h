//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Window.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <SDL.h>

class Window
{
public:
	SDL_Window * _window;

	Window();
	~Window();

	bool setup(const char *title, unsigned short width = 800, unsigned short height = 600, bool fullscreen = false);
	bool processMessages();
};