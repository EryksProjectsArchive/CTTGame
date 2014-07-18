//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/renderer/OpenGLContext.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

#include <video/Window.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace OpenGL
{
	#define MAKE_GL_VERSION(major, minor) (unsigned short)((major << 8) | minor)

	class Context
	{
	private:
#ifdef _WIN32
		HMODULE mModule;

		HDC mHDC;
		HGLRC mHRC;
#endif
	public:
		Context();
		~Context();

		bool setup(IWindow * window, unsigned short minVersion);

		void swapBuffers();

#ifdef _WIN32
		HGLRC	(_stdcall *wglCreateContext)(HDC);
		BOOL	(_stdcall *wglMakeCurrent)(HDC, HGLRC);
		BOOL (_stdcall *wglDeleteContext)(HGLRC);
#endif

		void	(_stdcall *glShadeModel)(GLenum mode);
		void	(_stdcall *glClear)(GLbitfield mask);

		void	(_stdcall *glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
		void	(_stdcall *glClearDepth)(GLclampd depth);

		const	GLubyte * (_stdcall * glGetString)(GLenum name);
		void	(_stdcall * glGetIntegerv)(GLenum pname, GLint *params);
	};
};