//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/images/bmp/BMPImageLoader.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "BMPImageLoader.h"
#include <stdio.h>

#include <graphics/ImageData.h>

#include <core/Logger.h>

namespace BMP
{
	ImageLoader::ImageLoader()
	{

	}

	ImageLoader::~ImageLoader()
	{

	}

	bool ImageLoader::isFileValid(const FilePath& filePath)
	{
		bool isValid = false;
		if (filePath.find(".bmp") != -1)
		{
			FILE * fp = fopen(filePath, "rb");
			if (fp)
			{
				char id[3] = { 0 };
				fread(id, sizeof(char), 2, fp);

				isValid = (id[0] == 'B' && id[1] == 'M');
				fclose(fp);
			}
		}
		return isValid;
	}

	ImageData * ImageLoader::load(const FilePath& filePath)
	{
		// Recursive loading
		ImageData *data = 0;
		if (data = ::ImageLoader::load(filePath))
			return data;

		FILE *fp = fopen(filePath, "rb");
		if (fp)
		{
			Magic magic = { 0 };
			fread(&magic, sizeof(Magic), 1, fp);

			Header header = { 0 };
			fread(&header.size, sizeof(Header), 1, fp);

			// header.id - we don't have to check id here it's checked in parent loader via isFileValid method
			if (header.size > 0)
			{
				InfoHeader infoHeader = { 0 };
				fread(&infoHeader, sizeof(InfoHeader), 1, fp);
	
				// Validate file we support 24 bits and no compression atm
				if (infoHeader.bitCount == 24 && infoHeader.compression == 0)
				{
					data = new ImageData();
					data->width = infoHeader.width;
					data->height = abs(infoHeader.height);

					unsigned int size = data->width * data->height * 3;
					data->pixels = new unsigned char[size];

					fseek(fp, header.offBits, SEEK_SET);
					fread(data->pixels, sizeof(unsigned char), size, fp);

					data->format = EImageFormat::BGR;
				}
				else {
					Error("BMPImageLoader", "Unsupported image. (%s, BIT CNT: %d, COMPRESS: %d)", filePath.get(), infoHeader.bitCount, infoHeader.compression);
				}
			}
			else {
				Error("BMPImageLoader", "Cannot load image. Header size is not valid. (%s, %d)", filePath.get(), header.size);
			}

			fclose(fp);
		}

		return data;
	}
};