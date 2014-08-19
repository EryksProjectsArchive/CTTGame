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

#include <Prerequisites.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <graphics/BufferBase.h>

class Renderer
{
protected:
	Window* m_window;

	SDL_GLContext m_glContext;
	static Renderer* s_instance;

	Material * m_currentMaterial;
	Material * m_defaultMaterial;
public:
	Renderer();
	~Renderer();

	bool setup(Window * window);

	void preFrame();
	void postFrame();

	void setFullscreen(bool fullscreen);

	BufferBase * createBuffer(BufferType::Type type);

	void setMaterial(Material * material);
	void renderGeometry(Geometry *geometry, Matrix4x4 * matrix);;

	static Renderer& get();

	// Extension methods
	static PFNGLCOMPILESHADERPROC glCompileShader;
	static PFNGLCREATESHADERPROC glCreateShader;
	static PFNGLDELETESHADERPROC glDeleteShader;
	static PFNGLSHADERSOURCEPROC glShaderSource;
	static PFNGLCREATEPROGRAMPROC glCreateProgram;
	static PFNGLDELETEPROGRAMPROC glDeleteProgram;
	static PFNGLATTACHSHADERPROC glAttachShader;
	static PFNGLUSEPROGRAMPROC glUseProgram;

	static PFNGLGENBUFFERSPROC glGenBuffers;
	static PFNGLBINDBUFFERPROC glBindBuffer;
	static PFNGLBUFFERDATAPROC glBufferData;
	static PFNGLMAPBUFFERPROC glMapBuffer;
	static PFNGLUNMAPBUFFERPROC glUnmapBuffer;
	static PFNGLDELETEBUFFERSPROC glDeleteBuffers;
};