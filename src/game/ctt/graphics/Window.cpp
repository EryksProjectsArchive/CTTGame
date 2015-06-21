//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Window.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Window.h"

IWindow::IWindow()
	: m_fullscreen(false), m_width(800), m_height(600)
{
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

void * IWindow::getSpecificPtr(unsigned char slot)
{
	return 0;
}

void IWindow::handleFocusLost()
{
}

void IWindow::handleFocus()
{
}

void IWindow::setRenderer(IRenderer *renderer)
{
	m_renderer = renderer;
}

IRenderer * IWindow::getRenderer()
{
	return m_renderer;
}

unsigned short IWindow::getWidth()
{
	return m_width;
}

unsigned short IWindow::getHeight()
{
	return m_height;
}

void IWindow::setFullscreen(bool fullscreen, unsigned short width, unsigned short height)
{
	m_fullscreen = fullscreen;
}

bool IWindow::isFullscreenEnabled()
{
	return m_fullscreen;
}