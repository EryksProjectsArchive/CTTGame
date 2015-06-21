//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/images/dds/DDSImageLoader.cpp
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#include "DDSImageLoader.h"
#include <io/fs/FileSystem.h>

#include <graphics/ImageData.h>

#include <core/Logger.h>

namespace DDS
{
	ImageLoader::ImageLoader()
	{

	}

	ImageLoader::~ImageLoader()
	{

	}

	bool ImageLoader::isFileValid(FilePath filePath)
	{
		bool isValid = false;
		if (filePath.find(".dds") != -1)
		{
			File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
			if (file->isLoaded())
			{
				char id[5] = { 0 };
				file->read(id, 4, 1);

				isValid = (id[0] == 'D' && id[1] == 'D' && id[2] == 'S' && id[3] == ' ');

				FileSystem::get()->close(file);
			}
		}
		return isValid;
	}

	ImageData * ImageLoader::load(FilePath filePath)
	{
		// Recursive loading
		ImageData *data = 0;
		if (data = ::ImageLoader::load(filePath))
			return data;

		File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
		if (file->isLoaded())
		{
			data = new ImageData;
			/*
			//Get the descriptor.
			uint32 FourCC;
			file->seek(84, SeekOrigin::Set);
			file->read(&FourCC, sizeof(uint32), 1);

			uint32 LinearSize;
			file->seek(20, SeekOrigin::Set);
			file->read(&LinearSize, sizeof(uint32), 1);

			uint32 MipMapCount;
			file->seek(28, SeekOrigin::Set);
			file->read(&MipMapCount, sizeof(uint32), 1);

			uint32 Width;
			file->seek(16, SeekOrigin::Set);
			file->read(&Width, sizeof(uint32), 1);

			uint32 Height;
			file->seek(12, SeekOrigin::Set);
			file->read(&Height, sizeof(uint32), 1);

			int32 Factor;
			int32 Size;

			switch (FourCC)
			{
			case FOURCC_DXT1:
				data->format = EImageFormat::RGBA;
				data->compressed = EImageCompreesion::DXT1;
				Factor = 2;
				break;

			case FOURCC_DXT3:
				data->format = EImageFormat::RGBA;
				data->compressed = EImageCompreesion::DXT3;
				Factor = 4;
				break;

			case FOURCC_DXT5:
				data->format = EImageFormat::RGBA;
				data->compressed = EImageCompreesion::DXT5;
				Factor = 4;
				break;

			default:
				return NULL;
			}

			Size = (MipMapCount > 1) ? (LinearSize * Factor) : LinearSize;
			data->pixels = new uint8[Size];

			data->width = Width;
			data->height = Height;

			file->seek(128, SeekOrigin::Set);
			file->read(data->pixels, Size, 1);


			//file->read(data->pixels, bufsize, 1);
			*/
			/* close the file pointer */
			FileSystem::get()->close(file);
		}
		return data;
	}
};