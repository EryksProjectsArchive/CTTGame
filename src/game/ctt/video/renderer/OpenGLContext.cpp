//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/renderer/OpenGLContext.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "OpenGLContext.h"

namespace OpenGL
{
	Context::Context()
	{
		this->mModule = 0;
	}

	Context::~Context()
	{
		if (this->mModule)
		{
			FreeLibrary(this->mModule);
			this->mModule = 0;
		}
	}

	void Context::init()
	{
#ifdef _WIN32
		this->mModule = LoadLibrary("opengl32.dll");
		if (this->mModule)
		{			
			this->wglCreateContext = (HGLRC(WINAPI *)(HDC))GetProcAddress(this->mModule, "wglCreateContext");
			this->wglMakeCurrent = (BOOL(WINAPI *)(HDC, HGLRC))GetProcAddress(this->mModule, "wglMakeCurrent");

			this->glShadeModel = (void(_stdcall *)(GLenum))GetProcAddress(this->mModule, "glShadeModel");
			this->glClear = (void(_stdcall *)(GLbitfield))GetProcAddress(this->mModule, "glClear");
			this->glClearColor = (void(_stdcall *)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))GetProcAddress(this->mModule, "glClearColor");
			this->glClearDepth = (void(_stdcall *)(GLclampd depth))GetProcAddress(this->mModule, "glClearDepth");

			this->glGetString = (const GLubyte * (_stdcall *)(GLenum name))GetProcAddress(this->mModule, "glGetString");
		}
#endif

	}

};