//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/images/dds/DDSImageLoader.h
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <resources/ImageLoader.h>
#include <Windows.h>

namespace DDS
{

	class ImageLoader : public ::ImageLoader
	{
	private:
#define FOURCC_DXT1 MAKEFOURCC('D', 'X', 'T', '1')
#define FOURCC_DXT3 MAKEFOURCC('D', 'X', 'T', '3')
#define FOURCC_DXT5 MAKEFOURCC('D', 'X', 'T', '5')

		void flipComplexAlphaBlock(uint8 *data);
		void flipDxt1(uint8* data, uint32 count);
		void flipDxt3(uint8* data, uint32 count);
		void flipDxt5(uint8* data, uint32 count);

	public:
		ImageLoader();
		~ImageLoader();

		bool isFileValid(const FilePath& filePath);
		ImageData * load(const FilePath& filePath);
	};
};