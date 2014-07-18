//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/renderer/OpenGLRenderer.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <video/Window.h>

#include "OpenGLContext.h"

namespace OpenGL
{
	class Renderer
	{
	private:
		Context * mContext;
	public:
		Renderer();
		~Renderer();

		bool setup(IWindow * window);

		void preFrame();
		void postFrame();
	};
};