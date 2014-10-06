//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/fs/FileSystem.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/String.h>
#include <core/List.h>
#include <core/Singleton.h>

#include "File.h"
#include "FileOpenMode.h"

class FileSystem : public Singleton<FileSystem>
{
private:
	List<FileSystem *> m_fileSystems;

	FilePath buildPath(FilePath file);
protected:
	FilePath m_baseDirectory;
public:
	FileSystem();
	virtual ~FileSystem();

	virtual File * open(FilePath file, uint32 mode);
	
	void close(File *file);
	
	void registerFileSystem(FileSystem *fileSystem);
	void unregisterFileSystem(FileSystem *fileSystem);

	void setBaseDirectory(FilePath baseDirectory);
	FilePath getBaseDirectory();
};