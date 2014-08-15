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
	static Renderer* s_instance;
public:
	Renderer();
	~Renderer();

	bool setup(Window * window);

	void preFrame();
	void postFrame();

	void setFullscreen(bool fullscreen);

	BufferBase * createBuffer(BufferType::Type type);

	static Renderer& get();

	// Extension methods
	static PFNGLCOMPILESHADERPROC glCompileShader;
	static PFNGLCREATESHADERPROC glCreateShader;
	static PFNGLDELETESHADERPROC glDeleteShader;
	static PFNGLSHADERSOURCEPROC glShaderSource;
	static PFNGLCREATEPROGRAMPROC glCreateProgram;
	static PFNGLDELETEPROGRAMPROC glDeleteProgram;
	static PFNGLATTACHSHADERPROC glAttachShader;
};