//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/Renderer.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <graphics/Window.h>
#include "BufferBase.h"

class IRenderer
{
protected:
	IWindow* m_window;
public:
	IRenderer();
	virtual ~IRenderer();

	virtual bool setup(IWindow * window);

	virtual void preFrame();
	virtual void postFrame();

	virtual char * getAPIName();

	virtual void setFullscreen(bool fullscreen);

	virtual BufferBase * createBuffer(BufferType type);
};