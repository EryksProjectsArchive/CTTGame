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
/*
struct EImageCompreesion
{
	enum Compressed
	{
		NONE,
		DXT1,
		DXT3,
		DXT5
	};
};*/
struct ImageData
{
	unsigned char *pixels;
	unsigned int width;
	unsigned int height;
	EImageFormat::Type format;
//	EImageCompreesion::Compressed compressed;

	ImageData()
	{
		pixels = 0;
		width = 0;
		height = 0;
		format = EImageFormat::RGB;
//		compressed = EImageCompreesion::NONE;

	}

	~ImageData()
	{
		if (pixels)
		{
			delete[] pixels;
		}
	}
};