//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/fs/stdio/StdioFileSystem.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <io/fs/FileSystem.h>

namespace Stdio
{
	class FileSystem : public ::FileSystem
	{
	public:
		FileSystem();
		~FileSystem();

		::File * open(FilePath file, uint32 mode) override;

		friend class File;
	};
};