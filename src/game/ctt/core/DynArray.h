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
	type *elements;
	unsigned int capacity;
public:
	DynArray()
	{
		capacity = -1;
		elements = 0;
	}

	~DynArray()
	{
		if (elements)
		{
			free(elements);
			elements = 0;
		}
	}

	type& operator[](unsigned int index)
	{
		if (index != -1 && capacity == -1)
			capacity = 1;
		else if (index > capacity - 1)
			capacity = index;

		if (capacity == 1)
			elements = (type *)malloc(sizeof(type) * capacity);
		else
			elements = (type *)realloc(elements, sizeof(type) * capacity);

		return elements[index];
	}

	unsigned int capacity()
	{
		return capacity;
	}
};