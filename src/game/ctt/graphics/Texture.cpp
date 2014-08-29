//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Texture.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Texture.h"
#include "renderer/Renderer.h"


Texture::Texture(char * filePath, bool mipmaps)
{
	glGenTextures(1, &m_textureID);
}

Texture::~Texture()
{

}