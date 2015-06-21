/////////////////////////////////////////////////
//
//				Optimus Engine
//
// File:				Logger.cpp
// Author(s):			Eryk Dwornicki
// Created:				11st July 2014
//
//	Copyright (C) 2014+ Black Ice Mountains
//
/////////////////////////////////////////////////

#include <stdio.h>
#include <time.h>
#include <cstdarg>

#include "Logger.h"

FILE * Logger::s_logFile = 0;

void Logger::init(const char *szFile, bool bAppend)
{
	if (!s_logFile)
	{
		if (s_logFile = fopen(szFile, bAppend?"a+":"w+"))
		{
			Info("log", "Logger started!");
		}
		else
		{
			printf("[FATAL ERROR] Cannot initialize logger (%s)\n", szFile);
		}
	}
	else
	{
		Error("log", "Cannot initialize logger two times!");
	}
}

void Logger::shutdown()
{
	Info("log", "Logger is shutting down.");
	if (s_logFile)
	{
		fclose(s_logFile);
		s_logFile = NULL;
	}
}

void Logger::log(const char *tag, LogType type, const char *msg, ...)
{
	if (!s_logFile)
	{
		printf("[FATAL ERROR] Cannot use Logger::log - no log file set!\n");
		return;
	}

	va_list args, args2;
	va_start(args, msg);

	time_t timeraw = time(NULL);
	struct tm * pTimeInfo = localtime(&timeraw);

	fprintf(s_logFile, "[%02d:%02d:%02d] ", pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
	printf("[%02d:%02d:%02d] ", pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);

	if (tag)
	{
		fprintf(s_logFile, "[%s] ", tag);
		printf("[%s] ", tag);
	}

	switch (type)
	{
	case LogType_Error:
		{
			fputs("<error> ", s_logFile);
			printf("<error> ");
			break;
		}
	case LogType_Warning:
		{
			fputs("<warning> ", s_logFile);
			printf("<warning> ");
			break;
		}
	case LogType_Debug:
		{
			fputs("<debug> ", s_logFile);
			printf("<debug> ");
			break;
		}
	default:
		{
			fputs("<info> ", s_logFile);
			printf("<info> ");
			break;
		}
	}

	va_copy(args2, args);
	vfprintf(s_logFile, msg, args2);
	fputc('\n', s_logFile);
	vprintf(msg, args);
	printf("\n");
	va_end(args);
	fflush(s_logFile);
}

FILE * Logger::getFile()
{
	return s_logFile;
}