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
#include <core/String.h>

#include "DynamicLibrary.h"

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
	bool directoryExists(FilePath path);
	bool fileExists(FilePath path);
	bool makeDirectory(FilePath path);
	bool isFileOSDynLib(FilePath path);

	// Window
	IWindow* createWindowInstance();

	// Dynamic libs
	DynamicLibrary * openDynamicLibrary(FilePath path);

	// Message box
	void msgBox(const char *message, const char *title);
};
