//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/DynString.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include "String.h"

/**
 * DynString class is used to store dynamically allocated string. May be used to save memory.
 * String stored in this class is null terminated so can be used in any standard c methods.
 */
class WDynString;
class DynString
{
private:
	char* m_buffer;
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
	DynString()
	{
		m_buffer = new char[1];
		m_buffer[0] = '\0';
		m_size = 0;
	}

	DynString(const DynString& string)
	{
		size_t size = string.m_size;
		m_buffer = new char[size + 1];
		strcpy(m_buffer, string.m_buffer);
		m_buffer[size] = '\0';
		m_size = size;
	}

	DynString(const char* buffer)
	{
		size_t size = strlen(buffer);
		m_buffer = new char[size+1];
		strcpy(m_buffer, buffer);
		m_buffer[size] = '\0';
		m_size = size;
	}

	template <int sizeOfString>
	DynString(String<sizeOfString> buffer)
	{
		size_t size = strlen(buffer.get());
		m_buffer = new char[size + 1];
		strcpy(m_buffer, buffer.get());
		m_buffer[size] = '\0';
		m_size = size;
	}

	// NOTE: We need to do format-based constructor here - but how :-)
	// if ill find some idea how to "guess" size of desired buffer ill do it
	// for now ill leave it without that kind of constructor

	~DynString()
	{
		clear();
	}

	const char* get() const
	{
		return m_buffer;
	}

	DynString& operator=(const DynString& rhs)
	{
		clear();
		m_buffer = new char[rhs.m_size + 1];
		strcpy(m_buffer, rhs.m_buffer);
		m_buffer[rhs.m_size] = '\0';
		m_size = rhs.m_size;
		return *this;
	}

	bool operator==(const DynString& rhs) const
	{
		return !strcmp(m_buffer, rhs.m_buffer);
	}

	unsigned char operator[](unsigned int index) const
	{
		if (index < 0 || index > m_size)
			return 0;

		return m_buffer[index];
	}

	uint32 getSize() const
	{
		return m_size;
	}

	uint32 getLength() const
	{
		return m_size;
	}
};