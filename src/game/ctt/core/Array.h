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

template <class type, unsigned int size>
class Array
{
private:
	type elements[size];
public:
	Array()
	{
		for (unsigned int i = 0; i < size; ++i)
		{
			elements[i] = 0;
		}
	}

	~Array()
	{
		for (unsigned int i = 0; i < size; ++i)
		{
			elements[i] = 0;
		}
	}

	type& operator[](unsigned int index)
	{
		// Make sure about that index is valid, if no then return element at first index
		if (index < 0 || index > size)
		{
			index = 0;
		}
		return elements[index];
	}
};