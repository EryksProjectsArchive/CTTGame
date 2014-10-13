//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Material.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <core/DynString.h>
#include <core/SharedPtr.h>
#include <resources/CacheableResource.h>

class Material : public CacheableResource
{
private:
	Texture* m_texture;
	ShaderProgram* m_program;
	uint8 m_hasTexture : 1;
	uint8 m_hasVertexShader : 1;
	uint8 m_hasFragmentShader : 1;
	uint8 m_isLoaded : 1;
	uint8 m_mipmaps;
	FilePath m_textureName;
	FilePath m_vertexShaderName;
	FilePath m_fragmentShaderName;
	DynString m_name;
public:
	Material(const DynString& name, const FilePath& file);
	~Material();

	void destroy() override;
	bool load() override;

	friend class Renderer;
	friend class MaterialLib;
};