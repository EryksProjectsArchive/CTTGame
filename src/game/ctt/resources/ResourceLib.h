//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/ResourceLib.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

template <typename Type>
class ResourceLib
{
public:
	ResourceLib()
	{

	}

	~ResourceLib()
	{

	}

	virtual Type* findByName(DynString name) = 0;
};