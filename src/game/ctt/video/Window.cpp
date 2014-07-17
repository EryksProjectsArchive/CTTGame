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
}
	
IWindow::~IWindow()
{
}

bool IWindow::setup(const char *title, int width, int height)
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