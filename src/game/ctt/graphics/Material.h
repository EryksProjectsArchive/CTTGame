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

class Material
{
private:
	Texture *m_texture;
	ShaderProgram * m_program;
public:
	Material();
	~Material();

	friend class Renderer;
};