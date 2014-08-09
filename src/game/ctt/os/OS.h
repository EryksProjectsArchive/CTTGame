//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/OS.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <graphics/Window.h>

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

namespace OS
{
	// Paths
	char* getAppPath();
	char* getHomePath(const char *file);
	char* initHomePath(const char *appName);

	// Files
	bool directoryExists(const char *path);
	bool fileExists(const char *path);
	bool makeDirectory(const char *path);

	// Window
	IWindow* createWindowInstance();

	// Message box
	void msgBox(const char *message, const char *title);
};
