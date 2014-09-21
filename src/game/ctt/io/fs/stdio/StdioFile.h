//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/fs/stdio/StdioFile.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/String.h>
#include <stdio.h>
#include <io/fs/FileOpenMode.h>
#include <io/fs/File.h>

namespace Stdio
{
	class File : public ::File
	{
	private:
		FILE * m_filePtr;

		virtual bool load(FilePath file, FileOpenMode::Type mode);
		virtual bool unload();
	public:
		File();
		virtual ~File();

		friend class FileSystem;
	};
};