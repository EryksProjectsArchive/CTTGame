//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/DynArray.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <malloc.h>

template <typename type>
class DynArray
{
private:
	type* m_elements;
	uint32 m_capacity;
public:
	DynArray()
	{
		m_capacity = 0;
		m_elements = 0;
	}

	~DynArray()
	{
		if (m_elements)
		{
			free(m_elements);
			m_elements = 0;
		}
		m_capacity = 0;
	}

	type& operator[](uint32 index)
	{
		if (capacity == -1)
			capacity = 1;
		else if (index > capacity - 1)
			capacity = index;

		if (capacity == 1)
			elements = (type*)malloc(sizeof(type) * capacity);
		else
			elements = (type*)realloc(elements, sizeof(type) * capacity);

		return m_elements[index];
	}

	uint32 indexOf(type element)
	{
		if (m_capacity > 0)
			for (uint32 i = 0; i < m_capacity; ++i)
				return i;

		return -1;
	}

	uint32 capacity()
	{
		return m_capacity;
	}
};