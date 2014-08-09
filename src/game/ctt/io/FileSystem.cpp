//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/FileSystem.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "FileSystem.h"

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

void FileSystem::setBaseDirectory(FilePath baseDirectory)
{
	m_baseDirectory = baseDirectory;
}

FilePath FileSystem::getBaseDirectory()
{
	return m_baseDirectory;
}

File * FileSystem::open(FilePath file)
{
	return 0;
}