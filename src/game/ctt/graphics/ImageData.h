//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ImageData.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

struct EImageFormat
{
	enum Type
	{
		RGB,
		BGR,
		RGBA
	};
};

struct ImageData
{
	unsigned char *pixels;
	unsigned int width;
	unsigned int height;
	EImageFormat::Type format;

	ImageData()
	{
		pixels = 0;
		width = 0;
		height = 0;
		format = EImageFormat::RGB;
	}

	~ImageData()
	{
		if (pixels)
		{
			delete[] pixels;
		}
	}
};