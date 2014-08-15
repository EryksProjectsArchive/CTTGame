//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/VertexShader.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader(const char * source);
	virtual ~VertexShader();
};