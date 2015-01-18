//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Shader.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <core/String.h>

class Shader
{
protected:
	uint32 m_shaderId;
	FilePath m_sourcePath;
	uint8 m_isCompiled : 1;
public:
	Shader(const FilePath& source);
	virtual ~Shader();

	virtual bool compile() { return false;  }

	friend class ShaderProgram;
};