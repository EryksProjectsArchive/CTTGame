/////////////////////////////////////////////////
//
//				Optimus Engine
//
// File:				OS.cpp
// Author(s):			Eryk Dwornicki
// Created:				11st July 2014
//
//	Copyright (C) 2014+ Black Ice Mountains
//
/////////////////////////////////////////////////

#include <video/Window.h>

#include "OS.h"

#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#include <ShlObj.h>

#include "win32/Win32Window.h"
#endif

namespace OS
{
	char * getAppPath()
	{
#ifdef _WIN32
		static char path[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, path, MAX_PATH);
		for (unsigned int i = strlen(path); i > 0; i--)
		{
			if (path[i] == '\\')
			{
				path[i+1] = '\0';
				break;
			}
		}
		return path;
#else
		return 0;
#endif
	}

	char * initHomePath(const char *appName)
	{
		static char homePath[MAX_PATH] = { 0 };
		strcpy(homePath, getHomePath(appName));
		if (!directoryExists(homePath))
		{
			if (!makeDirectory(homePath))
			{
				msgBox("Cannot make home directory!", "Error");
				return 0;
			}
		}
		return homePath;
	}

	char * getHomePath(const char *file)
	{
#ifdef _WIN32
		static char myDocuments[MAX_PATH] = { 0 };
		HRESULT hResult = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, (LPSTR)myDocuments);
		if (file)
		{
			strcat(myDocuments, "\\");
			strcat(myDocuments, file);
		}
		strcat(myDocuments, "\\");
		return myDocuments;
#else
		return 0;
#endif
	}

	bool fileExists(const char *path)
	{
#ifdef _WIN32
		return GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES;
#else
		return false;
#endif
	}

	bool directoryExists(const char *path)
	{
#ifdef _WIN32
		return GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES;
#else
		return false;
#endif
	}

	bool makeDirectory(const char *path)
	{
#ifdef _WIN32
		return ::CreateDirectory(path, NULL) == TRUE;
#else
		return false;
#endif
	}

	IWindow * createWindowInstance()
	{
#ifdef _WIN32
		return new Win32::Window();
#else
		return 0;
#endif
	}

	void msgBox(const char *message, const char *title)
	{
#ifdef _WIN32
		MessageBox(NULL, message, title, NULL);
#endif
	}
};