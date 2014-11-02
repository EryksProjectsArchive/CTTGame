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
	virtual bool load(const FilePath& file, uint32 mode);
	virtual bool unload();

protected:
	bool m_isLoaded;
public:
	File();
	virtual ~File();

	virtual bool isLoaded();

	virtual uint32 write(const void *data, uint32 count, uint32 size);
	virtual uint32 read(void * data, uint32 count, uint32 size);

	virtual void flush();

	virtual DynString getContent();

	virtual int32 tell();
	virtual void seek(int32 position, SeekOrigin::Type origin);
	virtual void rewind();

	friend class FileSystem;
};