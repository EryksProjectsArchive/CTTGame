//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/CrossroadEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <game/Game.h>
#include <game/scene/entities/Entity.h>

#include <graphics/Model.h>

#include <physics/PhysicsWorld.h>
#include <physics/PhysicalEntity.h>

#include "CrossroadEntity.h"

CrossroadEntity::CrossroadEntity()
	: Entity(EntityType::Crossroad)
{
	m_model = new Model("../../data/models/road.mdl");
	m_model->acquire();

	AABB * aabb = m_model->getAABB();

	// Detailed shape
	FILE *fp = fopen("../../data/models/road.mdl", "rb");
	mdl data;
	if (ModelFormat::load(&data, fp))
	{
		btTriangleMesh *triMesh = new btTriangleMesh();

		for (int i = 0; i < data.meshCount; ++i)
		{
			for (unsigned int t = 0; t < data.meshes[i].trianglesCount; ++t)
			{
				int a = data.meshes[i].triangles[t].a;
				int b = data.meshes[i].triangles[t].b;
				int c = data.meshes[i].triangles[t].c;
				triMesh->addTriangle(btVector3(data.meshes[i].vertices[a].x, data.meshes[i].vertices[a].y, data.meshes[i].vertices[a].z), btVector3(data.meshes[i].vertices[b].x, data.meshes[i].vertices[b].y, data.meshes[i].vertices[b].z), btVector3(data.meshes[i].vertices[c].x, data.meshes[i].vertices[c].y, data.meshes[i].vertices[c].z));
			}

			delete[] data.meshes[i].name.value;
			delete[] data.meshes[i].material.value;
			delete[] data.meshes[i].triangles;
			delete[] data.meshes[i].vertices;
		}

		delete[] data.meshes;


		btBvhTriangleMeshShape*physicsShape = new btBvhTriangleMeshShape(triMesh, true);

		btTransform transform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0));

		btDefaultMotionState *groundMotionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, physicsShape, btVector3(0, 0, 0));
		m_rigidBody = new btRigidBody(groundRigidBodyCI);

		Game::get()->getPhysicsWorld()->registerRigidBody(m_rigidBody);
	}
}

CrossroadEntity::~CrossroadEntity()
{
	if (m_model)
	{
		m_model->free();
		delete m_model;
		m_model = 0;
	}
}

void CrossroadEntity::render(RenderContext & ctx)
{
	if (m_model)
	{
		btScalar m[16];
		((btDefaultMotionState *)m_rigidBody->getMotionState())->m_graphicsWorldTrans.getOpenGLMatrix(m);
		m_model->setMatrix(Matrix4x4(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]));

		m_model->render(ctx);
	}
}

void CrossroadEntity::prePhysicsUpdate()
{
}

void CrossroadEntity::postPhysicsUpdate()
{
}