//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/FragmentShader.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "FragmentShader.h"

#include <stdio.h>
#include <core/Logger.h>

#include "renderer/Renderer.h"

#include <io/fs/FileSystem.h>

FragmentShader::FragmentShader(const FilePath& source) : Shader(source)
{	
}

FragmentShader::~FragmentShader()
{
	if (m_shaderId)
	{
		Renderer::glDeleteShader(m_shaderId);
		m_shaderId = 0;
	}
}

bool FragmentShader::compile()
{
	if (m_isCompiled)
	{
		Warning("FragmentShader", "Tried to compile shader twice. '%s'", m_sourcePath.get());
		return true;
	}

	bool success = false;

	File *file = FileSystem::get()->open(m_sourcePath, FileOpenMode::Read);
	if (file && file->isLoaded())
	{
		m_shaderId = Renderer::glCreateShader(GL_FRAGMENT_SHADER);

		DynString source = file->getContent();

		// Find any better way to do that.
		size_t length = source.getLength();
		char *sourceTmp = new char[length + 1];
		memset(sourceTmp, 0, length);
		strcpy(sourceTmp, source.get());
		sourceTmp[length] = '\0';

		Renderer::glShaderSource(m_shaderId, 1, (const GLchar **)&sourceTmp, (const GLint *)&length);
		Renderer::glCompileShader(m_shaderId);

		GLint params = 0;
		Renderer::glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &params);
		if (params == GL_FALSE)
		{
			GLint maxLength = 0;
			Renderer::glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			char *errorLog = new char[maxLength + 1];

			Renderer::glGetShaderInfoLog(m_shaderId, maxLength, &maxLength, errorLog);
			errorLog[maxLength] = '\0';

			Error("FragmentShader", "Compilation error (%s):", m_sourcePath.get());

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
					Error("FragmentShader", line);
					startIndex = i + 1;
					delete[]line;
				}
			}

			delete[]errorLog;

			//Provide the infolog in whatever manor you deem best.
			//Exit with failure.
			Renderer::glDeleteShader(m_shaderId); //Don't leak the shader.
		}
		else 
		{
			Debug("FragmentShader", "Compilation success '%s'.", m_sourcePath.get());
			success = true;
		}

		delete[]sourceTmp;
		sourceTmp = 0;
	}
	FileSystem::get()->close(file);
	return success;
}