//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: physics/PhysicalEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "PhysicsWorld.h"
#include "PhysicalEntity.h"

#include <game/Game.h>

PhysicalEntity::PhysicalEntity()
	: m_rigidBody(0)
{
	Game::get()->getPhysicsWorld()->registerEntity(this);
}

PhysicalEntity::~PhysicalEntity()
{
	Game::get()->getPhysicsWorld()->unregisterEntity(this);

	if (m_rigidBody)
	{
		Game::get()->getPhysicsWorld()->unregisterRigidBody(m_rigidBody);

		if (m_rigidBody->getCollisionShape())
			delete m_rigidBody->getCollisionShape();

		if (m_rigidBody->getMotionState())
			delete m_rigidBody->getMotionState();

		delete m_rigidBody;
		m_rigidBody = 0;
	}
}