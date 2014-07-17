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

		static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	public:
		Window();
		~Window();

		bool setup(const char *title, int width, int height);

		bool processMessages();

		void * getPtr();
	};
};
