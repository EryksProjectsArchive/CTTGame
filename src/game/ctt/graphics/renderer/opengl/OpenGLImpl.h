//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/opengl/OpenGLContext.h
// Author	: Eryk Dwornicki
//			  Patryk Ławicki
//
//////////////////////////////////////////////

#pragma once

#ifdef _WIN32
#	include <Windows.h>
#elif __linux__
#	include <dlfcn.h>
#	include <string.h>
#	include <GL/glx.h>
#endif

#include <graphics/Window.h>
#include <GL/gl.h>

#include <os/DynamicLibrary.h>

#ifndef _WIN32
#	define _stdcall __attribute__((_stdcall_))
#endif

namespace OpenGL
{
	typedef unsigned int GLsizeiptr;
	#define MAKE_GL_VERSION(major, minor) (unsigned short)((major << 8) | minor)

	class Impl
	{
	private:
#ifdef _WIN32
		HDC m_hDC;
		HGLRC m_hRC;
#elif __linux__
        GLXContext m_GLXContext;
#endif
		DynamicLibrary* m_openGLDynLib;

        IWindow* m_window;
	public:
		Impl();
		~Impl();

		bool setup(IWindow * window, unsigned short minVersion);

		void swapBuffers();

		bool isExtensionPresent(const char *extension);

#ifdef _WIN32
		HGLRC	(_stdcall *wglCreateContext)(HDC);
		BOOL	(_stdcall *wglMakeCurrent)(HDC, HGLRC);
		BOOL	(_stdcall *wglDeleteContext)(HGLRC);
		PROC	(_stdcall *wglGetProcAddress)(LPCSTR);
#elif __linux__
		GLXContext	(_stdcall *glXCreateContext)(Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct);
		Bool	(_stdcall *glXMakeCurrent)(Display *   dpy, GLXDrawable   drawable, GLXContext   ctx);
		Bool	(_stdcall *glXDestroyContext)(Display *   dpy, GLXContext   ctx);
		void	*(_stdcall *glXGetProcAddress)(const GLubyte *   procName);
		void 	(_stdcall * glXSwapBuffers)(Display *  	dpy, GLXDrawable  	drawable);
#endif

		void	(_stdcall *glShadeModel)(GLenum mode);

		void	(_stdcall *glClear)(GLbitfield mask);
		void	(_stdcall *glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
		void	(_stdcall *glClearDepth)(GLclampd depth);

		void	(_stdcall *glLoadIdentity)(void);
		void    (_stdcall *glMatrixMode)(GLenum mode);

		void	(_stdcall * glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);

		void	(_stdcall *glEnable)(GLenum cap);
		void	(_stdcall *glDisable)(GLenum cap);

		void	(_stdcall *glDepthFunc)(GLenum func);
		void	(_stdcall *glHint)(GLenum target, GLenum mode);

		void	(_stdcall *glVertexPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
		void	(_stdcall *glTexCoordPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
		void	(_stdcall *glColorPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
		void	(_stdcall *glNormalPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

		void	(_stdcall *glBindBuffer)(GLenum target, GLuint buffer);
		void	(_stdcall *glDrawArrays)(GLenum mode, GLint first, GLsizei count);
		void	(_stdcall *glGenBuffers)(GLsizei n, GLuint * buffers);
		void	(_stdcall *glBufferData)(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);

		void	(_stdcall *glGenTextures)(GLsizei n, GLuint *textures);
		void	(_stdcall *glBindTexture)(GLenum target, GLuint texture);
		void	(_stdcall *glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
		void	(_stdcall *glTexParameteri)(GLenum target, GLenum pname, GLint param);

		void	(_stdcall *glDisableClientState)(GLenum array);
		void	(_stdcall *glEnableClientState)(GLenum array);

		const	GLubyte* (_stdcall *glGetString)(GLenum name);
		void	(_stdcall *glGetIntegerv)(GLenum pname, GLint *params);
	};
};
