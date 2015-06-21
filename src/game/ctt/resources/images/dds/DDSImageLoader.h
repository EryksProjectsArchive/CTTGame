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

#define FOURCC_DXT1 MAKEFOURCC('D', 'X', 'T', '1')
#define FOURCC_DXT3 MAKEFOURCC('D', 'X', 'T', '3')
#define FOURCC_DXT5 MAKEFOURCC('D', 'X', 'T', '5')

	class ImageLoader : public ::ImageLoader
	{

	public:
		ImageLoader();
		~ImageLoader();

		bool isFileValid(FilePath filePath);
		ImageData * load(FilePath filePath);
	};
};