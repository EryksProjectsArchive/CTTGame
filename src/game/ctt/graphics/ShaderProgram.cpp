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

#include <core/Logger.h>

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
	m_shaders.pushBack(shader);	
}

void ShaderProgram::link()
{
	for (auto shader : m_shaders)
	{
		Renderer::glAttachShader(m_programId, shader->m_shaderId);
	}

	Renderer::glLinkProgram(m_programId);

	GLint success = 0;
	Renderer::glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		Renderer::glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		char *errorLog = new char[maxLength + 1];

		Renderer::glGetProgramInfoLog(m_programId, maxLength, &maxLength, errorLog);

		Error("program", "Link error: %s", errorLog);

		delete[]errorLog;
	}
}

unsigned int ShaderProgram::getUniformLocation(const char *name)
{
	return Renderer::glGetUniformLocation(m_programId, name);
	/*
	if (m_uniforms)
	{
		for (unsigned int i = 0; i < m_uniformsCount; ++i)
		{
			if (!strcmp(m_uniforms[i].name, name))
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
	return -1;*/
}