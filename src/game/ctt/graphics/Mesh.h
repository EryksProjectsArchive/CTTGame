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

#include <math/Vector.h>
#include <math/Quaternion.h>

#include "ModelFormat.h"

class Mesh
{
private:
	Vector3 m_position;
	Quaternion m_rotation;

	Geometry *m_geometry;
	Material *m_material;

	char *m_meshName;
public:
	Mesh(mesh * meshData);
	~Mesh();

	const char * getName();

	void render(RenderContext& context);
};