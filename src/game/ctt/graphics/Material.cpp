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
	m_program = 0;
	m_texture = 0;
}

Material::~Material()
{
	if (m_texture)
		m_texture->free();

	if (m_program)
	{
		delete m_program;
		m_program = 0;
	}
}

DynString Material::getName()
{
	return m_name;
}