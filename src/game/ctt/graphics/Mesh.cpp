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

#include <cstring>

#include "Mesh.h"
#include "renderer/RenderContext.h"
#include "Material.h"
#include "Geometry.h"
#include "ModelFormat.h"
#include <core/Logger.h>
#include <core/Timer.h>

Mesh::Mesh(mesh * meshData)
	: m_geometry(0), m_meshName(0), m_material(0),
	  m_position(Vector3(meshData->worldPlacement.position.x, meshData->worldPlacement.position.y, meshData->worldPlacement.position.z)),
	  m_rotation(Quaternion(meshData->worldPlacement.rotation.w, meshData->worldPlacement.rotation.x, meshData->worldPlacement.rotation.y, meshData->worldPlacement.rotation.z)),
	  m_scale(Vector3(meshData->worldPlacement.scale.x, meshData->worldPlacement.scale.y, meshData->worldPlacement.scale.z))
{
	m_geometry = new Geometry();
	if (m_geometry)
		m_geometry->fillData(meshData->vertices, meshData->verticesCount, meshData->triangles, meshData->trianglesCount);	

	m_meshName = new char[meshData->name.len+1];
	memcpy(m_meshName, meshData->name.value, meshData->name.len);
	m_meshName[meshData->name.len] = '\0';

	//m_material = MaterialLib::FindByName(meshData->material.value);
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
	Matrix4x4 translationMatrix, scaleMatrix;
	scaleMatrix = glm::scale(glm::mat4x4(), m_scale);
	translationMatrix = glm::translate(glm::mat4x4(), m_position);
	
	renderingTask->m_geometry = m_geometry;
	renderingTask->m_material = m_material;
	renderingTask->m_matrix = (translationMatrix * scaleMatrix * glm::mat4_cast(m_rotation));
}