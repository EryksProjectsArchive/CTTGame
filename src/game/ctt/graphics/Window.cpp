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
#include <input/Input.h>
#include <os/OS.h>
#include <core/WDynString.h>

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
		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_SHOWN));
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
				Input::get()->onKeyEvent((Key::Type)event.key.keysym.scancode, event.type == SDL_KEYDOWN);
			break;
		case SDL_MOUSEWHEEL:
			Input::get()->onMouseScroll(event.wheel.x, event.wheel.y);
			break;		
		case SDL_MOUSEMOTION:
			Input::get()->onMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			Input::get()->onMouseButtonEvent(event.button.button, event.button.state == SDL_PRESSED, event.button.clicks, event.button.x, event.button.y);
			break;
		case SDL_TEXTINPUT:
			{
				char *text = event.text.text;
				wchar_t *wcText = 0;
				size_t wcLen = 0;
				OS::multiByteToWideChar(text, strlen(text), &wcText, &wcLen);
				Input::get()->onTextInput(wcText);
				delete[]wcText;
			} break;
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

int Window::getWidth()
{
	int width = 0, height = 0;
	SDL_GetWindowSize(_window, &width, &height);
	return width;
}

int Window::getHeight()
{
	int width = 0, height = 0;
	SDL_GetWindowSize(_window, &width, &height);
	return height;
}