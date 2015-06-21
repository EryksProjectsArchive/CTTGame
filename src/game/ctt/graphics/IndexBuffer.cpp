//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/IndexBuffer.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "BufferBase.h"
#include "renderer/Renderer.h"

#include "IndexBuffer.h"
#include <core/Logger.h>

IndexBuffer::IndexBuffer()
{
}

void IndexBuffer::fillData(void * data)
{
	Renderer::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
	Renderer::glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, data, m_isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}