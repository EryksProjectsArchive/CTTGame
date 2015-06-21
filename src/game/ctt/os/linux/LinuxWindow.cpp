//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/linux/LinuxWindow.cpp
// Author	: Patryk Ławicki
//
//////////////////////////////////////////////

#include <string.h>
#include <dlfcn.h>
#include <X11/keysym.h>    
#include <core/Logger.h>
#include "LinuxWindow.h"

namespace Linux
{
	Window::Window()		
	{
		mDisplay = NULL;
		mVI = NULL;
		mModule = NULL;
		mOldMode = NULL;
		memset(&mWindow,0,sizeof(mWindow));
		memset(&mSWA,0,sizeof(mSWA));
	}

	Window::~Window()
	{
		if (mFullscreen)
		{
			::Window rootWindow = this->XDefaultRootWindow(mDisplay);
			XRRScreenConfiguration *config;
	
			config = this->XRRGetScreenInfo(mDisplay, rootWindow);
			if(config) 
			{
				Rotation current_rotation;
				this->XRRConfigCurrentConfiguration (config, &current_rotation);

				Info("linux_window", "Leaving full screen mode");
				this->XRRSetScreenConfig(mDisplay, config, rootWindow, mOldMode, current_rotation, CurrentTime);
				this->XRRFreeScreenConfigInfo(config);
			} 
			else 
			{
				Error("linux_window", "Could not switch from full screen mode: XRRGetScreenInfo failed");
			}
		}
		XCloseDisplay(mDisplay);
		dlclose(mModule);
	}

	bool Window::setup(const char *title, unsigned short width, unsigned short height, bool fullscreen)
	{
#define METHOD(name)\
    *(unsigned int *)&name = (unsigned int)dlsym(mModule, #name);\
    if(!name) { \
        printf("Cannot find OpenGL/X11 Method - '%s'.",#name);\
        return false;\
    }
		mModule = dlopen("libGL.so", RTLD_NOW);
		METHOD(glXChooseVisual);
		
		mModule = dlopen("libX11.so", RTLD_NOW);
		METHOD(XOpenDisplay);
		METHOD(XDefaultRootWindow);
		METHOD(XCreateColormap);
		METHOD(XCreateWindow);
		METHOD(XNextEvent);
		METHOD(XMapWindow);
		METHOD(XStoreName);
		METHOD(XDefaultScreen);
		METHOD(XFree);
		METHOD(XCloseDisplay);
		METHOD(XInternAtom);
		METHOD(XSetWMProtocols);
		METHOD(XMapRaised);
		METHOD(XLookupKeysym);
		METHOD(XWarpPointer);
		METHOD(XGrabKeyboard);
		METHOD(XGrabPointer);
		METHOD(XSendEvent);
		METHOD(XGetWindowAttributes);
		METHOD(XMoveResizeWindow);
		METHOD(XMoveWindow);

		mModule = dlopen("libXrandr.so", RTLD_NOW);
		METHOD(XRRGetScreenInfo);
		METHOD(XRRConfigCurrentConfiguration);
		METHOD(XRRSetScreenConfig);
		METHOD(XRRFreeScreenConfigInfo);
		METHOD(XRRConfigSizes);

		::Window root;
		Colormap cmap;
		GLint att[] = {GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, None};
		Atom wmDelete; 

		mDisplay = XOpenDisplay(NULL);

		mScreen = XDefaultScreen(mDisplay);

		if(!mDisplay) 
		{
			Error("linux_window", "Cannot connect to X server");
			return false;
		}

		mWidth = width;
		mHeight = height;

		Debug("linux_window", "Creating window (Title: %s, Width: %d, Height: %d)", title, width, height);

		root = this->XDefaultRootWindow(mDisplay);

		mVI = this->glXChooseVisual(mDisplay, mScreen, att);

		if(!mVI) 
		{
       		Error("linux_window", "No appropriate visual found");
       		return false;
 		} 
        Debug("linux_window","visual %p selected", (void *)mVI->visualid); 

        cmap = this->XCreateColormap(mDisplay, root, mVI->visual, AllocNone);

       	mSWA.colormap = cmap;

 		if(fullscreen)
 		{

			XRRScreenConfiguration *config;
			XRRScreenSize *sizes;
			Rotation current_rotation;
			int nsizes;
	
			config = this->XRRGetScreenInfo(mDisplay, root);

			if(config)
			sizes = this->XRRConfigSizes (config, &nsizes);

			if(config && nsizes > 0) {

				mOldMode = this->XRRConfigCurrentConfiguration (config, &current_rotation);

				int mode = -1;
				int mode_width = 2147483647;
				int mode_height = 2147483647;
				for(size_t i=0; i<nsizes; i++) 
				{
					if(sizes[i].width >= static_cast<int>(width) && 
						sizes[i].height >= static_cast<int>(height) &&
					    sizes[i].width < mode_width && 
						sizes[i].height < mode_height) 
					{
						mode = i;
						mode_width = sizes[i].width;
						mode_height = sizes[i].height;
					}
				}
				if(mode >= 0) {

					Info("linux_window", "Entering full screen mode");
					this->XRRSetScreenConfig(mDisplay, config, root, mode, current_rotation, CurrentTime);
				} else {
					Error("linux_window", "Could not switch to full screen mode: No conforming mode was found");
				}

				this->XRRFreeScreenConfigInfo(config);
			} else {
				Error("linux_window", "Could not switch to full screen mode: XRRGetScreenInfo failed");
			}

 			mSWA.border_pixel = 0;

 			mSWA.override_redirect = True;
			mSWA.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
			mSWA.backing_store = NotUseful;
    		mSWA.save_under = False;

			mWindow = this->XCreateWindow(mDisplay, RootWindow(mDisplay, mVI->screen), 0, 0, width, height, 0, mVI->depth, InputOutput, mVI->visual, CWBorderPixel|CWColormap|CWEventMask|CWOverrideRedirect , &mSWA);

			this->XMapRaised(mDisplay, mWindow); 

			this->XWarpPointer(mDisplay, None, mWindow, 0, 0, 0, 0, 0, 0);               
            this->XMapRaised(mDisplay, mWindow);                                 
       		this->XGrabKeyboard(mDisplay, mWindow, True, GrabModeAsync, GrabModeAsync, CurrentTime);                                     
        	this->XGrabPointer(mDisplay, mWindow, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, mWindow, None, CurrentTime);

			this->mFullscreen = fullscreen;

			Info("linux_window", "Setting window fullscreen mode");
 		}
 		else
 		{
 			mSWA.event_mask = ExposureMask | KeyPressMask;

			mWindow = this->XCreateWindow(mDisplay, root, 0, 0, width, height, 0, mVI->depth, InputOutput, mVI->visual, CWColormap | CWEventMask, &mSWA);	

			wmDelete = this->XInternAtom(mDisplay, "WM_DELETE_WINDOW", True);                 
        	this->XSetWMProtocols(mDisplay, mWindow, &wmDelete, 1);                                     
       		this->XMapRaised(mDisplay, mWindow); 
 		}


		this->XStoreName(mDisplay, mWindow, title); 
		this->XMapWindow(mDisplay, mWindow);

		Debug("linux_window", "Window has been created sucessfully.");			
		return true;
	}

	bool Window::processMessages()
	{
		XEvent  xev;
		XNextEvent(mDisplay, &xev);
		switch(xev.type)
		{
		/*case DestroyNotify:
			{
				return false;
			} break;*/
		case KeyPress:
			{
				if (XLookupKeysym(&xev.xkey, 0) == XK_Escape)
                {
                	return false;
                }
        	} break;
		}
        return true;
	}

	void * Window::getPtr()
	{
		return (void *)&mWindow;
	}

	void * Window::getSpecificPtr(unsigned char slot)
	{
		if(slot == 0)
		{
			return (void *)mVI;
		} 
		else if(slot == 1)
		{
			return (void *)mDisplay;
		}
		return 0;
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

			Info("linux_window", "Setting window fullscreen mode");
		}		
		else 
		{


		}


		this->mFullscreen = fullscreen;

		if (width != 0)
			mWidth = width;

		if (height != 0)
			mHeight = height;


		if (mRenderer)
			mRenderer->setFullscreen(fullscreen);
	}

	void Window::handleFocusLost()
	{
		if (mFullscreen)
		{

		}
	}
	
	void Window::handleFocus()
	{
		if (mFullscreen)
		{	

		}
	}
};