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
#include "console/Console.h"

#include <os/OS.h>

FILE * Logger::s_logFile = 0;

void Logger::init(const FilePath& file, bool bAppend)
{
	if (!s_logFile)
	{
		if (s_logFile = fopen(file, bAppend?"a+":"w+"))
		{
			Info("log", "Logger started! (%s)", file.get());
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
		return;
	}

	va_list args, args2;

	char message[512] = { 0 };
	wchar_t* wcMessage = 0;
	uint32 len = 0;
	va_start(args, msg);
	vsprintf(message, msg, args);
	va_end(args);

	OS::multiByteToWideChar(message, strlen(message), &wcMessage, &len);

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

	const char * prefix = 0;
	Console::MessageType::Type consoleMessageType;
	switch (type)
	{
	case LogType_Error:
		prefix = "<error> ";
		consoleMessageType = Console::MessageType::Error;
		break;
	case LogType_Warning:
		prefix = "<warning> ";
		consoleMessageType = Console::MessageType::Warning;
		break;
	case LogType_Debug:
		prefix = "<debug> ";
		consoleMessageType = Console::MessageType::Invalid;
		break;
	default:
		prefix = "<info> ";
		consoleMessageType = Console::MessageType::Info;
		break;		
	}

	Console::get()->output(consoleMessageType, wcMessage);
	delete []wcMessage;

	printf(prefix);
	fprintf(s_logFile, prefix);

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