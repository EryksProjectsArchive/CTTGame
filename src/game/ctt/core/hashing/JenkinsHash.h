//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/hashing/JenkinsHash.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "Hash.h"

class JenkinsHash : public Hash
{
public:
	JenkinsHash()
	{

	}

	~JenkinsHash()
	{

	}

	unsigned int encode(const char *data, size_t len) const override
	{
		unsigned int hash, i;
		for (hash = i = 0; i < len; ++i)
		{
			hash += data[i];
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash;
	}
};

