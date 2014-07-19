//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/renderer/opengl/OpenGLRenderer.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <core/Logger.h>

#include "OpenGLRenderer.h"

namespace OpenGL
{
	Renderer::Renderer()
	{
		this->mGL = new Impl();
	}

	Renderer::~Renderer()
	{
		if (this->mGL)
		{
			delete this->mGL;
			this->mGL = NULL;
		}
	}

	void Renderer::setFullscreen(bool fullscreen)
	{
		if (this->mWindow->isFullscreenEnabled() && fullscreen)
		{
			// Enable fullscreen
		}
		else
		{
			// Disable fullscreen
		}
	}

	bool Renderer::setup(IWindow * window)
	{
		this->mWindow = window;
		if (this->mGL->setup(window, MAKE_GL_VERSION(3,1)))
		{
			int width = window->getWidth(), height = window->getHeight();

			this->mGL->glShadeModel(GL_SMOOTH);
			this->mGL->glClearDepth(1.0f);

			this->mGL->glEnable(GL_DEPTH_TEST);
			this->mGL->glDepthFunc(GL_LEQUAL);
			this->mGL->glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			
			this->mGL->glViewport(0,0,width,height);

			this->mGL->glMatrixMode(GL_PROJECTION);	
			this->mGL->glLoadIdentity();

			this->mGL->glMatrixMode(GL_MODELVIEW);						
			this->mGL->glLoadIdentity();

			

			Info("gfx", "OpenGL Renderer started version %s. (Graphics vendor: %s, Graphics renderer: %s)", this->mGL->glGetString(GL_VERSION), this->mGL->glGetString(GL_VENDOR), this->mGL->glGetString(GL_RENDERER));
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
		this->mGL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->mGL->glLoadIdentity();
		this->mGL->glClearColor(0.5f, 0.9f, 0.5f, 1.0f);
	}

	void Renderer::postFrame()
	{
		this->mGL->swapBuffers();
	}

	char * Renderer::getAPIName()
	{
		return "OpenGL";
	}
};