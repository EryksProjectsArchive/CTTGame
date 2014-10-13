//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/OS.cpp
// Author	: Eryk Dwornicki
//			  Patryk Ławicki
//
//////////////////////////////////////////////

#include <graphics/Window.h>

#include "OS.h"

#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#	include <Windows.h>
#	include <ShlObj.h>

#	include "win32/Win32DynamicLibrary.h"
#elif __linux__ 
#	include <sys/stat.h>
#	include <sys/types.h>
#	include <pwd.h>
#	include <unistd.h>

#	include "win32/LinuxDynamicLibrary.h"
#endif

#include <core/String.h>

namespace OS
{
	static FilePath g_homePath;
	FilePath getAppPath()
	{
#ifdef _WIN32
		static char path[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, path, MAX_PATH);
		for (size_t i = strlen(path); i > 0; i--)
		{
			if (path[i] == '\\')
			{
				path[i+1] = '\0';
				break;
			}
		}
		return path;
#elif __linux__ 
		return FilePath(0);
#endif
	}

	FilePath initHomePath(const char *appName)
	{
		static char myDocuments[MAX_PATH] = { 0 };
		
#ifdef _WIN32
		HRESULT hResult = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, (LPSTR)myDocuments);
		if (appName)
		{
			strcat(myDocuments, "\\");
			strcat(myDocuments, appName);
		}
		strcat(myDocuments, "\\");
#endif
		
		if (!directoryExists(myDocuments))
		{
			if (!makeDirectory(myDocuments))
			{
				msgBox("Cannot make home directory!", "Error");
				
				return FilePath();
			}
		}
		g_homePath = myDocuments;
		return g_homePath;
	}

	FilePath getHomePath()
	{
		return g_homePath;
	}

	bool fileExists(const FilePath& path)
	{
#ifdef _WIN32
		return GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES;
#elif __linux__ 
		struct stat buf;
		return !stat(path,&buf);
#endif
	}

	bool directoryExists(const FilePath& path)
	{
#ifdef _WIN32
		return GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES;
#elif __linux__ 
		struct stat buf;
		return !stat(path,&buf);
#endif
	}

	bool makeDirectory(const FilePath& path)
	{
#ifdef _WIN32
		return ::CreateDirectory(path, NULL) == TRUE;
#elif __linux__ 
		return ::mkdir(path, S_IRWXU|S_IRGRP|S_IXGRP);
#endif
	}

	bool isFileOSDynLib(const FilePath& path)
	{
#ifdef _WIN32
		char windowsDirectory[256] = { 0 };
		GetWindowsDirectory(windowsDirectory, 256);
		return fileExists(FilePath("%s\\System32\\%s", windowsDirectory, path.get()));
#elif __linux__
		***** TODO: Linux support ***** (ERROR HERE ERROR HERE ERROR)
#endif
		return false;
	}

	DynamicLibrary * openDynamicLibrary(FilePath path)
	{
#ifdef _WIN32
		path.append(".dll");
		if (isFileOSDynLib(path) || fileExists(path)) 
		{
			return new Win32::DynamicLibrary(path);
		}
#elif __linux__
		path.append(".so");
		if (isFileOSDynLib(path) || fileExists(path))
		{
			return new Linux::DynamicLibrary(path);
		}
#endif
		return 0;
	}

	uint64 g_startLargeInt = 0;
	double g_frequency = 0.0;

	unsigned long long getMicrosecondsCount()
	{
		unsigned long long result = 0ull;
#ifdef _WIN32
		LARGE_INTEGER largeInt;
		QueryPerformanceCounter(&largeInt);
		result = uint64((largeInt.QuadPart - g_startLargeInt) / g_frequency);
#elif __linux__
		ERROR ERROR TO BE PORTED
#endif
		return result;
	}

	void initTime()
	{
#ifdef _WIN32
		LARGE_INTEGER li;
		if (QueryPerformanceFrequency(&li))
		{
			g_frequency = double(li.QuadPart) / 1000000.0;
		}


		LARGE_INTEGER lInt;
		QueryPerformanceCounter(&lInt);
		g_startLargeInt = lInt.QuadPart;
#elif __linux__
		ERROR ERROR TO BE PORTED
#endif
	}

	void msgBox(const char *message, const char *title)
	{
#ifdef _WIN32
		MessageBox(NULL, message, title, NULL);
#endif
	}
};