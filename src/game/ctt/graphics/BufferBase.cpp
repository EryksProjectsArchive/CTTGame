//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/BufferBase.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "renderer/Renderer.h"

#include "BufferBase.h"
#include <core/Logger.h>

BufferBase::BufferBase()
	: m_isDynamic(false), m_bufferId(0), m_size(-1)
{
	Renderer::glGenBuffers(1, &m_bufferId);
}

BufferBase::~BufferBase()
{
	Renderer::glDeleteBuffers(1, &m_bufferId);
}

void BufferBase::allocate(unsigned int size, bool dynamic)
{
	m_size = size;
	m_isDynamic = dynamic;
}

void BufferBase::fillData(void * data)
{

}