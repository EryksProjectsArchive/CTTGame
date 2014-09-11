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

Material::Material()
{
	m_program = 0;
	m_texture = new Texture("../../data/textures/testbitmap.bmp", true);
	m_texture->acquire();
}

Material::~Material()
{
	if (m_texture)
		m_texture->free();
}