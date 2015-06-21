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
#include <graphics/renderer/Renderer.h>

namespace Win32
{
	Window::Window()		
	{
		m_window = NULL;
	}

	Window::~Window()
	{
		if (m_fullscreen)
		{
			ChangeDisplaySettings(NULL, 0);
			ShowCursor(TRUE);
		}

		if (m_window)
		{
			DestroyWindow(m_window);
			UnregisterClass("AppWindow", m_wndClass.hInstance);
		}
	}

	bool Window::setup(const char *title, unsigned short width, unsigned short height, bool fullscreen)
	{
		if (m_window)
		{
			Warning("window", "Cannot setup window twice.");
			return false;
		}

		m_width = width;
		m_height = height;

		Debug("window", "Creating window (Title: %s, Width: %d, Height: %d)", title, width, height);

		memset(&m_wndClass, 0, sizeof(m_wndClass));
		m_wndClass.cbSize = sizeof(WNDCLASSEX);
		m_wndClass.lpfnWndProc = Window::WndProc;
		m_wndClass.hInstance = GetModuleHandle(NULL);
		m_wndClass.hCursor = LoadCursor(0, IDC_ARROW);
		m_wndClass.hIcon = m_wndClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
		m_wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		m_wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		m_wndClass.lpszClassName = "AppWindow";

		if (RegisterClassEx(&m_wndClass) == 0)
		{
			Error("window", "Cannot register class for application window!");
			return false;
		}

		m_window = CreateWindowEx(0, "AppWindow", title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, width, height, 0, 0, m_wndClass.hInstance, 0);
	
		if (m_window == 0)
		{
			Error("window", "Cannot create application window!");
			return false;
		}
			
		SetWindowLongPtr(m_window, GWLP_USERDATA, (LONG_PTR)this);

		setFullscreen(fullscreen, width, height);

		ShowWindow(m_window, SW_SHOWNORMAL);
		SetFocus(m_window);
		SetForegroundWindow(m_window);

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
		return (void *)m_window;
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

		SetWindowLong(m_window, GWL_STYLE, style);

		m_fullscreen = fullscreen;

		if (width != 0)
			m_width = width;

		if (height != 0)
			m_height = height;

		SetWindowPos(m_window, NULL, 0, 0, m_width, m_height, SWP_NOCOPYBITS | SWP_SHOWWINDOW | SWP_FRAMECHANGED);

		if (m_renderer)
			m_renderer->setFullscreen(fullscreen);
	}

	void Window::handleFocusLost()
	{
		if (m_fullscreen)
		{
		//	ShowCursor(TRUE);
			ShowWindow(m_window, SW_MINIMIZE);
		}
	}
	
	void Window::handleFocus()
	{
		if (m_fullscreen)
		{	
			ShowWindow(m_window, SW_SHOW);			
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