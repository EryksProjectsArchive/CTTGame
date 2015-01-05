//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Geometry.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include "Vertex3d.h"
#include "renderer/Renderer.h"
#include "BufferBase.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct EDrawType
{
	enum Type
	{
		TRIANGLES,
		LINES,
		LINE_STRIP
	};
};

template <class VertexType>
class Geometry
{
private:
	VertexBuffer* m_vertexBuffer;
	IndexBuffer* m_indexBuffer;

	uint16 m_trianglesCount;
	uint16 m_verticesCount;

	EDrawType::Type m_drawType;
public:
	Geometry()
	{
		m_vertexBuffer = (VertexBuffer *)Renderer::get()->createBuffer(BufferType::VERTEX);
		m_indexBuffer = (IndexBuffer *)Renderer::get()->createBuffer(BufferType::INDEX);

		m_trianglesCount = 0;
		m_verticesCount = 0;
		m_drawType = EDrawType::TRIANGLES;
	}

	Geometry(EDrawType::Type type) : Geometry()
	{
		m_drawType = type;
	}

	~Geometry()
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
	
	void fillData(VertexType *vertices, uint16 verticesCount, void *triangles, uint16 trianglesCount)
	{
		m_trianglesCount = trianglesCount;
		m_verticesCount = verticesCount;

		if (m_vertexBuffer)
		{
			m_vertexBuffer->allocate(sizeof(VertexType) * verticesCount, false);
			m_vertexBuffer->fillData(vertices);
		}

		if (m_indexBuffer)
		{
			m_indexBuffer->allocate(sizeof(uint16) * (trianglesCount * 3), false);
			m_indexBuffer->fillData(triangles);
		}
	}


	friend class Renderer;
	friend class DeferredRendering;
};