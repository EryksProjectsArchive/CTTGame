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
#include <io/fs/FileSystem.h>

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
			File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
			if (file->isLoaded())
			{
				char id[3] = { 0 };
				file->read(id, 2, 1);

				isValid = (id[0] == 'B' && id[1] == 'M');
				FileSystem::get()->close(file);
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

		File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
		if (file->isLoaded())
		{
			Magic magic = { 0 };
			file->read(&magic, sizeof(Magic), 1);

			Header header = { 0 };
			file->read(&header.size, sizeof(Header), 1);

			// header.id - we don't have to check id here it's checked in parent loader via isFileValid method
			if (header.size > 0)
			{
				InfoHeader infoHeader = { 0 };
				file->read(&infoHeader, sizeof(InfoHeader), 1);
	
				// Validate file we support 24 bits and no compression atm
				if (infoHeader.bitCount == 24 && infoHeader.compression == 0)
				{
					data = new ImageData();
					data->width = infoHeader.width;
					data->height = abs(infoHeader.height);

					unsigned int size = data->width * data->height * 3;
					data->pixels = new unsigned char[size];

					file->seek(header.offBits, SeekOrigin::Set);
					file->read(data->pixels, sizeof(unsigned char), size);

					data->format = EImageFormat::BGR;
				}
				else {
					Error("BMPImageLoader", "Unsupported image. (%s, BIT CNT: %d, COMPRESS: %d)", filePath.get(), infoHeader.bitCount, infoHeader.compression);
				}
			}
			else {
				Error("BMPImageLoader", "Cannot load image. Header size is not valid. (%s, %d)", filePath.get(), header.size);
			}

			FileSystem::get()->close(file);
		}

		return data;
	}
};