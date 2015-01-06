//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/WWString.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <cstring>
#include <cstdarg>
#include <cwchar>

template <uint32 maxSize>
class WString
{
private:
	widechar m_buffer[maxSize];
public:
	WString()
	{
		memset(m_buffer, 0, maxSize * sizeof(widechar));
	}

	WString(const WString& string) : WString()
	{
		wcscpy(m_buffer, string.m_buffer);
	}

	WString(const widechar *buffer) : WString()
	{
		size_t size = wcslen(buffer);
		if (size > maxSize)
			size = maxSize;

		wcsncpy(m_buffer, buffer, size);
		size_t len = wcslen(m_buffer);
		m_buffer[len] = '\0';
	}

	WString(widechar *buffer) : WString()
	{
		size_t size = wcslen(buffer);
		if (size > maxSize)
			size = maxSize;

		wcsncpy(m_buffer, buffer, size);
		size_t len = wcslen(m_buffer);
		m_buffer[len] = '\0';
	}

	explicit WString(const widechar *buffer, ...)
	{
		widechar tempBuffer[maxSize] = { 0 };
		va_list args;
		va_start(args, buffer);
		vswprintf(tempBuffer, buffer, args);
		va_end(args);
		wcsncpy(m_buffer, tempBuffer, maxSize);
	}

	WString::~WString()
	{
	}

	WString& append(const widechar *buffer)
	{
		size_t size = wcslen(buffer);
		size_t length = getLength();

		if (length + size >= maxSize)
			size = maxSize - length;

		if (size > 0)
		{
			memcpy(((widechar *)m_buffer + length), buffer, size * sizeof(widechar));
		}

		return *this;
	}

	WString& operator=(WString& string)
	{
		size_t size = wcslen(string.m_buffer);
		memcpy(m_buffer, string.m_buffer, (size > maxSize ? maxSize : size) * sizeof(widechar));
		return *this;
	}

	WString& operator=(const widechar *buffer)
	{
		clear();
		size_t size = wcslen(buffer);
		memcpy(m_buffer, buffer, (size > maxSize ? maxSize : size) * sizeof(widechar));
		return *this;
	}

	WString operator+(WString& string) const
	{
		return WString(L"%s%s", m_buffer, string.m_buffer);
	}

	WString operator+(const widechar *buffer) const
	{
		return WString(L"%s%s", m_buffer, buffer);
	}

	widechar operator[](uint32 index)
	{
		if (index < 0 || index > maxSize)
			return 0;

		return m_buffer[index];
	}

	operator const widechar*() const
	{
		return m_buffer;
	}

	const widechar * WString::get() const
	{
		return m_buffer;
	}

	size_t WString::getLength()
	{
		return wcslen(m_buffer);
	}

	unsigned short WString::getMaxSize()
	{
		return maxSize;
	}

	size_t WString::find(const widechar * key) const
	{
		widechar *buffer = m_buffer;
		size_t index = 0;
		while (*buffer)
		{
			if (!wcscmp(buffer, key))
				return index;

			*buffer++;
			index++;
		}	
		return -1;
	}

	WString operator+=(const widechar *value)
	{
		return append(value);
	}

	WString operator+=(widechar c)
	{
		widechar value[2] = { 0 };
		value[0] = c;
		return append(value);
	}

	WString substr(uint16 begin, uint16 length)
	{
		WString newWString;
		if (begin < maxSize)
		{
			uint16 end = begin + length;
			if (end > maxSize)
				end = maxSize;
			for (uint16 i = begin; i < end; ++i)
			{
				newWString += m_buffer[i];
			}
		}
		return newWString;
	}

	WString replaceOnce(const widechar *key, const widechar *value)
	{
		WString newWString;
		uint16 keyPos = find(key);

		widechar temp[maxSize] = { 0 };
		wcscpy(temp, keyPos < wcslen(key) ? substr(wcslen(key), wcslen(m_buffer)) : substr(keyPos + wcslen(key), wcslen(m_buffer)));

		wcscpy(newWString.m_buffer, value);
		wcscat(newWString.m_buffer, temp);
		return newWString;
	}

	void clear()
	{
		memset(m_buffer, 0, maxSize * sizeof(widechar));
	}
};