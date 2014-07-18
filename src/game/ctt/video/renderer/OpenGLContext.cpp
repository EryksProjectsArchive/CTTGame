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

#include <core/Logger.h>

#include "OpenGLContext.h"

namespace OpenGL
{
	Context::Context()
	{
		this->mModule = 0;
#ifdef _WIN32
		this->mHDC = NULL;
		this->mHRC = NULL;
#endif
	}

	Context::~Context()
	{
#ifdef _WIN32
		this->wglMakeCurrent(this->mHDC, NULL);
		this->wglDeleteContext(this->mHRC);
		this->mHRC = NULL;

		DeleteDC(this->mHDC);
		this->mHDC = NULL;
#endif

		if (this->mModule)
		{
			FreeLibrary(this->mModule);
			this->mModule = 0;
		}
	}

	bool Context::setup(IWindow *window, unsigned short minVersion)
	{
		unsigned char reqMajorVersion = (minVersion >> 8) & 0xFF;
		unsigned char reqMinorVersion = (minVersion)& 0xFF;
		Info("gfx", "Starting open gl context. Minimal version required: %d.%d", (minVersion >> 8) & 0xFF, minVersion & 0xFF);
#ifdef _WIN32
		HWND wnd = (HWND)window->getPtr();

		mHDC = GetDC(wnd);

		static  PIXELFORMATDESCRIPTOR pfd =			// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),			// Size Of This Pixel Format Descriptor
			1,										// Version Number
			PFD_DRAW_TO_WINDOW |					// Format Must Support Window
			PFD_SUPPORT_OPENGL |					// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
			PFD_TYPE_RGBA,							// Request An RGBA Format
			32,										// Select Our Color Depth
			0, 0, 0, 0, 0, 0,                       // Color Bits Ignored
			0,										// No Alpha Buffer
			0,										// Shift Bit Ignored
			0,										// No Accumulation Buffer
			0, 0, 0, 0,								// Accumulation Bits Ignored
			16,										// 16Bit Z-Buffer (Depth Buffer)
			0,										// No Stencil Buffer
			0,										// No Auxiliary Buffer
			PFD_MAIN_PLANE,                         // Main Drawing Layer
			0,										// Reserved
			0, 0, 0									// Layer Masks Ignored
		};

		int PixelFormat = ChoosePixelFormat(mHDC, &pfd);
		SetPixelFormat(mHDC, PixelFormat, &pfd);

		this->mModule = LoadLibrary("opengl32.dll");
		if (this->mModule)
		{
			if (!(this->wglCreateContext = (HGLRC(WINAPI *)(HDC))GetProcAddress(this->mModule, "wglCreateContext")))
				return false;
			
			if (!(this->wglMakeCurrent = (BOOL(WINAPI *)(HDC, HGLRC))GetProcAddress(this->mModule, "wglMakeCurrent")))
				return false;

			if (!(this->wglDeleteContext = (BOOL(_stdcall *)(HGLRC))GetProcAddress(this->mModule, "wglDeleteContext")))
				return false;

			if (!(this->mHRC = this->wglCreateContext(mHDC)))
			{
				Error("gfx", "Cannot create wgl context");
				return false;
			}
			
			if (!this->wglMakeCurrent(mHDC, this->mHRC))
			{
				Error("gfx", "Cannot set current opengl context for device context.");
				return false;
			}

			if (!(this->glShadeModel = (void(_stdcall *)(GLenum))GetProcAddress(this->mModule, "glShadeModel")))
				return false;

			if (!(this->glClear = (void(_stdcall *)(GLbitfield))GetProcAddress(this->mModule, "glClear")))
				return false;

			if (!(this->glClearColor = (void(_stdcall *)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))GetProcAddress(this->mModule, "glClearColor")))
				return false;

			if (!(this->glClearDepth = (void(_stdcall *)(GLclampd depth))GetProcAddress(this->mModule, "glClearDepth")))
				return false;
		
			if (!(this->glGetString = (const GLubyte * (_stdcall *)(GLenum name))GetProcAddress(this->mModule, "glGetString")))
				return false;

			if (!(this->glGetIntegerv = (void(_stdcall *)(GLenum pname, GLint *params))GetProcAddress(this->mModule, "glGetIntegerv")))
				return false;

			const unsigned char * version = this->glGetString(GL_VERSION);

			unsigned int minorVersion = 0;
			unsigned int majorVersion = 0;
			unsigned int revision = 0;
			if (sscanf((const char *)version, "%d.%d.%d", &majorVersion, &minorVersion, &revision) != 3)
			{
				if (sscanf((const char *)version, "%d.%d", &majorVersion, &minorVersion) != 2)
				{
					Error("gfx","Invalid opengl version syntax! (%d)", version);
					return false;
				}
			}

			Info("gfx", "OpenGL version detected: %s (%d.%d.%d)", version, majorVersion, minorVersion, revision);

			if (majorVersion < reqMajorVersion || minorVersion < reqMinorVersion)
			{
				Error("gfx", "Too old OpenGL detected %d.%d required using %d.%d!", reqMajorVersion, reqMinorVersion, majorVersion, minorVersion);
				return false;
			}
			return true;
		}

		return false;
#else
		return false;
#endif
	}

	void Context::swapBuffers()
	{
#ifdef _WIN32
		SwapBuffers(this->mHDC);
#endif
	}
};