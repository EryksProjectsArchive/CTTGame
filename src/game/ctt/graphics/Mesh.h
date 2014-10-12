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

#include <Prerequisites.h>

#include "ModelFormat.h"
#include <core/SharedPtr.h>
#include <math/AABB.h>

class Mesh
{
private:
	Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;	
	Matrix4x4 m_modelSpaceMatrix;

	Geometry<Vertex3d> *m_geometry;
	Material* m_material;

	AABB m_aabb;

	char *m_meshName;
public:
	Mesh(mesh * meshData);
	~Mesh();

	const char * getName();

	void render(RenderContext& context, Matrix4x4 modelMatrix);

	AABB * getAABB();
};