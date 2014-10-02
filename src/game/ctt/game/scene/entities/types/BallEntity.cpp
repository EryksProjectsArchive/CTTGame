//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/BallEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <game/Game.h>
#include <game/scene/entities/Entity.h>

#include <graphics/Model.h>

#include <physics/PhysicsWorld.h>
#include <physics/PhysicalEntity.h>

#include "BallEntity.h"

BallEntity::BallEntity()
	: Entity(EntityType::Ball)
{
	m_model = new Model("../../data/models/ball.mdl");
	m_model->acquire();

	AABB * aabb = m_model->getAABB();

	// Detailed shape

	float radius = (aabb->getMax().y - aabb->getMin().y) / 2;

	btSphereShape *physicsShape = new btSphereShape(radius);

	btTransform transform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0));

	btDefaultMotionState *fallMotionState = new btDefaultMotionState(transform);

	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	physicsShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, physicsShape, fallInertia);
	fallRigidBodyCI.m_friction = 2.5f; 
	m_rigidBody = new btRigidBody(fallRigidBodyCI);

	Game::get()->getPhysicsWorld()->registerRigidBody(m_rigidBody);
}

BallEntity::~BallEntity()
{
	if (m_model)
	{
		m_model->free();
		delete m_model;
		m_model = 0;
	}
}

void BallEntity::render(RenderContext & ctx)
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

void BallEntity::prePhysicsUpdate()
{
}

void BallEntity::postPhysicsUpdate()
{
}