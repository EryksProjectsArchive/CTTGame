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
#elif __linux__
		//this->mModule = dlopen("libGL.so", )
#endif
		if (this->mModule)
		{
#ifdef _WIN32
#define GET_PROC GetProcAddress
#elif __linux__
#define GET_PROC dlsym
#endif
			// Macro to make code looking slightly better.
#define METHOD(name)\
			*(unsigned int *)&this->name = (unsigned int)GET_PROC(this->mModule, #name);\
			if(!this->name) { \
				Error("gfx","Cannot find OpenGL Method - '%s'.",#name);\
				return false;\
			}
			
#ifdef _WIN32
			METHOD(wglCreateContext);
			METHOD(wglMakeCurrent);
			METHOD(wglDeleteContext);
			METHOD(wglGetProcAddress);
			
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

#define EXT_METHOD(name)\
			*(unsigned int *)&this->name = (unsigned int)this->wglGetProcAddress(#name);\
			if(!this->name) { \
				Error("gfx","Cannot find OpenGL Method - '%s'.",#name);\
				return false;\
						}

#elif __linux__

#endif

			METHOD(glGetString);
			METHOD(glShadeModel);
			METHOD(glClear);
			METHOD(glClearDepth);
			METHOD(glClearColor);
			METHOD(glLoadIdentity);			
			METHOD(glMatrixMode);
			METHOD(glViewport);
			METHOD(glEnable);
			METHOD(glDisable);
			METHOD(glDepthFunc);
			METHOD(glHint);			
			METHOD(glGetIntegerv);
			METHOD(glVertexPointer);
			METHOD(glTexCoordPointer);
			METHOD(glColorPointer);
			METHOD(glNormalPointer);
			EXT_METHOD(glBindBuffer);
			METHOD(glDrawArrays);
			EXT_METHOD(glGenBuffers);
			EXT_METHOD(glBufferData);
			METHOD(glGenTextures);
			METHOD(glBindTexture);
			METHOD(glTexImage2D);
			METHOD(glTexParameteri);
			METHOD(glEnableClientState);
			METHOD(glDisableClientState);

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

			if (majorVersion < reqMajorVersion || (majorVersion == reqMajorVersion && minorVersion < reqMinorVersion))
			{
				Error("gfx", "Too old OpenGL detected %d.%d required using %d.%d!", reqMajorVersion, reqMinorVersion, majorVersion, minorVersion);
				return false;
			}			
			return true;
		}
		else
			Error("gfx", "Cannot find OpenGL32.dll file. Try to reinstall your graphics driver to fix that issue.");

		return false;
	}

	void Impl::swapBuffers()
	{
#ifdef _WIN32
		SwapBuffers(this->mHDC);
#endif
	}

	bool Impl::isExtensionPresent(const char *extension)
	{
		const unsigned char *extensions = NULL;
		const unsigned char *start;
		unsigned char *where, *terminator;

		// Extension names should not have spaces
		where = (unsigned char *)strchr(extension, ' ');
		if (where || *extension == '\0')
			return false;

		// Get Extensions String
		extensions = this->glGetString(GL_EXTENSIONS);

		// Search The Extensions String For An Exact Copy
		start = extensions;
		for (;;)
		{
			where = (unsigned char *)strstr((const char *)start, extension);
			if (!where)
				break;
			terminator = where + strlen(extension);
			if (where == start || *(where - 1) == ' ')
				if (*terminator == ' ' || *terminator == '\0')
					return true;
			start = terminator;
		}
		return false;
	}
};