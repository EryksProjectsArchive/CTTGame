//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Texture.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

class Texture
{
private:
	unsigned int m_textureID;
public:
	Texture(char * filePath, bool mipmaps = false);
	~Texture();
};