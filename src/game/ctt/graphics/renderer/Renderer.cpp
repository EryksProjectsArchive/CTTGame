//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/Renderer.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Renderer.h"

Renderer::Renderer()
{
	m_window = 0;
	m_glContext = 0;
}

Renderer::~Renderer()
{
	if (m_glContext)
	{
		SDL_GL_DeleteContext(m_glContext);
		m_glContext = 0;
	}
}

bool Renderer::setup(Window * window)
{
	m_window = window;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_glContext = SDL_GL_CreateContext(window->_window);

	SDL_GL_SetSwapInterval(1);

	return true;
}

void Renderer::preFrame()
{

}

void Renderer::postFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 0.5f, 1.0f, 1.0f);


	SDL_GL_SwapWindow(m_window->_window);
}

void Renderer::setFullscreen(bool fullscreen)
{
	
}

BufferBase * Renderer::createBuffer(BufferType::Type type)
{
	return 0;
}

void Renderer::doQueueRender(RenderQueue * queue)
{

}