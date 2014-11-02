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

#include <stdio.h>
#include <io/fs/FileOpenMode.h>
#include <io/fs/File.h>

namespace Stdio
{
	class File : public ::File
	{
	private:
		FILE * m_filePtr;

		virtual bool load(const FilePath& file, uint32 mode);
		virtual bool unload();
	public:
		File();
		~File();

		uint32 write(const void *data, uint32 count, uint32 size);
		uint32 read(void * data, uint32 count, uint32 size);

		void flush();

		DynString getContent();

		int32 tell();
		void seek(int32 position, SeekOrigin::Type origin);
		void rewind();

		friend class FileSystem;
	};
};