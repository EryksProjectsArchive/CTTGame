//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/fs/FileSystem.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "FileSystem.h"

#include <core/Logger.h>

FileSystem::FileSystem()
{

}

FileSystem::~FileSystem()
{
	for (FileSystem *fs : m_fileSystems)
		delete fs;

	m_fileSystems.clear();
}

File * FileSystem::open(FilePath filePath, uint32 mode)
{
	FilePath path = buildPath(filePath);
	for (FileSystem *fs : m_fileSystems)
	{
		if (File * file = fs->open(path, mode))
			return file;			
	}
	return 0;
}

void FileSystem::close(File *file)
{
	if (file)
	{
		file->unload();
		delete file;
		file = 0;
	}
}

void FileSystem::setBaseDirectory(FilePath baseDirectory)
{
	Info("fs", "Base directory: ", *baseDirectory);
	m_baseDirectory = baseDirectory;
}

FilePath FileSystem::getBaseDirectory()
{
	return m_baseDirectory;
}

void FileSystem::registerFileSystem(FileSystem *fileSystem)
{
	m_fileSystems.pushBack(fileSystem);
}

void FileSystem::unregisterFileSystem(FileSystem *fileSystem)
{
	m_fileSystems.remove(fileSystem);
}

FilePath FileSystem::buildPath(FilePath file)
{
	return m_baseDirectory + file;
}