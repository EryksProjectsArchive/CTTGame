//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Mesh.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Mesh.h"

#include "renderer/RenderContext.h"

#include <cstring>

Mesh::Mesh(mesh * meshData)
	: m_geometry(0)
{
	m_geometry = new Geometry();
	if (m_geometry)
	{
		m_geometry->fillData(meshData->vertices, meshData->verticesCount, meshData->triangles, meshData->trianglesCount);
	}

	//m_material = MaterialLib::FindByName(meshData->material.value);

	memcpy(&m_position.x, &meshData->worldPlacement.position.x, sizeof(Vector3));
	memcpy(&m_rotation.w, &meshData->worldPlacement.rotation.w, sizeof(Quaternion));
}

Mesh::~Mesh()
{
	if (m_geometry)
	{
		delete m_geometry;
		m_geometry = 0;
	}
}

void Mesh::render(RenderContext& context)
{
	Matrix4x4 translationMatrix;
	translationMatrix.translate(m_position);	
	//context.push(m_geometry, m_material, &(translationMatrix * m_rotation.toMatrix4x4()));
}