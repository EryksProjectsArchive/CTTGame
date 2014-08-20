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
#include "Shader.h"

ShaderProgram::ShaderProgram()
{
	m_programId = Renderer::glCreateProgram();
	m_uniforms = 0;
	m_uniformsCount = 0;
}

ShaderProgram::~ShaderProgram()
{
	if (m_uniforms)
	{
		free(m_uniforms);
		m_uniforms = 0;
		m_uniformsCount = 0;
	}
}

void ShaderProgram::attachShader(Shader * shader)
{
	Renderer::glAttachShader(m_programId, shader->m_shaderId);
}

unsigned int ShaderProgram::getUniformLocation(const char *name)
{
	if (m_uniforms)
	{
		for (unsigned int i = 0; i < m_uniformsCount; ++i)
		{
			if (strcpy(m_uniforms[i].name, name))
			{
				return m_uniforms[i].location;
			}
		}
	}

	unsigned int location = Renderer::glGetUniformLocation(m_programId, name);
	if (location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION)
	{
		// Add new uniform
		++m_uniformsCount;

		if (!m_uniforms)
		{
			m_uniforms = (UniformData *)malloc(sizeof(UniformData));
		}
		else
		{
			m_uniforms = (UniformData *)realloc(m_uniforms, sizeof(UniformData) * m_uniformsCount);
		}

		strcpy(m_uniforms[m_uniformsCount - 1].name, name);
		m_uniforms[m_uniformsCount - 1].location = location;
		return location;
	}
	return -1;
}