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

namespace OpenGL
{
	// OpenGL definitions
	typedef unsigned int GLenum;
	typedef unsigned char GLboolean;
	typedef unsigned int GLbitfield;
	typedef signed char GLbyte;
	typedef short GLshort;
	typedef int GLint;
	typedef int GLsizei;
	typedef unsigned char GLubyte;
	typedef unsigned short GLushort;
	typedef unsigned int GLuint;
	typedef float GLfloat;
	typedef float GLclampf;
	typedef double GLdouble;
	typedef double GLclampd;
	typedef void GLvoid;

	/* StringName */
	#define GL_VENDOR                         0x1F00
	#define GL_RENDERER                       0x1F01
	#define GL_VERSION                        0x1F02
	#define GL_EXTENSIONS                     0x1F03


	class Context
	{
	private:
#ifdef _WIN32
		HMODULE mModule;
#endif
	public:
		Context();
		~Context();

		void init();


		HGLRC	(_stdcall *wglCreateContext)(HDC);
		BOOL	(_stdcall *wglMakeCurrent)(HDC, HGLRC);

		void	(_stdcall *glShadeModel)(GLenum mode);
		void	(_stdcall *glClear)(GLbitfield mask);

		void	(_stdcall *glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
		void	(_stdcall *glClearDepth)(GLclampd depth);

		const GLubyte * (_stdcall * glGetString)(GLenum name);
	};
};