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

class Shader
{
protected:
	uint32 m_shaderId;
public:
	Shader(const char *source);
	virtual ~Shader();

	friend class ShaderProgram;
};