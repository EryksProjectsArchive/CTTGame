//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/Renderer.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include "BufferBase.h"
#include <graphics/Window.h>

class RenderQueue;

class Window;

class Renderer
{
protected:
	Window* m_window;

	SDL_GLContext m_glContext;
public:
	Renderer();
	~Renderer();

	bool setup(Window * window);

	void preFrame();
	void postFrame();

	void setFullscreen(bool fullscreen);

	void doQueueRender(RenderQueue * queue);

	BufferBase * createBuffer(BufferType::Type type);
};