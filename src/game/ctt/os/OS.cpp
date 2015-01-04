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
	static void runThread(void *data)
	{
		ThreadRunData *runData = (ThreadRunData *)data;
		if (runData)
		{
			if (runData->m_callback)
				runData->m_callback(runData->m_userData);
		}
	}

	ThreadHandle createThread(ThreadRunData * data)
	{
#ifdef _WIN32
		return CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)runThread, data, NULL, NULL);
#else
		// TODO
#endif		
	}

	bool terminateThread(ThreadHandle handle, uint32 exitCode)
	{
		
#ifdef _WIN32
		if (handle)
		{
			if(TerminateThread(handle, exitCode))
				return true;			
		}
		return false;
#else
		// TODO
		return false;
#endif
	}

	uint32 waitForThread(ThreadHandle handle, uint32 interval)
	{
#ifdef _WIN32
		if (handle)
		{
			return WaitForSingleObject(handle, interval);
		}
#endif
		return -1;
	}

	bool closeThread(ThreadHandle handle)
	{
#ifdef _WIN32
		if (handle)
		{
			return CloseHandle(handle) != FALSE;
		}
#endif
		return false;
	}

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

	void multiByteToWideChar(const char *mb, size_t mbLen, wchar_t **wc, size_t *wcLen)
	{
		*wcLen = ::MultiByteToWideChar(CP_UTF8, NULL, mb, (int32)mbLen, NULL, 0);
		*wc = new wchar_t[*wcLen + 1];
		::MultiByteToWideChar(CP_UTF8, NULL, mb, (int32)mbLen, *wc, (int32)(*wcLen));
		(*wc)[*wcLen] = '\0';
	}

	void wideCharToMultiByte(const wchar_t *utf8, size_t utf8Len, char **ansi, size_t *ansiLen)
	{
		*ansiLen = utf8Len;
		*ansi = new char[utf8Len+1];
		wcstombs(*ansi, utf8, utf8Len);
		(*ansi)[*ansiLen] = '\0';
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

	uint64 getMicrosecondsCount()
	{
		uint64 result = 0ull;
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