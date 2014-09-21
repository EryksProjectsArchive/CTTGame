//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Window.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Window.h"
#include <game/Game.h>

Window::Window()
	: _window(0)
{

}

Window::~Window()
{
	if (_window)
	{
		_window = 0;
		SDL_DestroyWindow(_window);
	}
}

bool Window::setup(const char *title, unsigned short width, unsigned short height, bool fullscreen)
{
	if (!_window)
	{
		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN));
		if (!_window)
			return false;

		return true;
	}
	return false;
}

bool Window::processMessages()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return false;
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (!event.key.repeat)
				Game::get()->onKeyEvent(event.key.keysym.sym, event.type == SDL_KEYDOWN);
			break;
		}
	}
	return true;
}

float Window::getAspectRatio()
{
	int width = 0, height = 0;
	SDL_GetWindowSize(_window, &width, &height);
	return (float)width / (float)height;
}