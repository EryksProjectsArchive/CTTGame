//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/Window.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Window.h"

IWindow::IWindow()
{
	this->mFullscreen = false;
}
	
IWindow::~IWindow()
{
}

bool IWindow::setup(const char *title, unsigned short width, unsigned short height, bool fullscreen)
{
	return false;
}

bool IWindow::processMessages()
{
	return false;
}

void * IWindow::getPtr()
{
	return 0;
}

void IWindow::setRenderer(IRenderer *renderer)
{
	this->mRenderer = renderer;
}

IRenderer * IWindow::getRenderer()
{
	return this->mRenderer;
}

unsigned short IWindow::getWidth()
{
	return 800;
}

unsigned short IWindow::getHeight()
{
	return 600;
}

void IWindow::setFullscreen(bool fullscreen, unsigned short width, unsigned short height)
{
	this->mFullscreen = fullscreen;
}

bool IWindow::isFullscreenEnabled()
{
	return this->mFullscreen;
}