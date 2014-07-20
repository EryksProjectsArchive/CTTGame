//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/renderer/Renderer.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <video/Window.h>
#include "BufferBase.h"

enum RendererAPIs
{
	RENDERER_API_NOAPI,
	RENDERER_API_OPENGL,
	RENDERER_APIs_COUNT
};

class IRenderer
{
protected:
	IWindow * mWindow;
public:
	IRenderer();
	virtual ~IRenderer();

	virtual bool setup(IWindow * window);

	virtual void preFrame();
	virtual void postFrame();

	virtual char * getAPIName();

	virtual void setFullscreen(bool fullscreen);

	virtual BufferBase * createBuffer(BufferType type);

	static IRenderer * create(RendererAPIs api);
	static RendererAPIs getAPIIdFromString(const char *api);
};