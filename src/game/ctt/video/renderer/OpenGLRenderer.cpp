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

	bool Renderer::setup(IWindow * window)
	{
		if (this->mContext->setup(window, MAKE_GL_VERSION(3,1)))
		{
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
			return true;
		}
		else 
		{
			Error("gfx", "Failed to setup OpenGL context.");
			
		}
		return false;
	}

	void Renderer::preFrame()
	{
		this->mContext->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glLoadIdentity();
		this->mContext->glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	}

	void Renderer::postFrame()
	{
		this->mContext->swapBuffers();
	}
};