//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/images/jpeg/JPEGImageLoader.cpp
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#include "JPEGImageLoader.h"
#include <io/fs/FileSystem.h>

extern "C" {  // stupid JPEG library
#include <jpeglib.h>
}

#include <graphics/ImageData.h>

#include <core/Logger.h>

namespace JPEG
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
		if (filePath.find(".jpg") != -1)
		{
			File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
			if (file->isLoaded())
			{
				int8 id[5] = { 0 };
				file->seek(6, SeekOrigin::Set);
				file->read(id, 4, 1);
				isValid = (id[0] == 'E' && id[1] == 'x' && id[2] == 'i' && id[3] == 'f') || (id[0] == 'J' && id[1] == 'F' && id[2] == 'I' && id[3] == 'F');
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
			uint32 length;
			jpeg_decompress_struct cinfo;
			data = new ImageData;
			jpeg_error_mgr jerr;
			uint8 *tmp_data;
			JSAMPROW row_pointer;

			cinfo.err = jpeg_std_error(&jerr);

			jpeg_create_decompress(&cinfo);

			file->seek(0, SeekOrigin::End);
			length = file->tell();
			file->rewind();
			tmp_data = new uint8[length + 1];
			file->read(tmp_data, length, 1);
			tmp_data[length] = '\0';

			jpeg_mem_src(&cinfo, tmp_data, length);

			jpeg_read_header(&cinfo, TRUE);

			jpeg_start_decompress(&cinfo);

			data->height = cinfo.output_height;
			data->width = cinfo.output_width;
			data->format = cinfo.output_components == 4 ? EImageFormat::RGBA : EImageFormat::RGB;

			data->pixels = new uint8[data->width * data->height * cinfo.output_components];

			while (cinfo.output_scanline < cinfo.output_height)
			{
				row_pointer = (JSAMPROW)&data->pixels[(cinfo.output_height - 1 - cinfo.output_scanline) * data->width * cinfo.output_components];
				jpeg_read_scanlines(&cinfo, &row_pointer, 1);
			}

			jpeg_finish_decompress(&cinfo);

			jpeg_destroy_decompress(&cinfo);

			delete[] tmp_data;

			FileSystem::get()->close(file);

		}
		return data;
	}
};