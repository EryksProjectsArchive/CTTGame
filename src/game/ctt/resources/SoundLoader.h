//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/SoundLoader.h
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <core/String.h>
#include <core/List.h>
#include <core/Singleton.h>

#include <stdio.h>

class SoundLoader : public Singleton<SoundLoader>
{
private:
	List<SoundLoader *> m_loaders;
public:
	SoundLoader();
	virtual ~SoundLoader();

	virtual bool isFileValid(FilePath filePath);
	virtual void registerLoader(SoundLoader * loader);

	virtual SoundData * load(FilePath filePath);
};