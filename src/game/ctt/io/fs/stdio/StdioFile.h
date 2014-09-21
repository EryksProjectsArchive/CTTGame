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

		virtual bool load(FilePath file, FileOpenMode::Type mode);
		virtual bool unload();
	public:
		File();
		~File();

		unsigned int write(const void *data, unsigned int count, unsigned int size);
		unsigned int read(void * data, unsigned int count, unsigned int size);

		void flush();

		DynString getContent();

		long tell();
		void seek(int position, SeekOrigin::Type origin);
		void rewind();

		friend class FileSystem;
	};
};