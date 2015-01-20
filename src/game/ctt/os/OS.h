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
#include <core/DynString.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef _WIN32
#define MUTEX_WAIT_INFIITE INFINITE

#define USE_CRITICAL_SECTIONS 1
#else
#define MUTEX_WAIT_INFINITE ((uint32)-1)
#endif
namespace OS
{
#ifdef _WIN32
	// Threads
	typedef HANDLE ThreadHandle;

#ifdef USE_CRITICAL_SECTIONS 
	// Mutexes
	typedef CRITICAL_SECTION MutexHandle;
#else
	typedef HANDLE MutexHandle;
#endif
#else
	// TODO
#endif

	void initializeMutex(MutexHandle* mutex, const DynString& name = "");
	void destroyMutex(MutexHandle* mutex);
	void lockMutex(MutexHandle *mutex, uint32 waitTime);
	void unlockMutex(MutexHandle *mutex);
	bool tryLockMutex(MutexHandle *mutex);

	// Threads
	typedef void(*pfnThreadCallback)(void * data);

	struct ThreadRunData
	{
		pfnThreadCallback m_callback;
		void* m_userData;
	};
		
	ThreadHandle createThread(ThreadRunData *data);
	bool terminateThread(ThreadHandle handle, uint32 exitCode);
	uint32 waitForThread(ThreadHandle handle, uint32 interval);
	bool closeThread(ThreadHandle handle);

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
	void multiByteToWideChar(const char *ansi, size_t ansiLen, wchar_t **utf8, size_t *utf8Len);
	void wideCharToMultiByte(const wchar_t *utf8, size_t utf8Len, char **ansi, size_t *ansiLen);

	// Dynamic libs
	DynamicLibrary * openDynamicLibrary(const FilePath path);

	// Time OS functions
	uint64 getMicrosecondsCount();
	void initTime();

	// Message box
	void msgBox(const char *message, const char *title);
};
