//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/WaveFile.h
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

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