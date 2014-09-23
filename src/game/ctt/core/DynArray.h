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

#include <malloc.h>

template <typename type>
class DynArray
{
private:
	type * m_elements;
	unsigned int m_capacity;
public:
	DynArray()
	{
		m_capacity = -1;
		m_elements = 0;
	}

	~DynArray()
	{
		if (m_elements)
		{
			free(m_elements);
			m_elements = 0;
		}
		m_capacity = -1;
	}

	type& operator[](unsigned int index)
	{
		if (capacity == -1)
			capacity = 1;
		else if (index > capacity - 1)
			capacity = index;

		if (capacity == 1)
			elements = (type *)malloc(sizeof(type) * capacity);
		else
			elements = (type *)realloc(elements, sizeof(type) * capacity);

		return m_elements[index];
	}

	unsigned int capacity()
	{
		return m_capacity;
	}
};