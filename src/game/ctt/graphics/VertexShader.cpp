//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/VertexShader.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "VertexShader.h"

#include <stdio.h>
#include <core/Logger.h>

#include "renderer/Renderer.h"

VertexShader::VertexShader(const char * source) : Shader(source)
{
	FILE *shaderFile = fopen(source, "r");
	printf("%s\n", source);
	if (shaderFile)
	{
		m_shaderId = Renderer::glCreateShader(GL_VERTEX_SHADER);

		char * shaderSource = 0;
		unsigned int shaderLength = 0;

		fseek(shaderFile, 0, SEEK_END);
		shaderLength = ftell(shaderFile);
		rewind(shaderFile);
		shaderSource = new char[shaderLength];
		memset(shaderSource, 0, shaderLength);
		fread(shaderSource, sizeof(char), shaderLength, shaderFile);
		shaderSource[shaderLength - 1] = '\0';

		Info("vertShader", "Vertex Shader: %s", shaderSource);

		Renderer::glShaderSource(m_shaderId, 1, (const GLchar **)&shaderSource, (const GLint *)&shaderLength);
		Renderer::glCompileShader(m_shaderId);

		delete[] shaderSource;
		fclose(shaderFile);
	}
}

VertexShader::~VertexShader()
{
	if (m_shaderId)
	{
		Renderer::glDeleteShader(m_shaderId);
		m_shaderId = 0;
	}
}