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

#include <Prerequisites.h>

#include <core/String.h>

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

	// Strings
	void multiByteToWideChar(const char *ansi, uint32 ansiLen, wchar_t **utf8, uint32 *utf8Len);

	// Dynamic libs
	DynamicLibrary * openDynamicLibrary(const FilePath path);

	// Time OS functions
	uint64 getMicrosecondsCount();
	void initTime();

	// Message box
	void msgBox(const char *message, const char *title);
};
