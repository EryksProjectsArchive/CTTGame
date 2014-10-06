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

#include <core/String.h>
#include "Texture.h"
#include "renderer/Renderer.h"

#include <resources/ImageLoader.h>
#include <graphics/ImageData.h>

Texture::Texture(FilePath filePath, bool mipmaps)
	: m_textureID(-1), CacheableResource(filePath), m_mipmaps(mipmaps)
{
}

Texture::~Texture()
{

}

void Texture::destroy()
{
	if (glIsTexture(m_textureID))
	{
		glDeleteTextures(1, &m_textureID);
		m_textureID = -1;
	}
	m_isLoaded = false;
}

bool Texture::load()
{
	ImageData * data = ImageLoader::get()->load(m_filePath);
	if (data)
	{
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		unsigned int format = GL_RGB;
		switch (data->format)
		{
		case EImageFormat::BGR:
			format = GL_BGR;
			break;
		case EImageFormat::RGBA:			
			format = GL_RGBA;
			break;
		default:			
			format = GL_RGB;
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data->width, data->height, 0, format, GL_UNSIGNED_BYTE, data->pixels);

		if (m_mipmaps)
		{
			if (Renderer::glGenerateMipmap)
				Renderer::glGenerateMipmap(GL_TEXTURE_2D);
		}

		delete data;
		m_isLoaded = true;
		return true;
	}
	return false;
}

bool Texture::isLoaded()
{
	return m_isLoaded && glIsTexture(m_textureID);
}