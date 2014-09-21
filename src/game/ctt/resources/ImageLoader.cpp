//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/ImageLoader.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "ImageLoader.h"
#include <stdio.h>

ImageLoader::ImageLoader()
{
}

ImageLoader::~ImageLoader()
{
	for (ImageLoader * loader : m_loaders)	
		delete loader;
	
	m_loaders.clear();
}

bool ImageLoader::isFileValid(FilePath filePath)
{
	return false;
}

void ImageLoader::registerLoader(ImageLoader * loader)
{
	m_loaders.pushBack(loader);
}

ImageData * ImageLoader::load(FilePath filePath)
{
	ImageData * data = 0;
	for (ImageLoader *loader : m_loaders)
	{
		if (loader->isFileValid(filePath) && (data = loader->load(filePath)) != 0)
		{
			return data;
		}
	}
	return data;
}