//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/linux/LinuxWindow.h
// Author	: Patryk Ławicki
//
//////////////////////////////////////////////

#pragma once

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <X11/keysym.h> 
#include <GL/glx.h>
#include <video/Window.h>

#ifndef _WIN32
#	define _stdcall __attribute__((_stdcall_))
#endif

namespace Linux
{
	class Window : public IWindow
	{
	private: 
		::Window mWindow;
		Display *mDisplay;
		XVisualInfo *mVI;
		XSetWindowAttributes mSWA;

		int mScreen;  	
		int mOldMode;

		unsigned short mWidth;
		unsigned short mHeight;

		void *mModule;

		XVisualInfo*	(_stdcall *glXChooseVisual)( Display *dpy, int screen, int *attribList );

		Display 		*(_stdcall *XOpenDisplay)(_Xconst char*);
		::Window 		(_stdcall *XDefaultRootWindow)(Display*);
		Colormap		(_stdcall *XCreateColormap)(Display*, ::Window, Visual*, int);
		::Window 		(_stdcall *XCreateWindow)(Display*, ::Window, int, int, unsigned int, unsigned int, unsigned int, int, unsigned int, Visual*, unsigned long, XSetWindowAttributes*);
		int				(_stdcall *XNextEvent)(Display*, XEvent*);
		int 			(_stdcall *XMapWindow)(Display*, ::Window);
		int 			(_stdcall *XStoreName)(Display*, ::Window, _Xconst char*);
		int				(_stdcall *XDefaultScreen)(Display*);
		int				(_stdcall *XFree)(void*);
		int				(_stdcall *XCloseDisplay)(Display*);
		Atom 			(_stdcall *XInternAtom)(Display*, _Xconst char*, Bool);
		Status 			(_stdcall *XSetWMProtocols)(Display*, ::Window, Atom*, int);
		int				(_stdcall *XMapRaised)(Display*, ::Window);
		KeySym 			(_stdcall *XLookupKeysym)(XKeyEvent*, int);
		int				(_stdcall *XWarpPointer)(Display*, ::Window, ::Window, int, int, unsigned int, unsigned int, int, int);
		int 			(_stdcall *XGrabKeyboard)(Display*, ::Window, Bool, int, int, Time);
		int				(_stdcall *XGrabPointer)(Display*, ::Window, Bool, unsigned int, int, int, ::Window, Cursor, Time);
		Status			(_stdcall *XSendEvent)(Display*, ::Window, Bool, long, XEvent*);
		Status			(_stdcall *XGetWindowAttributes)(Display*, ::Window, XWindowAttributes*);
		int				(_stdcall *XMoveResizeWindow)(Display*, ::Window, int, int, unsigned int, unsigned int);
		int				(_stdcall *XMoveWindow)(Display*, ::Window, int, int);

		XRRScreenConfiguration *(_stdcall *XRRGetScreenInfo)(Display *dpy, ::Window window);
		SizeID 			(_stdcall *XRRConfigCurrentConfiguration)(XRRScreenConfiguration *config, Rotation *rotation);
		Status 			(_stdcall *XRRSetScreenConfig)(Display *dpy, XRRScreenConfiguration *config, Drawable draw, int size_index, Rotation rotation, Time timestamp);
		void 			(_stdcall *XRRFreeScreenConfigInfo)(XRRScreenConfiguration *config);
		XRRScreenSize 	*(_stdcall*XRRConfigSizes)(XRRScreenConfiguration *config, int *nsizes);


	public:
		Window();
		~Window();

		bool setup(const char *title, unsigned short width, unsigned short height, bool fullscreen);

		bool processMessages();

		void handleFocusLost();
		void handleFocus();

		void * getPtr();
		void * getSpecificPtr(unsigned char slot);

		unsigned short getWidth();
		unsigned short getHeight();

		void setFullscreen(bool fullscreen, unsigned short width, unsigned short height);
	};
};
