//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/File.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/String.h>

class File
{
private:
	virtual bool load(FilePath file);
	virtual bool unload();
public:
	File();
	virtual ~File();


};