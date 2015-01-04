//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: sound/SoundData.h
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#pragma once

struct SoundData
{
	uint8 *data;
	uint32 format;
	uint64 size;
	uint32 sampleRate;

	SoundData()
	{
		data = 0;
		format = 0;
		size = 0;
		sampleRate = 0;
	}

	~SoundData()
	{
		if (data)
		{
			delete[] data;
		}
	}
};