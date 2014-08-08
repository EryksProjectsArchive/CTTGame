//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/String.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <cstring>
#include <cstdarg>

template <int maxSize = 256>
class String
{
private:
	char m_buffer[maxSize];
public:
	String()
	{
		memset(m_buffer, 0, maxSize);
	}

	String(const char *buffer)
	{
		memset(m_buffer, 0, maxSize);

		int size = strlen(buffer);
		if (size > maxSize)
			size = maxSize;

		memcpy(m_buffer, buffer, size);
	}

	String(const char *buffer, ...)
	{
		char tempBuffer[maxSize] = { 0 };
		va_list args;
		va_start(args, buffer);
		vsprintf(tempBuffer, buffer, args);
		va_end(args);
		memcpy(m_buffer, tempBuffer, maxSize);
	}

	String::~String()
	{
	}

	operator const char*() const
	{
		return m_buffer;
	}

	const char * operator*() const
	{
		return m_buffer;
	}

	const char * String::get()
	{
		return m_buffer;
	}

	unsigned short String::getLength()
	{
		return strlen(m_buffer);
	}

	unsigned short String::getMaxSize()
	{
		return maxSize;
	}
};

// Default string types
typedef String<256> FilePath;