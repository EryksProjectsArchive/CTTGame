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
	wchar m_buffer[maxSize];
public:
	WString()
	{
		memset(m_buffer, 0, maxSize * sizeof(wchar));
	}

	WString(const WString<maxSize>& string) : WString()
	{
		wcscpy(m_buffer, string.m_buffer);
	}

	WString(const wchar *buffer) : WString()
	{
		size_t size = wcslen(buffer);
		if (size > maxSize)
			size = maxSize;

		wcsncpy(m_buffer, buffer, size);
		size_t len = wcslen(m_buffer);
		m_buffer[len] = '\0';
	}

	WString(wchar *buffer) : WString()
	{
		size_t size = wcslen(buffer);
		if (size > maxSize)
			size = maxSize;

		wcsncpy(m_buffer, buffer, size);
		size_t len = wcslen(m_buffer);
		m_buffer[len] = '\0';
	}

	explicit WString(const wchar *buffer, ...)
	{
		wchar tempBuffer[maxSize] = { 0 };
		va_list args;
		va_start(args, buffer);
		vswprintf(tempBuffer, buffer, args);
		va_end(args);
		wcsncpy(m_buffer, tempBuffer, maxSize);
	}

	WString::~WString()
	{
	}

	WString& append(const wchar *buffer)
	{
		size_t size = wcslen(buffer);
		size_t length = getLength();

		if (length + size >= maxSize)
			size = maxSize - length;

		if (size > 0)
		{
			memcpy(((wchar *)m_buffer + length), buffer, size * sizeof(wchar));
		}

		return *this;
	}

	WString& operator=(WString& string)
	{
		size_t size = wcslen(string.m_buffer);
		memcpy(m_buffer, string.m_buffer, (size > maxSize ? maxSize : size) * sizeof(wchar));
		return *this;
	}

	WString& operator=(const wchar *buffer)
	{
		uint32 size = wcslen(buffer);
		memcpy(m_buffer, buffer, (size > maxSize ? maxSize : size) * sizeof(wchar));
		return *this;
	}

	WString operator+(WString& string) const
	{
		return WString(L"%s%s", m_buffer, string.m_buffer);
	}

	WString operator+(const wchar *buffer) const
	{
		return WString(L"%s%s", m_buffer, buffer);
	}

	wchar operator[](uint32 index)
	{
		if (index < 0 || index > maxSize)
			return 0;

		return m_buffer[index];
	}

	operator const wchar*() const
	{
		return m_buffer;
	}

	const wchar * WString::get() const
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

	uint16 WString::find(const wchar * key) const
	{
		uint32 range = wcslen(m_buffer);
		if (range + wcslen(key) > maxSize)
			range = maxSize;

		for (uint32 i = 0; i < range; ++i)
		{
			if (!memcmp(m_buffer + i, key, wcslen(key)*  sizeof(wchar)))
			{
				return i;
			}
		}

		return -1;
	}

	WString operator+=(const wchar *value)
	{
		return append(value);
	}

	WString operator+=(wchar c)
	{
		wchar value[2] = { 0 };
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

	WString replace(const wchar *key, const wchar *value)
	{
		WString newWString;
		uint16 keyPos = find(key);

		wchar temp[maxSize] = { 0 };
		wcscpy(temp, keyPos < wcslen(key) ? substr(wcslen(key), wcslen(m_buffer)) : substr(keyPos + wcslen(key), wcslen(m_buffer)));

		wcscpy(newWString.m_buffer, value);
		wcscat(newWString.m_buffer, temp);
		return newWString;
	}
};