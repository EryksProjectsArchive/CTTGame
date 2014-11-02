//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/Array.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

template <class type, uint32 size>
class Array
{
private:
	type m_elements[size];
public:
	Array()
	{			
	}

	~Array()
	{
	}

	type& operator[](uint32 index)
	{
		// Make sure about that index is valid, if no then return element at first index
		if (index < 0 || index > size)
			index = 0;

		return m_elements[index];
	}

	uint32 indexOf(type element)
	{
		for (uint32 i = 0; i < size; ++i)
		{
			if (m_elements[i] == element)
			{
				return i;
			}
		}
		return -1;
	}
};