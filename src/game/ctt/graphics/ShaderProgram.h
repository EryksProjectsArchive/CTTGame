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
private:
	GLint m_programId;
public:

	ShaderProgram();
	~ShaderProgram();

	void attachShader(Shader * shader);
};