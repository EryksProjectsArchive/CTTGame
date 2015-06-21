//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/opengl/OpenGLRenderer.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <core/Logger.h>

#include "OpenGLRenderer.h"

#include <math/Matrix.h>

namespace OpenGL
{
	Renderer::Renderer()
	{
		m_gl = new Impl();
	}

	Renderer::~Renderer()
	{
		if (m_gl)
		{
			delete m_gl;
			m_gl = NULL;
		}
	}

	void Renderer::setFullscreen(bool fullscreen)
	{
		if (m_window->isFullscreenEnabled() && fullscreen)
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
		m_window = window;

		if (m_gl->setup(window, MAKE_GL_VERSION(3,1)))
		{
			int width = window->getWidth(), height = window->getHeight();

			m_gl->glShadeModel(GL_SMOOTH);
			m_gl->glClearDepth(1.0f);

			m_gl->glEnable(GL_DEPTH_TEST);
			m_gl->glDepthFunc(GL_LEQUAL);
			m_gl->glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			
			m_gl->glViewport(0,0,width,height);

			m_gl->glMatrixMode(GL_PROJECTION);	
			m_gl->glLoadIdentity();

			m_gl->glMatrixMode(GL_MODELVIEW);						
			m_gl->glLoadIdentity();

			Info("gfx", "OpenGL Renderer started version %s. (Graphics vendor: %s, Graphics renderer: %s)", m_gl->glGetString(GL_VERSION), m_gl->glGetString(GL_VENDOR), m_gl->glGetString(GL_RENDERER));
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
		m_gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_gl->glLoadIdentity();
		m_gl->glClearColor(0.5f, 0.9f, 0.5f, 1.0f);
	}

	void Renderer::postFrame()
	{
		m_gl->swapBuffers();
	}

	char * Renderer::getAPIName()
	{
		return "OpenGL";
	}
};