//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Material.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <resources/CacheableResource.h>
#include <core/Logger.h>
#include "Material.h"
#include "Texture.h"

#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"

Material::Material(const DynString name, const FilePath file)
	: CacheableResource(file),
	  m_name(name),
	  m_texture(0),
	  m_program(0),
	  m_hasTexture(0),
	  m_hasVertexShader(0),
	  m_hasFragmentShader(0),
	  m_isLoaded(0)
{
}


Material::~Material()
{
	// NOTE: I don't remember if it's necessary here.
	if (m_texture)
	{
		m_texture->free();
		delete m_texture;
		m_texture = 0;
	}

	if (m_program)
	{
		delete m_program;
		m_program = 0;
	}
}

void Material::destroy()
{
	if (m_texture)
	{
		m_texture->free();
		delete m_texture;
		m_texture = 0;
	}

	if (m_program)
	{
		delete m_program;
		m_program = 0;
	}
}

bool Material::load()
{
	if (!m_isLoaded)
	{
		// TODO: TextureLib
		if (m_hasTexture)
		{
			m_texture = new Texture(FilePath("../../data/textures/%s", *m_textureName), m_mipmaps ? true : false);
			m_texture->acquire(); // Acquire texture into material - we are calling free when material is being removed
		}

		m_program = new ShaderProgram();

		if (m_hasVertexShader)
		{
			m_program->attachShader(new VertexShader(FilePath("../../data/shaders/%s.vert", *m_vertexShaderName)));
		}

		if (m_hasFragmentShader)
		{
			m_program->attachShader(new FragmentShader(FilePath("../../data/shaders/%s.frag",*m_fragmentShaderName)));
		}

		m_program->link();
		m_isLoaded = 1;
		return true;
	}
	return false;
}
