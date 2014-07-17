//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/Window.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class IWindow
{
public:
	IWindow();
	virtual ~IWindow();

	virtual bool setup(const char *title, int width, int height);
	virtual bool processMessages();
	virtual void * getPtr();
};