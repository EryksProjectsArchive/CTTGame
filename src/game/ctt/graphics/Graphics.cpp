//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Graphics.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Graphics.h"

#include "renderer/opengl/OpenGLRenderer.h"

IRenderer * Graphics::s_rendererInstance = 0;

IRenderer * Graphics::createRenderer(Graphics::RendererAPIs::Type api)
{
	IRenderer * renderer = 0;
	if (s_rendererInstance)
	{
		renderer = s_rendererInstance;
	}
	else
	{
		switch (api)
		{
		case Graphics::RendererAPIs::OPENGL:
			{
				renderer = new OpenGL::Renderer();;
			} break;
		default:
			{
				renderer = new IRenderer();
			} break;
		};
	}
	return renderer;
}

Graphics::RendererAPIs::Type Graphics::getRendererAPIFromString(const char *api)
{
	if (!strcmp(api, "gl") || !strcmp(api, "ogl") || !strcmp(api, "opengl"))
	{
		return Graphics::RendererAPIs::OPENGL;
	}

	return Graphics::RendererAPIs::NOAPI;
}

IRenderer * Graphics::getRenderer()
{
	return s_rendererInstance;
}