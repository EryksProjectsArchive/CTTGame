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

#include <core/String.h>
#include <resources/CacheableResource.h>

class Texture : public CacheableResource
{
private:
	uint32 m_textureID;
	bool m_mipmaps;
public:
	Texture(const FilePath& filePath, bool mipmaps = false);
	~Texture();

	void destroy();

	bool load();

	bool isLoaded();

	friend class Renderer;
};