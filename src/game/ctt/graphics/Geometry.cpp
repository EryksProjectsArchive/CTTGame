//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Geometry.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Geometry.h"

#include "BufferBase.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "renderer/Renderer.h"

#include "Vertex3d.h"

Geometry::Geometry()
{
	m_vertexBuffer = (VertexBuffer * )Renderer::get().createBuffer(BufferType::VERTEX);
	m_indexBuffer = (IndexBuffer *)Renderer::get().createBuffer(BufferType::INDEX);

	m_trianglesCount = 0;
	m_verticesCount = 0;
	m_drawType = EDrawType::TRIANGLES;
}

Geometry::Geometry(EDrawType::Type type) : Geometry()
{
	m_drawType = type;
}

Geometry::~Geometry()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = 0;
	}

	if (m_indexBuffer)
	{
		delete m_indexBuffer;
		m_indexBuffer = 0;
	}
}

void Geometry::fillData(void *vertices, unsigned short verticesCount, void *triangles, unsigned short trianglesCount)
{
	m_trianglesCount = trianglesCount;
	m_verticesCount = verticesCount;

	if (m_vertexBuffer)
	{
		m_vertexBuffer->allocate(sizeof(Vertex3d) * verticesCount, false);
		m_vertexBuffer->fillData(vertices);
	}

	if (m_indexBuffer)
	{
		m_indexBuffer->allocate(sizeof(unsigned short) * (trianglesCount * 3), false);
		m_indexBuffer->fillData(triangles);
	}
}
