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

FILE * Logger::sLogFile = 0;

void Logger::init(const char *szFile, bool bAppend)
{
	if (!sLogFile)
	{
		if (sLogFile = fopen(szFile, bAppend?"a+":"w+"))
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
	if (sLogFile)
	{
		fclose(sLogFile);
		sLogFile = NULL;
	}
}

void Logger::log(const char *tag, LogType type, const char *msg, ...)
{
	if (!sLogFile)
	{
		printf("[FATAL ERROR] Cannot use Logger::log - no log file set!\n");
		return;
	}

	va_list args, args2;
	va_start(args, msg);

	time_t timeraw = time(NULL);
	struct tm * pTimeInfo = localtime(&timeraw);

	fprintf(sLogFile, "[%02d:%02d:%02d] ", pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
	printf("[%02d:%02d:%02d] ", pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);

	if (tag)
	{
		fprintf(sLogFile, "[%s] ", tag);
		printf("[%s] ", tag);
	}

	switch (type)
	{
	case LogType_Error:
		{
			fputs("<error> ", sLogFile);
			printf("<error> ");
			break;
		}
	case LogType_Warning:
		{
			fputs("<warning> ", sLogFile);
			printf("<warning> ");
			break;
		}
	case LogType_Debug:
		{
			fputs("<debug> ", sLogFile);
			printf("<debug> ");
			break;
		}
	default:
		{
			fputs("<info> ", sLogFile);
			printf("<info> ");
			break;
		}
	}

	va_copy(args2, args);
	vfprintf(sLogFile, msg, args2);
	fputc('\n', sLogFile);
	vprintf(msg, args);
	printf("\n");
	va_end(args);
	fflush(sLogFile);
}

FILE * Logger::getFile()
{
	return sLogFile;
}