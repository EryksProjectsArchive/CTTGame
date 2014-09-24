//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/sounds/wav/WAVsoundLoader.h
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#pragma once 

#include <Prerequisites.h>
#include <resources/SoundLoader.h>
#include <Windows.h>

namespace WAV
{
	class SoundLoader : public ::SoundLoader
	{
	private:
		struct WaveHeader
		{
			char ChunkID[4];
			long ChunkSize;
			char Format[4];
		};

		struct WaveInfoChunk
		{
			char ChunkID[4];
			unsigned int ChunkSize;
			unsigned short AudioFormat;
			unsigned short NumChannels;
			unsigned int SampleRate;
			unsigned int ByteRate;
			unsigned short BlockAlign;
			unsigned short BitsPerSample;
		};

		struct WaveDataChunk
		{
			char ChunkID[4];
			unsigned int ChunkSize;
			unsigned char *Data;
		};

		struct WaveFile
		{
			WaveHeader header;
			WaveInfoChunk info;
			WaveDataChunk data;
			// char * data (unknown size)
		};

	public:
		SoundLoader();
		~SoundLoader();

		bool isFileValid(FilePath filePath);
		SoundData * load(FilePath filePath);
	};
}

