//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/fs/File.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/String.h>
#include "FileOpenMode.h"

class File
{
private:
	virtual bool load(FilePath file, FileOpenMode::Type mode);
	virtual bool unload();

public:
	File();
	virtual ~File();

	friend class FileSystem;
};