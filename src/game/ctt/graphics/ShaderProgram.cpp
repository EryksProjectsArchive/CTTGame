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

#include <core/hashing/JenkinsHash.h>

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

	for (Shader* shader : m_shaders)
		delete shader;

	m_shaders.clear();
}

void ShaderProgram::attachShader(Shader * shader)
{
	if (!shader)
	{
		Error("ShaderProgram", "Trying to add non existing shader.");
		return;
	}

	// Compile shader
	if (!shader->compile())
	{
		Error("ShaderProgram", "Unable to compile shader.");
		return;
	}

	m_shaders.pushBack(shader);	
}

void ShaderProgram::begin()
{
	Renderer::glUseProgram(m_programId);
}

void ShaderProgram::end()
{

}

bool ShaderProgram::isValid()
{
	return Renderer::glIsProgram(m_programId) != 0;
}

bool ShaderProgram::link()
{
	if (!m_shaders.size())
	{
		Error("ShaderProgram", "Unable to link program. No shaders attached.");
		return false;
	}

	bool success = true;

	for (auto shader : m_shaders)
	{
		Renderer::glAttachShader(m_programId, shader->m_shaderId);
	}

	Renderer::glLinkProgram(m_programId);

	GLint params = 0;
	Renderer::glGetProgramiv(m_programId, GL_LINK_STATUS, &params);
	if (params == GL_FALSE)
	{
		GLint maxLength = 0;
		Renderer::glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

		char *errorLog = new char[maxLength + 1];
		Renderer::glGetProgramInfoLog(m_programId, maxLength, &maxLength, errorLog);
		errorLog[maxLength] = '\0';

		Error("ShaderProgram", "Linker error:");

		char *lineBuffer = errorLog;
		uint32 startIndex = 0;
		for (uint32 i = 0; i < strlen(errorLog); ++i)
		{
			if (errorLog[i] == '\n' || errorLog[i] == '\0')
			{
				uint32 length = (i - startIndex) + 1;
				char *line = new char[length];
				memcpy(line, lineBuffer + startIndex, length - 1);
				line[length - 1] = '\0';
				Error("ShaderProgram", line);
				startIndex = i + 1;
				delete[]line;
			}
		}

		delete[]errorLog;
		success = false;
	}

	for (auto shader : m_shaders)
	{
		Renderer::glDetachShader(m_programId, shader->m_shaderId);
	}
	return success;
}

unsigned int ShaderProgram::getUniformLocation(const char *name)
{
	uint32 hashName = JenkinsHash().encode(name, strlen(name));

	if (m_uniforms)
	{
		for (unsigned int i = 0; i < m_uniformsCount; ++i)
		{
			if (m_uniforms[i].name == hashName)
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

		m_uniforms[m_uniformsCount - 1].name = hashName;
		m_uniforms[m_uniformsCount - 1].location = location;
		return location;
	}
	return -1;
}

unsigned int ShaderProgram::getAttributeLocation(const char *name)
{
	uint32 hashName = JenkinsHash().encode(name, strlen(name));

	if (m_attributes)
	{
		for (unsigned int i = 0; i < m_attributesCount; ++i)
		{
			if (m_attributes[i].name == hashName)
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

		m_attributes[m_attributesCount - 1].name = hashName;
		m_attributes[m_attributesCount - 1].location = location;
		return location;
	}
	return -1;
}
