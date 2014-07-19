//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/win32/Win32Window.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////


#include <core/Logger.h>

#include "Win32Window.h"

namespace Win32
{
	Window::Window()		
	{
		this->mWindow = NULL;
	}

	Window::~Window()
	{
		if (mFullscreen)
		{
			ChangeDisplaySettings(NULL, 0);
			ShowCursor(TRUE);
		}

		if (mWindow)
		{
			DestroyWindow(mWindow);
			UnregisterClass("AppWindow", mWndClass.hInstance);
		}
	}

	bool Window::setup(const char *title, unsigned short width, unsigned short height, bool fullscreen)
	{
		if (mWindow)
		{
			Warning("window", "Cannot setup window twice.");
			return false;
		}

		this->mWidth = width;
		this->mHeight = height;

		Debug("window", "Creating window (Title: %s, Width: %d, Height: %d)", title, width, height);

		memset(&mWndClass, 0, sizeof(mWndClass));
		mWndClass.cbSize = sizeof(WNDCLASSEX);
		mWndClass.lpfnWndProc = Window::WndProc;
		mWndClass.hInstance = GetModuleHandle(NULL);
		mWndClass.hCursor = LoadCursor(0, IDC_ARROW);
		mWndClass.hIcon = mWndClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
		mWndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		mWndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		mWndClass.lpszClassName = "AppWindow";

		if (RegisterClassEx(&mWndClass) == 0)
		{
			Error("window", "Cannot register class for application window!");
			return false;
		}

		mWindow = CreateWindowEx(0, "AppWindow", title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, width, height, 0, 0, mWndClass.hInstance, 0);

		if (mWindow == 0)
		{
			Error("window", "Cannot create application window!");
			return false;
		}
			
		SetWindowLongPtr(mWindow, GWLP_USERDATA, (LONG_PTR)this);

		setFullscreen(fullscreen, width, height);

		ShowWindow(mWindow, SW_SHOWNORMAL);
		SetFocus(mWindow);
		SetForegroundWindow(mWindow);

		Debug("window", "Window has been created sucessfully.");			
		return true;
	}

	bool Window::processMessages()
	{
		MSG msg;
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		return true;
	}

	void * Window::getPtr()
	{
		return (void *)mWindow;
	}

	unsigned short Window::getWidth()
	{
		return mWidth;
	}

	unsigned short Window::getHeight()
	{
		return mHeight;
	}

	void Window::setFullscreen(bool fullscreen, unsigned short width, unsigned short height)
	{
		unsigned int style = NULL;
		if (fullscreen)
		{
			DEVMODE dmScreenSettings;									
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = width;
			dmScreenSettings.dmPelsHeight = height;
			dmScreenSettings.dmBitsPerPel = 16;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			unsigned int retn = ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
			if (retn != DISP_CHANGE_SUCCESSFUL)
			{
				dmScreenSettings.dmBitsPerPel = 32;
				retn = ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
				if (retn != DISP_CHANGE_SUCCESSFUL)
				{
					Error("win32_window", "Cannot change display settings for fullscreen mode (%d).", retn);
					return;
				}
			}
			style = WS_POPUP;
		//	ShowCursor(FALSE);

			Info("win32_window", "Setting window fullscreen mode");
		}		
		else 
		{
			ChangeDisplaySettings(0, NULL);
			style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		//	ShowCursor(TRUE);
		}

		SetWindowLong(this->mWindow, GWL_STYLE, style);

		this->mFullscreen = fullscreen;

		if (width != 0)
			this->mWidth = width;

		if (height != 0)
			this->mHeight = width;

		SetWindowPos(this->mWindow, NULL, 0, 0, this->mWidth, this->mHeight, SWP_NOCOPYBITS | SWP_SHOWWINDOW | SWP_FRAMECHANGED);

		if (this->mRenderer)
			this->mRenderer->setFullscreen(fullscreen);
	}

	void Window::handleFocusLost()
	{
		if (mFullscreen)
		{
		//	ShowCursor(TRUE);
			ShowWindow(mWindow, SW_MINIMIZE);
		}
	}
	
	void Window::handleFocus()
	{
		if (mFullscreen)
		{	
			ShowWindow(mWindow, SW_SHOW);			
		//	ShowCursor(FALSE);
		}
	}

	LRESULT WINAPI Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Window *wnd = (Window *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		switch (uMsg)
		{		
		case WM_ACTIVATE:
			{				
				if (wnd)
				{
					if (LOWORD(wParam) == WA_ACTIVE)
						wnd->handleFocus();
					else
						wnd->handleFocusLost();
				}
			} break;
		case WM_KEYDOWN:
			{
				if (wParam == VK_ESCAPE)
				{
					PostQuitMessage(0);
				}
			} break;
		case WM_CLOSE:
			{
				DestroyWindow(hWnd);
				return 0;
			} break;
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			} break;			
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
};