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

bool File::load(FilePath file, FileOpenMode::Type mode)
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

unsigned int File::write(const void *data, unsigned int count, unsigned int size)
{
	return -1;
}

unsigned int File::read(void * data, unsigned int count, unsigned int size)
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

long File::tell()
{
	return -1;
}

void File::seek(int position, SeekOrigin::Type origin)
{

}

void File::rewind()
{

}
