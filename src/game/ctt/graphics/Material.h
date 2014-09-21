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

class Material
{
private:
	SharedPtr<Texture> m_texture;
	SharedPtr<ShaderProgram> m_program;

	DynString m_name;
public:
	Material(const DynString & name);
	~Material();

	DynString getName();

	friend class Renderer;
	friend class MaterialLib;
};