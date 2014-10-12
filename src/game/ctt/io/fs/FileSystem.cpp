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
#include <os/OS.h>

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
	for (FileSystem *fs : m_fileSystems)
		delete fs;

	m_fileSystems.clear();
}

void FileSystem::setHomePath(FilePath homePath)
{
	Info("fs", "Home path: %s", homePath.get());
	m_homePath = homePath;
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
	Info("fs", "Base directory: ", baseDirectory.get());
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
	if (file.find("home/") == 0)
	{
		FilePath path = file.replace("home/", m_homePath);
		Debug("home", "%s", path.get());
		return path;
	}
	return m_baseDirectory + file;
}