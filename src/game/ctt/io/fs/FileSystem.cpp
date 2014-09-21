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


FileSystem::FileSystem()
{

}

FileSystem::~FileSystem()
{
	for (FileSystem *fs : m_fileSystems)
		delete fs;

	m_fileSystems.clear();
}

File * FileSystem::open(FilePath filePath, FileOpenMode::Type mode)
{
	for (FileSystem *fs : m_fileSystems)
	{
		if (File * file = fs->open(filePath, mode))
			return file;			
	}
	return 0;
}

void FileSystem::close(File *file)
{
	for (FileSystem *fs : m_fileSystems)
		fs->close(file);

	if (file)
	{
		file->unload();
		delete file;
		file = 0;
	}
}

void FileSystem::setBaseDirectory(FilePath baseDirectory)
{
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