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
#include "MaterialLib.h"

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

	m_material = MaterialLib::get()->findByName(meshData->material.value);

	m_colbox = new Geometry(EDrawType::LINE_STRIP);
	if (m_colbox)
	{
		vertex colbox[8] = { 0 };
		for (unsigned int i = 0; i < 8; ++i)
			colbox[i].color = 0xFF0000FF;

		colbox[0].x = meshData->simpleColBox.min.x;
		colbox[0].y = meshData->simpleColBox.max.y;
		colbox[0].z = meshData->simpleColBox.min.z;

		colbox[1].x = meshData->simpleColBox.max.x;
		colbox[1].y = meshData->simpleColBox.max.y;
		colbox[1].z = meshData->simpleColBox.max.z;

		colbox[2].x = meshData->simpleColBox.min.x;
		colbox[2].y = meshData->simpleColBox.max.y;
		colbox[2].z = meshData->simpleColBox.max.z;

		colbox[3].x = meshData->simpleColBox.max.x;
		colbox[3].y = meshData->simpleColBox.max.y;
		colbox[3].z = meshData->simpleColBox.min.z;

		colbox[4].x = meshData->simpleColBox.min.x;
		colbox[4].y = meshData->simpleColBox.min.y;
		colbox[4].z = meshData->simpleColBox.min.z;

		colbox[5].x = meshData->simpleColBox.max.x;
		colbox[5].y = meshData->simpleColBox.min.y;
		colbox[5].z = meshData->simpleColBox.max.z;

		colbox[6].x = meshData->simpleColBox.min.x;
		colbox[6].y = meshData->simpleColBox.min.y;
		colbox[6].z = meshData->simpleColBox.max.z;

		colbox[7].x = meshData->simpleColBox.max.x;
		colbox[7].y = meshData->simpleColBox.min.y;
		colbox[7].z = meshData->simpleColBox.min.z;

		triangle triangles[4];
		triangles[0].a = 0;
		triangles[0].b = 1;
		triangles[0].c = 2;

		triangles[1].a = 0;
		triangles[1].b = 3;
		triangles[1].c = 1;

		triangles[2].a = 4;
		triangles[2].b = 5;
		triangles[2].c = 6;

		triangles[3].a = 4;
		triangles[3].b = 7;
		triangles[3].c = 5;

		m_colbox->fillData(colbox, 8, triangles, 4);
	}
}

Mesh::~Mesh()
{
	if (m_geometry)
	{
		delete m_geometry;
		m_geometry = 0;
	}

	if (m_colbox)
	{
		delete m_colbox;
		m_colbox = 0;
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
	Matrix4x4 translationMatrix, scaleMatrix;
	scaleMatrix = glm::scale(glm::mat4x4(), m_scale);
	translationMatrix = glm::translate(glm::mat4x4(), m_position);

	RenderTask * renderingTask = 0;

	// Geometry debug
	//if (physicsScene->isDebugEnabled())
	{
		renderingTask = context.newTask();

		renderingTask->m_geometry = m_colbox;
		renderingTask->m_matrix = (translationMatrix * glm::mat4_cast(m_rotation) * scaleMatrix);
	}

	renderingTask = context.newTask();
	
	renderingTask->m_geometry = m_geometry;
	renderingTask->m_material = m_material;
	renderingTask->m_matrix = (translationMatrix * glm::mat4_cast(m_rotation) * scaleMatrix);
}