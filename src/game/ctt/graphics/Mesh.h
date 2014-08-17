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

#include <math/Vector.h>
#include <math/Quaternion.h>

#include "Material.h"
#include "Geometry.h"

#include "ModelFormat.h"

class RenderContext;

class Mesh
{
private:
	Vector3 m_position;
	Quaternion m_rotation;

	Geometry *m_geometry;
	Material *m_material;
public:
	Mesh(mesh * meshData);
	~Mesh();

	void render(RenderContext& context);
};