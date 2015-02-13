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

#include "PNGImageLoader.h"
#include <io/fs/FileSystem.h>

#include <graphics/ImageData.h>

#include <core/Logger.h>

#include <png.h>

namespace PNG
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
		if (filePath.find(".png") != -1)
		{
			File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
			if (file->isLoaded())
			{
				//Allocate a buffer of 8 bytes, where we can put the file signature.
				png_byte pngsig[8];
				int32 is_png = 0;

				//Read the 8 bytes from the stream into the sig buffer.
				file->read(pngsig, 8, 1);

				//Let LibPNG check the sig. If this function returns 0, everything is OK.
				isValid = !png_sig_cmp(pngsig, 0, 8);

				FileSystem::get()->close(file);
			}
		}
		return isValid;
	}

	static void userReadData(png_structp png_ptr, png_bytep data, png_size_t length)
	{
		typedef struct {
			File *file;
		} File_Struct;

		File_Struct *file = (File_Struct*)png_get_io_ptr(png_ptr);

		file->file->read((int8*)data, length, 1);
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
			file->seek(8, SeekOrigin::Set);
			png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

			if (pngPtr) {
				png_infop infoPtr = png_create_info_struct(pngPtr);

				if (infoPtr) {
					png_infop end_info = png_create_info_struct(pngPtr);

					if (end_info)
					{
						png_set_read_fn(pngPtr, (png_voidp)&file, userReadData);
						if (!setjmp(png_jmpbuf(pngPtr))) {
							png_set_sig_bytes(pngPtr, 8);

							png_read_info(pngPtr, infoPtr);

							data->width = png_get_image_width(pngPtr, infoPtr);
							data->height = png_get_image_height(pngPtr, infoPtr);
							png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);
							switch (color_type) {
							case PNG_COLOR_TYPE_PALETTE:
								png_set_palette_to_rgb(pngPtr);
								data->format = EImageFormat::RGB;
								break;
							case PNG_COLOR_TYPE_RGB:
								data->format = EImageFormat::RGB;
								break;
							case PNG_COLOR_TYPE_RGB_ALPHA:
								data->format = EImageFormat::RGBA;
								break;
							}
							size_t rowbytes = png_get_rowbytes(pngPtr, infoPtr);

							data->pixels = new uint8[rowbytes * data->height];

							uint8** row_pointers = new uint8*[data->height];

							for (uint32 i = 0; i < data->height; ++i)
								row_pointers[i] = data->pixels + i * rowbytes;

							png_read_image(pngPtr, row_pointers);

							png_destroy_read_struct(&pngPtr, &infoPtr, &end_info);
							delete[] row_pointers;
						}
						else {
							Error("PNGImageLoader", "png error.");
							png_destroy_read_struct(&pngPtr, &infoPtr, &end_info);
						}
					}
					else {
						Error("PNGImageLoader", "Couldn't initialize png info struct.");
						png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
					}
				}
				else {
					Error("PNGImageLoader", "Couldn't initialize png info struct.");
					png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
				}
			}
			else {
				Error("PNGImageLoader", "Couldn't initialize png read struct.");
			}
			FileSystem::get()->close(file);
		}
		return data;
	}
};