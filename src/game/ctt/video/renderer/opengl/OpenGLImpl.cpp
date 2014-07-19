//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/renderer/opengl/OpenGLImpl.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <core/Logger.h>

#include "OpenGLImpl.h"

namespace OpenGL
{
	Impl::Impl()
	{
		this->mModule = 0;
		this->mWindow = 0;
#ifdef _WIN32
		this->mHDC = NULL;
		this->mHRC = NULL;
#endif
	}

	Impl::~Impl()
	{
#ifdef _WIN32
		this->wglMakeCurrent(NULL, NULL);
		this->wglDeleteContext(this->mHRC);
		this->mHRC = NULL;

		ReleaseDC((HWND)mWindow->getPtr(), this->mHDC);
		this->mHDC = NULL;
#endif

		if (this->mModule)
		{
			FreeLibrary(this->mModule);
			this->mModule = 0;
		}
	}

	bool Impl::setup(IWindow *window, unsigned short minVersion)
	{
		this->mWindow = window;
		unsigned char reqMajorVersion = (minVersion >> 8) & 0xFF;
		unsigned char reqMinorVersion = (minVersion) & 0xFF;
		Info("gfx", "Starting open gl Impl. Minimal version required: %d.%d", (minVersion >> 8) & 0xFF, minVersion & 0xFF);

#ifdef _WIN32
		// Grab window hwnd
		HWND wnd = (HWND)window->getPtr();

		// Grab window device Impl
		mHDC = GetDC(wnd);

		// Setup pixel format descriptor
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 16;
		pfd.cDepthBits = 16;
		pfd.iLayerType = PFD_MAIN_PLANE;

		// Choose pixel format
		int pixelFormat = ChoosePixelFormat(mHDC, &pfd);
		if (!pixelFormat)
		{
			Error("gfx", "Cannot chose pixel format. (%d)", GetLastError());
			return false;
		}

		// Set pixel format
		if (!SetPixelFormat(mHDC, pixelFormat, &pfd))
		{
			Error("gfx", "Cannot set pixel format. (%d)", GetLastError());
			return false;
		}

		this->mModule = LoadLibrary("opengl32.dll");
		if (this->mModule)
		{
			// Macro to make code looking slightly better.
#define METHOD(name)\
			*(unsigned int *)&this->name = (unsigned int)GetProcAddress(this->mModule, #name);\
			if(!this->name) { \
				Error("gfx","Cannot find OpenGL Method - '%s'.",#name);\
				return false;\
			}

			METHOD(wglCreateContext);
			METHOD(wglMakeCurrent);
			METHOD(wglDeleteContext);

			if (!(this->mHRC = this->wglCreateContext(mHDC)))
			{
				Error("gfx", "Cannot create wgl Impl");
				return false;
			}
			
			if (!this->wglMakeCurrent(mHDC, this->mHRC))
			{
				Error("gfx", "Cannot set current opengl Impl for device Impl.");
				return false;
			}

			METHOD(glShadeModel);
			METHOD(glClear);
			METHOD(glClearDepth);
			METHOD(glClearColor);

			METHOD(glLoadIdentity);
			
			METHOD(glMatrixMode);

			METHOD(glViewport);

			METHOD(glEnable);
			METHOD(glDepthFunc);
			METHOD(glHint);

			METHOD(glGetString);
			METHOD(glGetIntegerv);

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
		else
			Error("gfx", "Cannot find OpenGL32.dll file. Try to reinstall your graphics driver to fix that issue.");

		return false;
#else
		return false;
#endif
	}

	void Impl::swapBuffers()
	{
#ifdef _WIN32
		SwapBuffers(this->mHDC);
#endif
	}
};