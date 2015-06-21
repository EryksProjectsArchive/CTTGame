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
#include <core/List.h>
#include <resources/CacheableResource.h>

class Material : public CacheableResource
{
private:
	struct TextureData
	{
		DynString m_name;
		FilePath m_path;
		Texture* m_texture;
		uint8 m_mipmaps : 1;

		TextureData()
		{
			m_texture = 0;
		}

		TextureData(const TextureData& data)
		{
			m_name = data.m_name;
			m_path = data.m_path;
			m_texture = data.m_texture;
			m_mipmaps = data.m_mipmaps;
		}

		~TextureData() {}
	};
	List<TextureData*> m_textures;
	ShaderProgram* m_program;
	uint8 m_hasVertexShader : 1;
	uint8 m_hasFragmentShader : 1;
	uint8 m_isLoaded : 1;
	uint8 m_wireframe : 1;
	FilePath m_vertexShaderName;
	FilePath m_fragmentShaderName;
	DynString m_name;
public:
	Material(const DynString& name, const FilePath& file);
	~Material();

	void destroy() override;
	bool load() override;

	void addTexture(const DynString& name, const FilePath& path, bool mipmaps);

	friend class Renderer;
	friend class DeferredRendering;
	friend class DynamicShadowsPass;
	friend class MaterialLib;
};