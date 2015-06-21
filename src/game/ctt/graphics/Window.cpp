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
		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
		}
	}
	return true;
}