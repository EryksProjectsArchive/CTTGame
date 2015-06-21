/////////////////////////////////////////////////
//
//				Optimus Engine
//
// File:				Logger.h
// Author(s):			Eryk Dwornicki
// Created:				11st July 2014
//
//	Copyright (C) 2014+ Black Ice Mountains
//
/////////////////////////////////////////////////

#pragma once

#include <stdio.h>

enum LogType
{
	LogType_Info,
	LogType_Error,
	LogType_Warning,
	LogType_Debug,

	LogTypes_Count
};

class Logger
{
private:
	static FILE * s_logFile;
public:
	static void init(const char * file, bool append = false);

	static void shutdown();

	static void log(const char *tag, LogType type, const char *msg, ...);

	static FILE * getFile();
};

#define Info(t,s,...) Logger::log(t,LogType_Info,s,##__VA_ARGS__)
#define Error(t,s,...) Logger::log(t,LogType_Error,s,##__VA_ARGS__)
#define Warning(t,s,...) Logger::log(t,LogType_Warning,s,##__VA_ARGS__)
#ifdef DEBUG
#    define Debug(t,s,...) Logger::log(t,LogType_Debug,s,##__VA_ARGS__)
#else
#    define Debug(t,s,...)
#endif