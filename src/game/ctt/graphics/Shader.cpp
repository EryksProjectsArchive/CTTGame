//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Shader.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Shader.h"

Shader::Shader(const FilePath& source) : m_shaderId(0), m_sourcePath(source)
{
	m_isCompiled = 0;
}

Shader::~Shader()
{
}
