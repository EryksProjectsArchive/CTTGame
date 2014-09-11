//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/ImageLoader.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <core/String.h>
#include <core/List.h>

#include <stdio.h>

class ImageLoader
{
private:
	List<ImageLoader *> m_loaders;
public:
	ImageLoader();
	virtual ~ImageLoader();

	virtual bool isFileValid(FilePath filePath);
	virtual void registerLoader(ImageLoader * loader);

	virtual ImageData * load(FilePath filePath);

	static ImageLoader * get();
};