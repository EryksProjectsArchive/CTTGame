//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/Renderer.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Renderer.h"

IRenderer::IRenderer()
{
	m_window = 0;
}

IRenderer::~IRenderer()
{
}

bool IRenderer::setup(IWindow * window)
{
	m_window = window;
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

BufferBase * IRenderer::createBuffer(BufferType type)
{
	return 0;
}