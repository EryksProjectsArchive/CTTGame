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
#include <core/DynString.h>

#include "FileOpenMode.h"

struct SeekOrigin
{
	enum Type
	{
		Set,
		Current,
		End,
		Count
	};
};

class File
{
private:
	virtual bool load(FilePath file, uint32 mode);
	virtual bool unload();

protected:
	bool m_isLoaded;
public:
	File();
	virtual ~File();

	virtual bool isLoaded();

	virtual unsigned int write(const void *data, unsigned int count, unsigned int size);
	virtual unsigned int read(void * data, unsigned int count, unsigned int size);

	virtual void flush();

	virtual DynString getContent();

	virtual long tell();
	virtual void seek(int position, SeekOrigin::Type origin);
	virtual void rewind();

	friend class FileSystem;
};