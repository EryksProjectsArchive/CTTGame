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

	bool ImageLoader::isFileValid(FilePath filePath)
	{
		bool isValid = false;
		if (filePath.find(".jpg") != -1)
		{
			File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
			if (file->isLoaded())
			{
//				char id[3] = { 0 };
//				file->read(id, 2, 1);

				isValid = true;

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
			unsigned long length;
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
			tmp_data = new unsigned char[length + 1];
			file->read(tmp_data, length, 1);
			tmp_data[length] = '\0';

			jpeg_mem_src(&cinfo, tmp_data, length);

			jpeg_read_header(&cinfo, TRUE);

			jpeg_start_decompress(&cinfo);

			data->height = cinfo.output_height;
			data->width = cinfo.output_width;
			data->format = cinfo.output_components == 4 ? EImageFormat::RGBA : EImageFormat::RGB;

			data->pixels = new unsigned char[data->width * data->height * cinfo.output_components];

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