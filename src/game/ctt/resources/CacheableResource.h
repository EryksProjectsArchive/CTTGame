//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/CacheableResource.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include "Resource.h"

class CacheableResource : public Resource
{
private:
	uint32 m_refCount;
public:
	CacheableResource(const FilePath& filePath);
	virtual ~CacheableResource();

	void acquire();
	void release();

	uint32 getRefCount();
};