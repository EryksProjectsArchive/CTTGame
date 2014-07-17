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

#ifdef _WIN32
#include <Windows.h>
#endif

namespace OpenGL
{
	class Renderer
	{
	private:
#ifdef _WIN32
		HDC mHDC;
#endif
		Context * mContext;
	public:
		Renderer();
		~Renderer();

		void setup(IWindow * window);

		void preFrame();
		void postFrame();
	};
};