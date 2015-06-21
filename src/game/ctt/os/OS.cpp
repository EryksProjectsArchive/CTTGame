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

#include <video/Window.h>

#include "OS.h"

#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#	include <Windows.h>
#	include <ShlObj.h>

#	include "win32/Win32Window.h"
#elif __linux__ 
#	include <sys/stat.h>
#	include <sys/types.h>
#	include <pwd.h>
#	include <unistd.h>

#	include "linux/LinuxWindow.h"
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
#elif __linux__ 
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
		static char myDocuments[MAX_PATH] = { 0 };
#ifdef _WIN32
		HRESULT hResult = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, (LPSTR)myDocuments);
		if (file)
		{
			strcat(myDocuments, "\\");
			strcat(myDocuments, file);
		}
		strcat(myDocuments, "\\");
		return myDocuments;
#elif __linux__ 
		struct passwd *pw = getpwuid(getuid());
		if (file)
		{
			strcat(myDocuments, pw->pw_dir);
			strcat(myDocuments, "/");
			strcat(myDocuments, file);
		}
		strcat(myDocuments, "/");
		return myDocuments;
#endif
	}

	bool fileExists(const char *path)
	{
#ifdef _WIN32
		return GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES;
#elif __linux__ 
		struct stat buf;
		return !stat(path,&buf);
#endif
	}

	bool directoryExists(const char *path)
	{
#ifdef _WIN32
		return GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES;
#elif __linux__ 
		struct stat buf;
		return !stat(path,&buf);
#endif
	}

	bool makeDirectory(const char *path)
	{
#ifdef _WIN32
		return ::CreateDirectory(path, NULL) == TRUE;
#elif __linux__ 
		return ::mkdir(path, S_IRWXU|S_IRGRP|S_IXGRP);
#endif
	}

	IWindow * createWindowInstance()
	{
#ifdef _WIN32
		return new Win32::Window();
#elif __linux__ 
		return new Linux::Window();
#endif
	}

	void msgBox(const char *message, const char *title)
	{
#ifdef _WIN32
		MessageBox(NULL, message, title, NULL);
#endif
	}
};