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

// Extension methods
PFNGLCOMPILESHADERPROC Renderer::glCompileShader = 0;
PFNGLCREATESHADERPROC Renderer::glCreateShader = 0;
PFNGLDELETESHADERPROC Renderer::glDeleteShader = 0;
PFNGLSHADERSOURCEPROC Renderer::glShaderSource = 0;
PFNGLCREATEPROGRAMPROC Renderer::glCreateProgram = 0;
PFNGLDELETEPROGRAMPROC Renderer::glDeleteProgram = 0;
PFNGLATTACHSHADERPROC Renderer::glAttachShader = 0;

Renderer * Renderer::s_instance = 0;

Renderer::Renderer()
{
	m_window = 0;
	m_glContext = 0;
	s_instance = this;
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

	glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
	glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");

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

Renderer& Renderer::get()
{
	return *s_instance;
}