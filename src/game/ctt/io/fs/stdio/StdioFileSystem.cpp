//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/fs/stdio/StdioFileSystem.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "StdioFileSystem.h"
#include "StdioFile.h"

namespace Stdio
{
	FileSystem::FileSystem()
	{
	}

	FileSystem::~FileSystem()
	{
	}

	::File * FileSystem::open(FilePath file, uint32 mode)
	{
		Stdio::File * filePtr = new Stdio::File();
		if (filePtr)
			filePtr->load(file, mode);
	
		return filePtr;
	}
};