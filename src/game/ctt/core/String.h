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

#include <Prerequisites.h>

#include <cstring>
#include <cstdarg>

template <int maxSize>
class String
{
private:
	char m_buffer[maxSize];
public:
	String()
	{
		memset(m_buffer, 0, maxSize);
	}

	String(const String<maxSize>& string)
	{
		memcpy(m_buffer, string.m_buffer, maxSize);
	}

	String(const char *buffer)
	{
		memset(m_buffer, 0, maxSize);
		
		size_t size = strlen(buffer);
		if (size > maxSize)
			size = maxSize;

		memcpy(m_buffer, buffer, size);
	}

	explicit String(const char *buffer, ...)
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

	void append(const char *buffer)
	{
		size_t size = strlen(buffer);
		size_t length = getLength();

		if (length + size >= maxSize)
			size = maxSize - length;
		
		if (size > 0)
			memcpy(m_buffer + length, buffer, size);
	}

	String& operator=(String& string)
	{
		unsigned int size = strlen(string.m_buffer);
		memcpy(m_buffer, string.m_buffer, size > maxSize ? maxSize : size);
		return *this;
	}

	String& operator=(const char *buffer)
	{
		memcpy(m_buffer, buffer, (unsigned int size = strlen(buffer)) > maxSize ? maxSize : size);
		return *this;
	}

	String operator+(String& string) const
	{
		return String("%s%s", m_buffer, string.m_buffer);
	}

	String operator+(const char *buffer) const
	{
		return String("%s%s", m_buffer, buffer);
	}

	unsigned char operator[](unsigned int index)
	{
		if (index < 0 || index > maxSize)
			return 0;

		return m_buffer[index];
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

	size_t String::getLength()
	{
		return strlen(m_buffer);
	}

	unsigned short String::getMaxSize()
	{
		return maxSize;
	}

	unsigned short String::find(const char * key)
	{		
		for (unsigned int i = 0; i < maxSize; ++i)		// should i change maxSize to maxSize - strlen(key)?
			if (!memcmp(&m_buffer[i], key, strlen(key)))
				return i;			
		
		return -1;
	}
};

// Default string types
typedef String<256> FilePath;