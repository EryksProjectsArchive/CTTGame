//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/SoundLoader.cpp
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#include "SoundLoader.h"
#include <stdio.h>

SoundLoader::SoundLoader()
{
}

SoundLoader::~SoundLoader()
{
	for (SoundLoader * loader : m_loaders)
		delete loader;

	m_loaders.clear();
}

bool SoundLoader::isFileValid(const FilePath& filePath)
{
	return false;
}

void SoundLoader::registerLoader(SoundLoader * loader)
{
	m_loaders.pushBack(loader);
}

SoundData * SoundLoader::load(const FilePath& filePath)
{
	SoundData * data = 0;
	for (SoundLoader *loader : m_loaders)
	{
		if (loader->isFileValid(filePath) && (data = loader->load(filePath)) != 0)
		{
			return data;
		}
	}
	return data;
}