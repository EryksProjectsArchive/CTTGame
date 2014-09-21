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
		virtual ~FileSystem();

		virtual ::File * open(FilePath file, FileOpenMode::Type mode) override;

		friend class File;
	};
};