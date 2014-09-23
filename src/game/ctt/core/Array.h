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

template <class Type, unsigned int Size>
class Array
{
private:
	Type m_elements[Size];
public:
	Array()
	{
	}

	~Array()
	{
	}

	Type& operator[](unsigned int index)
	{
		// Make sure about that index is valid, if no then return element at first index
		if (index < 0 || index > Size)
			index = 0;

		return m_elements[index];
	}
};