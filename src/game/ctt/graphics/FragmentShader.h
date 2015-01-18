//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/FragmentShader.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include "Shader.h"

class FragmentShader : public Shader
{
public:
	FragmentShader(const FilePath& source);
	virtual ~FragmentShader();

	virtual bool compile();
};

typedef FragmentShader PixelShader;