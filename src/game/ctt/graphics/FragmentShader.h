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

#include "Shader.h"

class FragmentShader : public Shader
{
public:
	FragmentShader(const char * source);
	virtual ~FragmentShader();
};

typedef FragmentShader PixelShader;