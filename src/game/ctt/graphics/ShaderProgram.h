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

#include "Shader.h"

class ShaderProgram
{
protected:
	unsigned int m_programId;
public:
	ShaderProgram();
	~ShaderProgram();

	void attachShader(Shader * shader);

	friend class Renderer;
};