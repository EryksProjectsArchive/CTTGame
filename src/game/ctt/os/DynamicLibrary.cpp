//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/DynamicLibrary.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "DynamicLibrary.h"

DynamicLibrary::DynamicLibrary(const FilePath& fileName)
{
}

DynamicLibrary::~DynamicLibrary()
{
}

bool DynamicLibrary::isValid()
{
	return false;
}

unsigned long DynamicLibrary::getProcAddress(const String<128>& procName)
{
	return 0;
}
