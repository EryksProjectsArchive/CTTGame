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

Texture::Texture(const FilePath& filePath, bool mipmaps)
	: m_textureID(-1), CacheableResource(filePath), m_mipmaps(mipmaps), m_width(0), m_height(0)
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
		m_width = data->width;
		m_height = data->height;

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		uint32 format = GL_RGB;
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
		
		switch (data->compressed)
		{
		case EImageCompreesion::DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			Renderer::glCompressedTexImage2D(GL_TEXTURE_2D, 0, format, data->width, data->height, 0, ((data->width + 3) / 4) * ((data->height + 3) / 4) * 8, data->pixels);
			break;
		case EImageCompreesion::DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			Renderer::glCompressedTexImage2D(GL_TEXTURE_2D, 0, format, data->width, data->height, 0, ((data->width + 3) / 4) * ((data->height + 3) / 4) * 16, data->pixels);
			break;
		case EImageCompreesion::DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			Renderer::glCompressedTexImage2D(GL_TEXTURE_2D, 0, format, data->width, data->height, 0, ((data->width + 3) / 4) * ((data->height + 3) / 4) * 16, data->pixels);
			break;
		default:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data->width, data->height, 0, format, GL_UNSIGNED_BYTE, data->pixels);
			break;
		}
		
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

uint32 Texture::width()
{
	return m_width;
}

uint32 Texture::height()
{
	return m_height;
}