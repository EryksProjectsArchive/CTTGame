//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/Resource.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/String.h>

class Resource
{
protected:
	bool m_isLoaded;
	FilePath m_filePath;
public:
	Resource(FilePath filePath);
	virtual ~Resource();
	virtual void destroy();

	virtual bool load();

	virtual bool isLoaded();
};