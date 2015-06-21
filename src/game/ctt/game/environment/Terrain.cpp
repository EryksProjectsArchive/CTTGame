//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/environment/Terrain.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Terrain.h"

#include <graphics/renderer/RenderContext.h>
#include <graphics/renderer/tasks/ModelRenderTask.h>

#include <resources/materials/MaterialLib.h>

#include <game/Game.h>
#include <physics/PhysicsWorld.h>

#include <graphics/Camera.h>

#include <Windows.h>

Terrain::Terrain(uint32 width, uint32 height)
{
	m_nodeSize = 300;
	m_width = width;
	m_height = height;
	m_wNodes = width / m_nodeSize;
	m_hNodes = height / m_nodeSize;

	m_node = new TerrainGrid**[m_wNodes];
	for (uint32 x = 0; x < m_wNodes; ++x)
	{
		m_node[x] = new TerrainGrid*[m_hNodes];
		for (uint32 y = 0; y < m_hNodes; ++y)
			m_node[x][y] = 0;
	}

	uint32 i = 0;
	Vector3 point(-(float)(width / 2), 0, -(float)(height / 2));
	for (uint32 y = 0; y < m_hNodes; ++y)
	{
		for (uint32 x = 0; x < m_wNodes; ++x)
		{			
			m_node[x][y] = new TerrainGrid(point, m_nodeSize);
			point.x += m_nodeSize;
			++i;
		}
		point.x = -(float)(width / 2);
		point.z += m_nodeSize;
	
	}

	Info("terrain", "Add %d grids", i);
}
	
Terrain::~Terrain()
{
	uint32 i = 0;
	for (uint32 y = 0; y < m_hNodes; ++y)
	{
		for (uint32 x = 0; x < m_wNodes; ++x)
		{
			delete m_node[x][y];
			++i;
		}
	}
	Info("terrain", "Removed %d grids", i);

	for (uint32 x = 0; x < m_wNodes; ++x)
		delete [] m_node[x];

	delete[]m_node;
}

void Terrain::render(RenderContext& context)
{
	int32 x = 0;
	int32 y = 0;

	int32 wNodes = (int32) m_wNodes;
	int32 hNodes = (int32) m_hNodes;

	Vector3 cameraRelative = CameraManager::get()->getCurrent()->getPosition() - Vector3(-(float)(m_width / 2), 0, -(float)(m_height / 2));

	x = (int32)(cameraRelative.x / m_nodeSize);
	y = (int32)(cameraRelative.z / m_nodeSize);

	{
		bool yInRange = (y >= 0 && y < hNodes);
		bool xInRange = (x >= 0 && x < wNodes);
		if (xInRange && yInRange)
		{
			if (m_node[x][y])
				m_node[x][y]->render(context);
		}
	
		if (xInRange && (y + 1) < hNodes)
		{
			if (m_node[x][y + 1])
				m_node[x][y + 1]->render(context);
		}

		if (xInRange && (y - 1) >= 0)
		{
			if (m_node[x][y - 1])
				m_node[x][y - 1]->render(context);
		}

		// X Y
		if ((x + 1) < wNodes && (y + 1) < hNodes)
		{
			if (m_node[x + 1][y + 1])
				m_node[x + 1][y + 1]->render(context);
		}

		// X
		if ((x + 1) < wNodes && (y - 1) >= 0)
		{
			if (m_node[x + 1][y - 1])
				m_node[x + 1][y - 1]->render(context);
		}

		// Y
		if ((x - 1) >= 0 && (y + 1) < hNodes)
		{
			if (m_node[x - 1][y + 1])
				m_node[x - 1][y + 1]->render(context);
		}

		// Y
		if (yInRange && (x+1) < wNodes)
		{
			if (m_node[x + 1][y])
				m_node[x + 1][y]->render(context);
		}

		if (yInRange && (x - 1) >= 0)
		{
			if (m_node[x-1][y])
				m_node[x-1][y]->render(context);
		}

		if ((x-1) >= 0 && (y-1) >= 0)
		{
			if (m_node[x-1][y - 1])
				m_node[x-1][y - 1]->render(context);
		}
	}
}

TerrainGrid::TerrainGrid(Vector3 position, uint32 size) : m_left(0), m_right(0), m_top(0), m_bottom(0)
{
	m_world = glm::translate(glm::mat4(), position);
	m_material = MaterialLib::get()->findByName("terrain");
	m_material->acquire();

	Vertex3d vertices[4] = {
		{ 0, 0, 0, 0, 1, 0, 60, 0, 0xFFFFFFFF, 0, 0, 0 },
		{ float(size), 0, 0, 0, 1, 0, 0, 0, 0xFFFFFFFF, 0, 0, 0 },
		{ float(size), 0, float(size), 0, 1, 0, 0, 60, 0xFFFFFFFF, 0, 0, 0 },
		{ 0, 0, float(size), 0, 1, 0, 60, 60, 0xFFFFFFFF, 0, 0, 0 }
	};

	uint16 indices[6] = {
		0, 1, 2,
		0, 2, 3
	};

	m_geometry.fillData(vertices, 4, indices, 2);
	
	btTriangleMesh* triMesh = new btTriangleMesh();
	triMesh->addTriangle(btVector3(0, 0, 0), btVector3(float(size), 0, 0), btVector3(float(size), 0, float(size)));
	triMesh->addTriangle(btVector3(0, 0, 0), btVector3(float(size), 0, float(size)), btVector3(0, 0, float(size)));

	btBvhTriangleMeshShape* physicsShape = new btBvhTriangleMeshShape(triMesh, true);

	m_rigidBody = new btRigidBody(0, NULL, physicsShape);
	m_rigidBody->setRestitution(0.5f);
	m_rigidBody->setFriction(2.0f);
	btTransform transform = m_rigidBody->getWorldTransform();
	transform.setOrigin(btVector3(position.x, position.y, position.z));
	m_rigidBody->setWorldTransform(transform);
	Game::get()->getPhysicsWorld()->registerRigidBody(m_rigidBody);
}

TerrainGrid::~TerrainGrid()
{
	if (m_rigidBody)
	{
		Game::get()->getPhysicsWorld()->unregisterRigidBody(m_rigidBody);
		delete m_rigidBody;
	}

	if (m_material)
		m_material->release();
}

void TerrainGrid::render(RenderContext& context)
{
	// TODO: TerrainRenderTask
	ModelRenderTask *task = context.newTask<ModelRenderTask>();

	task->setGeometry(&m_geometry);
	task->setMaterial(m_material);
	task->setModelMatrix(m_world);
}