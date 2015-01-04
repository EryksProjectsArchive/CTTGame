//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/File.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "File.h"

File::File()
{
	m_isLoaded = false;
}
	
File::~File()
{

}

bool File::load(const FilePath& file, uint32 mode)
{
	return false;
}
	
bool File::unload()
{
	return false;
}

bool File::isLoaded()
{
	return m_isLoaded;
}

size_t File::write(const void *data, size_t count, size_t size)
{
	return -1;
}

size_t File::read(void * data, size_t count, size_t size)
{
	return -1;
}

void File::flush()
{

}

DynString File::getContent()
{
	return DynString();
}

int32 File::tell()
{
	return -1;
}

void File::seek(int position, SeekOrigin::Type origin)
{

}

void File::rewind()
{

}
