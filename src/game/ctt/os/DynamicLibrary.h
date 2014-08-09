//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/DynamicLibrary.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/String.h>

class DynamicLibrary
{
public:
	DynamicLibrary(FilePath fileName);
	virtual ~DynamicLibrary();

	virtual bool isValid();

	virtual unsigned long getProcAddress(String<128> procName);
};