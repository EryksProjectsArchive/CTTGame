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

	String(char *buffer)
	{
		memset(m_buffer, 0, maxSize);

		size_t size = strlen(buffer);
		if (size > maxSize)
			size = maxSize;

		strcpy(m_buffer, buffer);
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

	String& append(const char *buffer)
	{
		size_t size = strlen(buffer);
		size_t length = getLength();

		if (length + size >= maxSize)
			size = maxSize - length;
		
		if (size > 0)
		{
			memcpy(((char *)m_buffer + length), buffer, size);
		}

		return *this;		
	}

	String& operator=(String& string)
	{
		unsigned int size = strlen(string.m_buffer);
		memcpy(m_buffer, string.m_buffer, size > maxSize ? maxSize : size);
		return *this;
	}

	String& operator=(const char *buffer)
	{
		uint32 size = strlen(buffer);
		memcpy(m_buffer, buffer, size > maxSize ? maxSize : size);
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

	uint16 String::find(const char * key)
	{		
		uint32 range = strlen(m_buffer);
		if (range + strlen(key) > maxSize)		
			range = maxSize;
		
		for (uint32 i = 0; i < range; ++i)
		{
			if (!memcmp(m_buffer + i, key, strlen(key)))
			{
				return i;
			}
		}
		
		return -1;
	}

	String operator+=(const char *value)
	{
		return append(value);
	}

	String operator+=(unsigned char c)
	{
		char value[2] = { 0 };
		value[0] = c;
		return append(value);
	}

	String substr(uint16 begin, uint16 length)
	{
		String newString;
		if (begin < maxSize)
		{
			uint16 end = begin + length;
			if (end > maxSize)
				end = maxSize;
			for (uint16 i = begin; i < end; ++i)
			{
				newString += m_buffer[i];
			}
		}
		return newString;
	}

	String replace(const char *key, const char *value)
	{
		String newString;
		uint16 keyPos = find(key);
		
		char temp[maxSize] = { 0 };
		strcpy(temp, keyPos < strlen(key) ? substr(strlen(key), strlen(m_buffer)) : substr(keyPos + strlen(key), strlen(m_buffer)));
		
		strcpy(newString.m_buffer, value);
		strcat(newString.m_buffer, temp);
		return newString;
	}
};

// Default string types
typedef String<260> FilePath;