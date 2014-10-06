//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/BoxEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <game/Game.h>
#include <game/scene/entities/Entity.h>

#include <graphics/Model.h>

#include "BoxEntity.h"

BoxEntity::BoxEntity()
	: Entity(EntityType::Box)
{
	m_model = new Model("../../data/models/simpleBox.mdl");
	m_model->acquire();

	AABB * aabb = m_model->getAABB();

	btBoxShape *physicsShape = new btBoxShape(btVector3((aabb->getMax().x - aabb->getMin().x) / 2, (aabb->getMax().y - aabb->getMin().y) / 2, (aabb->getMax().z - aabb->getMin().z) / 2));

	btTransform transform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0));

	btDefaultMotionState *fallMotionState = new btDefaultMotionState(transform);

	btScalar mass = 0.5f;
	btVector3 fallInertia(0, 0, 0);
	physicsShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, physicsShape, fallInertia);
	fallRigidBodyCI.m_friction = 10.0f;
	m_rigidBody = new btRigidBody(fallRigidBodyCI);
	
	Game::get()->getPhysicsWorld()->registerRigidBody(m_rigidBody);
}

BoxEntity::~BoxEntity()
{
	if (m_model)
	{
		m_model->free();
		delete m_model;
		m_model = 0;
	}
}

void BoxEntity::render(RenderContext & ctx)
{
	if (m_model)
	{
		btRigidBody * rigidBody = m_rigidBody;
		if (rigidBody && rigidBody->getMotionState())
		{
			float _matrix[16];
			btDefaultMotionState* myMotionState = (btDefaultMotionState *)rigidBody->getMotionState();
			myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(_matrix);

			m_model->setMatrix(Matrix4x4(_matrix[0], _matrix[1], _matrix[2], _matrix[3], _matrix[4], _matrix[5], _matrix[6], _matrix[7], _matrix[8], _matrix[9], _matrix[10], _matrix[11], _matrix[12], _matrix[13], _matrix[14], _matrix[15]));
			m_model->render(ctx);
		}
	}
}

void BoxEntity::prePhysicsUpdate()
{
}

void BoxEntity::postPhysicsUpdate()
{
}