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
#include <resources/materials/MaterialLib.h>

#include <game/Game.h>
#include <physics/PhysicsWorld.h>

#include <graphics/Camera.h>

Terrain::Terrain(uint32 width, uint32 height)
{
	uint32 nodeSize = 15;
	m_width = width;
	m_height = height;
	m_wNodes = width / nodeSize;
	m_hNodes = height / nodeSize;

	m_node = new TerrainNode**[m_wNodes];
	for (uint32 x = 0; x < m_wNodes; ++x)
		m_node[x] = new TerrainNode*[m_hNodes];

	Vector3 point(-(float)(width / 2), 0, -(float)(height / 2));
	for (uint32 y = 0; y < m_hNodes; ++y)
	{
		for (uint32 x = 0; x < m_wNodes; ++x)
		{
			m_node[x][y] = new TerrainNode(point, nodeSize);
			point.x += nodeSize;
		}
		point.x = -(float)(width / 2);
		point.z += nodeSize;
	}
}
	
Terrain::~Terrain()
{
	for (uint32 y = 0; y < m_hNodes; ++y)
	{
		for (uint32 x = 0; x < m_wNodes; ++x)
		{
			delete m_node[x][y];
		}
	}

	for (uint32 x = 0; x < m_wNodes; ++x)
		delete[]m_node[x];
	delete[]m_node;
}

void Terrain::render(RenderContext& context)
{
	uint32 x = 0;
	uint32 y = 0;

	Vector3 position = Camera::current->getPosition();

	x = uint32(position.x / (float)((m_width/2)/15));
	y = uint32(position.z / (float)((m_height/2)/15));

	Info("pos", "%f,%f %d,%d", position.x, position.z, x, y);
	if (x > m_wNodes || x < 0 || y > m_hNodes || y < 0)
		return;

	if (m_node[x][y])
		m_node[x][y]->render(context);
}

TerrainNode::TerrainNode(Vector3 position, uint32 size) : m_left(0), m_right(0), m_top(0), m_bottom(0)
{
	m_world = glm::translate(glm::mat4(), position);
	m_material = MaterialLib::get()->findByName("terrain");
	m_material->acquire();

	Vertex3d vertices[4] = {
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0xFFFFFFFF, 0, 0, 0, 0 },
		{ float(size), 0, 0, 0, 1, 0, 1, 0, 0xFFFFFFFF, 0, 0, 0, 0 },
		{ float(size), 0, float(size), 0, 1, 0, 1, 1, 0xFFFFFFFF, 0, 0, 0, 0 },
		{ 0, 0, float(size), 0, 1, 0, 0, 1, 0xFFFFFFFF, 0, 0, 0, 0 }
	};

	uint16 indices[6] = {
		0, 1, 2,
		0, 2, 3
	};

	m_geometry.fillData(vertices, 4, indices, 2);
	
	btTriangleMesh *triMesh = new btTriangleMesh();
	triMesh->addTriangle(btVector3(0, 0, 0), btVector3(float(size), 0, 0), btVector3(float(size), 0, float(size)));
	triMesh->addTriangle(btVector3(0, 0, 0), btVector3(float(size), 0, float(size)), btVector3(0, 0, float(size)));

	btBvhTriangleMeshShape*physicsShape = new btBvhTriangleMeshShape(triMesh, true);

	btTransform transform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z));
	btDefaultMotionState *groundMotionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, physicsShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(groundRigidBodyCI);

	Game::get()->getPhysicsWorld()->registerRigidBody(m_rigidBody);
}

TerrainNode::~TerrainNode()
{
	if (m_material)
		m_material->release();
}

void TerrainNode::render(RenderContext& context)
{
	RenderTask *task = context.newTask();

	task->m_geometry = &m_geometry;
	task->m_material = m_material;
	task->m_matrix = m_world;
}