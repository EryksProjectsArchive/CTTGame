//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/RenderContext.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "RenderContext.h"
#include "Renderer.h"

RenderContext::RenderContext()
	: m_shaderProgram(0)
{

}

RenderContext::~RenderContext()
{
	// Do whole rendering here
}

void RenderContext::setShaderProgram(ShaderProgram * shaderProgram)
{
	m_shaderProgram = shaderProgram;
}