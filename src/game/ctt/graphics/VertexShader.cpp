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

		Renderer::glShaderSource(m_shaderId, 1, (const GLchar **)&shaderSource, (const GLint *)&shaderLength);
		Renderer::glCompileShader(m_shaderId);

		GLint success = 0;
		Renderer::glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			Renderer::glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			char *errorLog = new char[maxLength + 1];

			Renderer::glGetShaderInfoLog(m_shaderId, maxLength, &maxLength, errorLog);
			errorLog[maxLength] = '\0';

			Error("shader", "Compilation error (%s):", source);

			char *lineBuffer = errorLog;
			uint32 startIndex = 0;
			for (uint32 i = 0; i < strlen(errorLog); ++i)
			{
				if (errorLog[i] == '\n' || errorLog[i] == '\0')
				{
					uint32 length = (i - startIndex);
					char *line = new char[length];
					memcpy(line, lineBuffer + startIndex, length - 1);
					line[length - 1] = '\0';
					Error("shader", line);
					startIndex = i + 1;
					delete[]line;
				}
			}

			delete[]errorLog;

			//Provide the infolog in whatever manor you deem best.
			//Exit with failure.
			Renderer::glDeleteShader(m_shaderId); //Don't leak the shader.
		}
		else {
			Debug("shader", "Compilation success '%s'.", source);
		}


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