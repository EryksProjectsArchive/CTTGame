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

class Mesh
{
private:
	Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;

	Geometry *m_geometry;
	Geometry *m_colbox;
	SharedPtr<Material> m_material;

	char *m_meshName;
public:
	Mesh(mesh * meshData);
	~Mesh();

	const char * getName();

	void render(RenderContext& context);
};