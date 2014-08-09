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
#include <graphics/Window.h>

namespace Win32
{
	class Window : public IWindow
	{
	private:
		HWND m_window;
		WNDCLASSEX m_wndClass;

		static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	public:
		Window();
		~Window() override;

		bool setup(const char *title, unsigned short width, unsigned short height, bool fullscreen) override;

		bool processMessages() override;

		void handleFocusLost()override;
		void handleFocus()override;

		void* getPtr() override;

		void setFullscreen(bool fullscreen, unsigned short width, unsigned short height) override;
	};
};
