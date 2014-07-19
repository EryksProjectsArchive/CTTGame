//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/win32/Win32Window.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Windows.h>
#include <video/Window.h>

namespace Win32
{
	class Window : public IWindow
	{
	private:
		HWND mWindow;
		WNDCLASSEX mWndClass;

		unsigned short mWidth;
		unsigned short mHeight;

		static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	public:
		Window();
		~Window();

		bool setup(const char *title, unsigned short width, unsigned short height, bool fullscreen);

		bool processMessages();

		void handleFocusLost();
		void handleFocus();

		void * getPtr();

		unsigned short getWidth();
		unsigned short getHeight();

		void setFullscreen(bool fullscreen, unsigned short width, unsigned short height);
	};
};
