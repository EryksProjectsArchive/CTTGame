//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/images/bmp/BMPImageLoader.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <resources/ImageLoader.h>
#include <Windows.h>

namespace BMP
{
	class ImageLoader : public ::ImageLoader
	{
	private:
		struct Magic
		{
			unsigned char id[2];  // id must be "BM"
		};

		struct Header
		{			
			unsigned int size; // size of the whole bmp file
			unsigned int reserved; // must be 0
			unsigned int offBits; 
		};

		struct InfoHeader
		{
			unsigned long size;
			long width;
			long height;
			unsigned short planes;
			unsigned short bitCount;
			unsigned long compression;
			unsigned long sizeImage;
			long xPelsPerMeter;
			long yPelsPerMeter;
			unsigned long clrUsed;
			unsigned long clrImportant;
		};
	public:
		ImageLoader();
		~ImageLoader();

		bool isFileValid(const FilePath& filePath);
		ImageData * load(const FilePath& filePath);
	};
};