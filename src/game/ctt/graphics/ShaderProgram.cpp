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

	for (auto shader : m_shaders)
		delete shader;

	m_shaders.clear();
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

		Error("program", "Linker error: %s", errorLog);

		delete[]errorLog;
	}

	for (auto shader : m_shaders)
	{
		Renderer::glDetachShader(m_programId, shader->m_shaderId);
	}
}

unsigned int ShaderProgram::getUniformLocation(const char *name)
{
	if (m_uniforms)
	{
		for (unsigned int i = 0; i < m_uniformsCount; ++i)
		{
			if (!strcmp(m_uniforms[i].name, name))
			{
				//Info("shader program", "Cached uniform found. Name: '%s', Location: '%d'", name, m_uniforms[i].location);
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

unsigned int ShaderProgram::getAttributeLocation(const char *name)
{
	if (m_attributes)
	{
		for (unsigned int i = 0; i < m_attributesCount; ++i)
		{
			if (!strcmp(m_attributes[i].name, name))
			{
				//Info("shader program", "Cached attribute found. Name: '%s', Location: '%d'", name, m_attributes[i].location);
				return m_attributes[i].location;
			}
		}
	}

	unsigned int location = Renderer::glGetAttribLocation(m_programId, name);
	if (location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION)
	{
		// Add new attribute
		++m_attributesCount;

		AttributeData * attributes = m_attributes;

		m_attributes = (AttributeData *)realloc(attributes, sizeof(AttributeData) * m_attributesCount);

		strcpy(m_attributes[m_attributesCount - 1].name, name);
		m_attributes[m_attributesCount - 1].location = location;
		return location;
	}
	return -1;
}
