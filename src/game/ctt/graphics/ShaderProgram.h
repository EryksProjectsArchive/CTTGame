//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ShaderProgram.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

struct UniformData
{
	char name[32];
	unsigned int location;
};

class ShaderProgram
{
protected:
	unsigned int m_programId;

	UniformData * m_uniforms;
	unsigned int m_uniformsCount;
public:
	ShaderProgram();
	~ShaderProgram();

	void attachShader(Shader * shader);

	unsigned int getUniformLocation(const char *name);

	friend class Renderer;
};