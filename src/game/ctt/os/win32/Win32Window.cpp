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
		: mWindow(NULL)
	{
	}

	Window::~Window()
	{
		if (mWindow)
		{
			DestroyWindow(mWindow);
			UnregisterClass("AppWindow", mWndClass.hInstance);
		}
	}

	bool Window::setup(const char *title, int width, int height)
	{
		if (mWindow)
		{
			Warning("window", "Cannot setup window twice.");
			return false;
		}

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
			
		SetWindowLongPtr(mWindow, 0, (LONG_PTR)this);

		ShowWindow(mWindow, SW_SHOWNORMAL);
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

	LRESULT WINAPI Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Window *wnd = (Window *)GetWindowLongPtr(hWnd, 0);
		switch (uMsg)
		{
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