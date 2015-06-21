//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/opengl/OpenGLRenderer.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <graphics/Window.h>
#include <graphics/renderer/Renderer.h>

#include "OpenGLImpl.h"

namespace OpenGL
{
	class Renderer : public IRenderer
	{
	private:
		Impl * m_gl;
	public:
		Renderer();
		~Renderer();

		bool setup(IWindow * window);

		void preFrame();
		void postFrame();

		void setFullscreen(bool fullscreen);

		char * getAPIName();
	};
};