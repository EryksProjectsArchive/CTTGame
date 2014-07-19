//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/renderer/Renderer.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <cstring>

#include "opengl/OpenGLRenderer.h"
#include "Renderer.h"

IRenderer::IRenderer()
{
	this->mWindow = NULL;
}

IRenderer::~IRenderer()
{
}

bool IRenderer::setup(IWindow * window)
{
	this->mWindow = window;
	return false;
}

void IRenderer::preFrame()
{
}

void IRenderer::postFrame()
{
}

char * IRenderer::getAPIName()
{
	return "NoAPI";
}

void IRenderer::setFullscreen(bool fullscreen)
{
}

IRenderer * IRenderer::create(RendererAPIs api)
{
	if (api == RENDERER_API_OPENGL)
		return new OpenGL::Renderer();

	return new IRenderer();
}

RendererAPIs IRenderer::getAPIIdFromString(const char *api)
{
	if (!strcmp(api, "gl") || !strcmp(api, "ogl") || !strcmp(api, "opengl"))
		return RENDERER_API_OPENGL;

	return RENDERER_API_NOAPI;
}