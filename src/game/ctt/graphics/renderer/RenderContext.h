//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/RenderContext.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <graphics/Geometry.h>
#include <graphics/Material.h>

#include <math/Matrix.h>

class ShaderProgram;
class RenderContext
{
private:
	ShaderProgram *m_shaderProgram;
public:
	RenderContext();
	~RenderContext();

	void setShaderProgram(ShaderProgram *shaderProgram);
};