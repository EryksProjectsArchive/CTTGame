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

#include <graphics/Imagedata.h>

#include <core/Logger.h>

namespace DDS
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
		if (filePath.find(".dds") != -1)
		{
			File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
			if (file->isLoaded())
			{
				int8 id[5] = { 0 };
				file->read(id, 4, 1);

				isValid = (id[0] == 'D' && id[1] == 'D' && id[2] == 'S' && id[3] == ' ');

				FileSystem::get()->close(file);
			}
		}
		return isValid;
	}

	void ImageLoader::flipComplexAlphaBlock(uint8 *data)
	{
		uint8 tmp[3];
		data += 2; 

		memcpy(tmp, data, 3);
		memcpy(data, data + 3, 3);
		memcpy(data + 3, tmp, 3);

		uint8 tmps[2];

		tmps[0] = (data[0] | (data[1] += 8)) & 0xfff;
		tmps[1] = ((data[1] += 4) | (data[2] << 4)) & 0xfff;

		data[0] = tmps[1];
		data[1] = (tmps[1] += 8) | (tmps[0] << 4);
		data[2] = tmps[0] += 4;

		tmps[0] = (data[3] | (data[4] += 8)) & 0xfff;
		tmps[1] = ((data[4] += 4) | (data[5] << 4)) & 0xfff;

		data[3] = tmps[1];
		data[4] = (tmps[1] += 8) | (tmps[0] << 4);
		data[5] = tmps[0] += 4;
	}

	void ImageLoader::flipDxt1(uint8* data, uint32 count)
	{
		uint32 i;

		for (i = 0; i < count; ++i) {
			uint8 tmp;

			tmp = data[4];
			data[4] = data[7];
			data[7] = tmp;

			tmp = data[5];
			data[5] = data[6];
			data[6] = tmp;

			data += 8;
		}
	}

	void ImageLoader::flipDxt3(uint8* data, uint32 count)
	{
		for (uint32 i = 0; i < count; ++i) 
		{
			uint8 tmp;

			tmp = data[0];
			data[0] = data[3];
			data[3] = tmp;

			tmp = data[1];
			data[1] = data[2];
			data[2] = tmp;

			for (uint32 j = 0; j < count; ++j) 
			{
				tmp = data[12];
				data[12] = data[15];
				data[15] = tmp;

				tmp = data[13];
				data[13] = data[14];
				data[14] = tmp;

				data += 16;
			}
			data += 16; 
		}
	}

	void ImageLoader::flipDxt5(uint8* data, uint32 count)
	{
		for (uint32 i = 0; i < count; ++i) 
		{
			flipComplexAlphaBlock(data);

			for (uint32 j = 0; j < count; ++j) 
			{
				uint8 tmp;

				tmp = data[12];
				data[12] = data[15];
				data[15] = tmp;

				tmp = data[13];
				data[13] = data[14];
				data[14] = tmp;

				data += 16;
			}
			data += 16; 
		}
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
			data = new ImageData;
			uint32 numXBlocks, numYBlocks, lineSize, height, width, linearSize, mipMapCount, fourCC;
			int32 size;
			uint8 *runner, *top, *bottom, *temp;

			file->seek(12, SeekOrigin::Set);
			file->read(&height, sizeof(uint32), 1);

			file->read(&width, sizeof(uint32), 1);

			file->read(&linearSize, sizeof(uint32), 1);

			file->seek(28, SeekOrigin::Set);
			file->read(&mipMapCount, sizeof(uint32), 1);

			file->seek(84, SeekOrigin::Set);
			file->read(&fourCC, sizeof(uint32), 1);

			size = mipMapCount > 1 ? linearSize * 2 : linearSize;
			data->pixels = new uint8[size];

			data->width = width;
			data->height = height;

			file->seek(128, SeekOrigin::Set);
			file->read(data->pixels, 1, size);

			numXBlocks = (data->width + 3) / 4;
			numYBlocks = (data->height + 3) / 4;

			switch (fourCC)
			{
			case FOURCC_DXT1:
				lineSize = numXBlocks * 8;
				temp = new uint8[lineSize];

				data->format = EImageFormat::RGBA;
				data->compressed = EImageCompreesion::DXT1;
				runner = data->pixels;
				for (uint32 z = 0; z < 2; ++z) {
					top = runner;
					bottom = runner + (numYBlocks - 1)*lineSize;

					for (uint32 y = 0; y < numYBlocks / 2; ++y) {
						memcpy(temp, top, lineSize);
						memcpy(top, bottom, lineSize);
						memcpy(bottom, temp, lineSize);

						flipDxt1(top, numXBlocks);
						flipDxt1(bottom, numXBlocks);

						top += lineSize;
						bottom -= lineSize;
					}

					if (numYBlocks % 2 != 0)
						flipDxt1(top, numXBlocks);

					runner += lineSize * numYBlocks;
				}
				delete[] temp;
				break;

			case FOURCC_DXT3:
				lineSize = numXBlocks * 16;
				temp = new uint8[lineSize];

				data->format = EImageFormat::RGBA;
				data->compressed = EImageCompreesion::DXT3;
				runner = data->pixels;
				for (uint32 z = 0; z < 2; ++z) {
					top = runner;
					bottom = runner + (numYBlocks - 1)*lineSize;

					for (uint32 y = 0; y < numYBlocks / 2; ++y) {
						memcpy(temp, top, lineSize);
						memcpy(top, bottom, lineSize);
						memcpy(bottom, temp, lineSize);

						flipDxt3(top, numXBlocks);
						flipDxt3(bottom, numXBlocks);

						top += lineSize;
						bottom -= lineSize;
					}

					if (numYBlocks % 2 != 0)
						flipDxt3(top, numXBlocks);

					runner += lineSize * numYBlocks;
				}
				delete[] temp;
				break;

			case FOURCC_DXT5:
				lineSize = numXBlocks * 16;
				temp = new uint8[lineSize];

				data->format = EImageFormat::RGBA;
				data->compressed = EImageCompreesion::DXT5;
				runner = data->pixels;
				for (uint32 z = 0; z < 2; ++z) {
					top = runner;
					bottom = runner + (numYBlocks - 1)*lineSize;

					for (uint32 y = 0; y < numYBlocks / 2; ++y) {
						memcpy(temp, top, lineSize);
						memcpy(top, bottom, lineSize);
						memcpy(bottom, temp, lineSize);

						flipDxt5(top, numXBlocks);
						flipDxt5(bottom, numXBlocks);

						top += lineSize;
						bottom -= lineSize;
					}

					if (numYBlocks % 2 != 0)
						flipDxt5(top, numXBlocks);

					runner += lineSize * numYBlocks;
				}
				delete[] temp;
				break;

			default:
				return NULL;
			}

			FileSystem::get()->close(file);
		}
		return data;
	}
};