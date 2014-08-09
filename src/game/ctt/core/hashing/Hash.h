//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/hashing/Hash.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class Hash
{
public:
	Hash()
	{

	}

	virtual ~Hash()
	{

	}

	virtual int encode(const char *data, size_t size)
	{
		return 0;
	}


	virtual unsigned int encode(const char *data, size_t size) const
	{
		return 0;
	}
};