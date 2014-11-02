//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/WDynString.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/Logger.h>

/**
* WDynString class is used to store dynamically allocated string. May be used to save memory.
* String stored in this class is null terminated so can be used in any standard c methods.
*/
class WDynString
{
private:
	wchar * m_buffer;
	uint32 m_size;

	void clear()
	{
		if (m_buffer)
		{
			delete[] m_buffer;
			m_buffer = 0;
		}
		m_size = 0;
	}
public:
	WDynString()
	{
		m_buffer = new wchar[1];
		m_buffer[0] = '\0';
		m_size = 0;
	}

	WDynString(const WDynString& string)
	{
		size_t size = string.m_size;
		m_buffer = new wchar[size + 1];
		wcscpy(m_buffer, string.m_buffer);
		m_buffer[size] = '\0';
		m_size = size;
	}

	WDynString(const wchar *buffer)
	{
		size_t size = wcslen(buffer);
		m_buffer = new wchar[size + 1];
		wcscpy(m_buffer, buffer);
		m_buffer[size] = '\0';
		m_size = size;
	}

	WDynString(wchar *buffer)
	{
		size_t size = wcslen(buffer);
		m_buffer = new wchar[size + 1];
		wcscpy(m_buffer, buffer);
		m_buffer[size] = '\0';
		m_size = size;
	}

	template <uint32 sizeOfString>
	WDynString(WString<sizeOfString> buffer)
	{
		size_t size = wcslen(buffer.get());
		m_buffer = new wchar[size + 1];
		wcscpy(m_buffer, buffer.get());
		m_buffer[size] = L'\0';
		m_size = size;
	}

	// NOTE: We need to do format-based constructor here - but how :-)
	// if ill find some idea how to "guess" size of desired buffer ill do it
	// for now ill leave it without that kind of constructor

	~WDynString()
	{
		clear();
	}

	const wchar * get() const
	{
		return m_buffer;
	}

	WDynString& operator=(const WDynString& rhs)
	{
		clear();
		m_buffer = new wchar[rhs.m_size + 1];
		wcscpy(m_buffer, rhs.m_buffer);
		m_buffer[rhs.m_size] = '\0';
		m_size = rhs.m_size;
		return *this;
	}

	WDynString& operator+=(const WDynString& rhs)
	{		
		wchar *temp = new wchar[m_size + 1];
		wcscpy(temp, m_buffer);
		
		m_size += rhs.m_size;

		delete[]m_buffer;
		m_buffer = new wchar[m_size + 1];
		wcscpy(m_buffer, temp);
		wcscat(m_buffer, rhs.m_buffer);
		m_buffer[m_size] = '\0';

		delete[]temp;
		return *this;
	}

	bool operator==(const WDynString& rhs)
	{
		return !wcscmp(m_buffer, rhs.m_buffer);
	}

	wchar operator[](uint32 index) const
	{
		if (index < 0 || index > m_size)
			return 0;

		return m_buffer[index];
	}

	uint32 getSize()
	{
		return m_size;
	}

	uint32 getLength() const
	{
		return m_size;
	}

	void reset()
	{
		m_buffer = new wchar[1];
		m_buffer[0] = '\0';
		m_size = 0;
	}

	WDynString substr(uint32 start, uint32 end)
	{
		if (!m_size)
			return *this;

		WDynString sub;
		if (sub.m_buffer)
			delete[]sub.m_buffer;

		uint32 len = end - start;
		sub.m_buffer = new wchar[len+1];
		memset(sub.m_buffer, 0, len*sizeof(wchar));
		wcsncpy(sub.m_buffer, m_buffer + start, end > m_size ? m_size : len);
		sub.m_buffer[len] = '\0';
		sub.m_size = len;
		return sub;
	}
};