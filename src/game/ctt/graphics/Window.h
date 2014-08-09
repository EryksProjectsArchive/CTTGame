//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Window.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class IRenderer;
class IWindow
{
protected:
	unsigned short m_width;
	unsigned short m_height;

	bool m_fullscreen;

	IRenderer* m_renderer;
public:
	IWindow();
	virtual ~IWindow();

	virtual bool setup(const char *title, unsigned short width = 800, unsigned short height = 600, bool fullscreen = false);
	virtual bool processMessages();

	virtual void* getPtr();
	virtual void* getSpecificPtr(unsigned char slot);

	virtual void handleFocusLost();
	virtual void handleFocus();

	virtual void setFullscreen(bool fullscreen, unsigned short width = 0, unsigned short height = 0);
	virtual bool isFullscreenEnabled();

	virtual void setRenderer(IRenderer* renderer);
	virtual IRenderer* getRenderer();

	virtual unsigned short getWidth();
	virtual unsigned short getHeight();
};