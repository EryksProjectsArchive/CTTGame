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

class Texture;
class Shader;

class Material
{
private:
	Texture *m_texture;
	Shader *m_vertexShader;
	Shader *m_pixelShader;
public:
	Material();
	~Material();
};