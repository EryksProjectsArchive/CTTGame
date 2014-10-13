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

#include <input/Input.h>

#include "CrossroadEntity.h"

#include <resources/models/ModelLib.h>

#include <io/fs/FileSystem.h>

#include <graphics/Vertex3d.h>

CrossroadEntity::CrossroadEntity()
	: Entity(EntityType::Crossroad)
{
	m_model = ModelLib::get()->findByName("road");
	m_model->acquire();

	AABB * aabb = m_model->getAABB();

	// Detailed shape
	File* file = FileSystem::get()->open("models/road.mdl", FileOpenMode::Read | FileOpenMode::Binary);
	if (file->isLoaded())
	{
		mdl data;
		if (ModelFormat::load(&data, file))
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
	else
	{
		Error("CrossroadEntity", "Cannot open model file to generate tri mesh collisions.");
	}
	FileSystem::get()->close(file);
}

CrossroadEntity::~CrossroadEntity()
{
	if (m_model)
		m_model->release();
}

void CrossroadEntity::render(RenderContext & ctx)
{
	if (m_model)
	{
		btRigidBody * rigidBody = m_rigidBody;
		if (rigidBody)
		{			
			float _matrix[16];
			// it's not dynamic so we should use simple world transformation from rigid body
			m_rigidBody->getWorldTransform().getOpenGLMatrix(_matrix);
			
			m_model->setMatrix(Matrix4x4(_matrix[0], _matrix[1], _matrix[2], _matrix[3], _matrix[4], _matrix[5], _matrix[6], _matrix[7], _matrix[8], _matrix[9], _matrix[10], _matrix[11], _matrix[12], _matrix[13], _matrix[14], _matrix[15]));
			m_model->render(ctx);
		}
	}
}

void CrossroadEntity::prePhysicsUpdate()
{
}

void CrossroadEntity::postPhysicsUpdate()
{
}