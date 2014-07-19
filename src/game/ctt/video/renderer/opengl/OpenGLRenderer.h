//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/renderer/opengl/OpenGLRenderer.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <video/Window.h>
#include <video/renderer/Renderer.h>

#include "OpenGLImpl.h"

namespace OpenGL
{
	class Renderer : public IRenderer
	{
	private:
		Impl * mGL;
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