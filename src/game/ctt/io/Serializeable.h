//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/Serializeble.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/String.h>

class Serializeable
{
public:
	Serializeable();
	~Serializeable();

	virtual void serialize(FilePath file) = 0;
	virtual void deserialize(FilePath file) = 0;
};