//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ShaderProgram.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "ShaderProgram.h"
#include "renderer/Renderer.h"

ShaderProgram::ShaderProgram()
{
	m_programId = Renderer::glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	
}

void ShaderProgram::attachShader(Shader * shader)
{
	Renderer::glAttachShader(m_programId, shader->m_shaderId);
}