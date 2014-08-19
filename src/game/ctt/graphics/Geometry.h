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

class Geometry
{
private:
	VertexBuffer* m_vertexBuffer;
	IndexBuffer* m_indexBuffer;

	unsigned short m_trianglesCount;
	unsigned short m_verticesCount;
public:
	Geometry();
	~Geometry();

	void fillData(void *vertices, unsigned short verticesCount, void *triangles, unsigned short trianglesCount);

	friend class Renderer;
};