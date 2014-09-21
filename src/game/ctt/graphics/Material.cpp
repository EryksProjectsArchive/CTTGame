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

#include "Material.h"
#include "Texture.h"

#include "ShaderProgram.h"

Material::Material(const DynString & name)
{
	m_name = name;
}

Material::~Material()
{
	if (!m_texture.isNull())
		m_texture->free();
}

DynString Material::getName()
{
	return m_name;
}