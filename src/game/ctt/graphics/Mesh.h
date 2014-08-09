//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Mesh.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "renderer/Renderer.h"
#include "renderer/BufferBase.h"

#include <math/Vector.h>
#include <math/Quaternion.h>

class Mesh
{
private:
	Vector3 m_position;
	Quaternion m_rotation;

	BufferBase* m_vertexBuffer;
	BufferBase* m_indexBuffer;
public:
	Mesh();
	~Mesh();

	void render(IRenderer* renderer);
};