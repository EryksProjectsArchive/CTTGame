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
	: m_geometry(0), m_meshName(0)
{
	m_geometry = new Geometry();
	if (m_geometry)
		m_geometry->fillData(meshData->vertices, meshData->verticesCount, meshData->triangles, meshData->trianglesCount);	

	m_meshName = new char[meshData->name.len+1];
	memcpy(m_meshName, meshData->name.value, meshData->name.len);
	m_meshName[meshData->name.len] = '\0';

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

	if (m_meshName)
	{
		delete[] m_meshName;
		m_meshName = 0;
	}
}

const char * Mesh::getName()
{
	return m_meshName;
}

void Mesh::render(RenderContext& context)
{	
	RenderTask * renderingTask = context.newTask();
	Matrix4x4 translationMatrix;
	translationMatrix.translate(m_position);	

	renderingTask->m_geometry = m_geometry;
	renderingTask->m_material = m_material;
	renderingTask->m_matrix = &(translationMatrix * m_rotation.toMatrix4x4());
}