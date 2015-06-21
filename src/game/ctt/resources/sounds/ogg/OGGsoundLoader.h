//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/sounds/ogg/OGGsoundLoader.h
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#pragma once 

#include <Prerequisites.h>
#include <resources/SoundLoader.h>
#include <Windows.h>

#include <ogg/ogg.h>

namespace OGG
{
	class SoundLoader : public ::SoundLoader
	{
	private:
		static uint32 fileRead(void* buffer, uint32 size, uint32 n, void* opaque);
		static int    fileSeek(void* opaque, ogg_int64_t offset, int whence);
		static int    fileClose(void* opaque);
		static long   fileTell(void* opaque);

	public:
		SoundLoader();
		~SoundLoader();

		bool isFileValid(const FilePath& filePath);
		SoundData * load(const FilePath& filePath);
	};
}

