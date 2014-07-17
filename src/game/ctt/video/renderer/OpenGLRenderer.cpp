//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/renderer/OpenGLRenderer.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <core/Logger.h>

#include "OpenGLRenderer.h"

#include <gl/GL.h>
#include <gl/GLU.h>

namespace OpenGL
{
	Renderer::Renderer()
	{
		this->mContext = new Context();
	}

	Renderer::~Renderer()
	{
		if (this->mContext)
		{
			delete this->mContext;
			this->mContext = NULL;
		}
	}

	void Renderer::setup(IWindow * window)
	{
#ifdef _WIN32
		this->mContext->init();

		int bits = 32;//32bit colors
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
			bits,								    // Select Our Color Depth
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

		HGLRC hRC = this->mContext->wglCreateContext(mHDC);

		this->mContext->wglMakeCurrent(mHDC, hRC);

		this->mContext->glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
		this->mContext->glClearDepth(1.0f);									// Depth Buffer Setup
		//glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		//glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

		//int width = 800, height = 600;
		//glViewport(0,0,width,height);						// Reset The Current Viewport

		//glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		//glLoadIdentity();									// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window
		//gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

		//glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		//glLoadIdentity();									// Reset The Modelview Matrix

		Info("gfx", "OpenGL Renderer started version %s. (Graphics vendor: %s, Graphics renderer: %s)", this->mContext->glGetString(GL_VERSION), this->mContext->glGetString(GL_VENDOR), this->mContext->glGetString(GL_RENDERER));
#else

#endif
	}

	void Renderer::preFrame()
	{
		this->mContext->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glLoadIdentity();
		this->mContext->glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	}

	void Renderer::postFrame()
	{
#ifdef _WIN32
		SwapBuffers(mHDC);
#endif
	}
};