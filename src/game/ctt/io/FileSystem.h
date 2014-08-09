//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/FileSystem.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/String.h>

#include "File.h"

class FileSystem
{
private:
	FilePath m_baseDirectory;
public:
	FileSystem();
	virtual ~FileSystem();

	virtual void setBaseDirectory(FilePath baseDirectory);
	virtual FilePath getBaseDirectory();

	virtual File * open(FilePath file);
};