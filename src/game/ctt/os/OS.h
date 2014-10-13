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

#include <core/String.h>

#include "DynamicLibrary.h"

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

namespace OS
{
	// Paths
	FilePath getAppPath();
	FilePath getHomePath();
	FilePath initHomePath(const char *appName);

	// Files
	bool directoryExists(const FilePath& path);
	bool fileExists(const FilePath& path);
	bool makeDirectory(const FilePath& path);
	bool isFileOSDynLib(const FilePath& path);

	// Dynamic libs
	DynamicLibrary * openDynamicLibrary(const FilePath path);

	// Time OS functions
	unsigned long long getMicrosecondsCount();
	void initTime();

	// Message box
	void msgBox(const char *message, const char *title);
};
