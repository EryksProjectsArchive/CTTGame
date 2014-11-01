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
	Game::get()->getPhysicsWorld().registerEntity(this);
}

PhysicalEntity::~PhysicalEntity()
{
	Game::get()->getPhysicsWorld().unregisterEntity(this);

	if (m_rigidBody)
	{
		Game::get()->getPhysicsWorld().unregisterRigidBody(m_rigidBody);

		if (m_rigidBody->getCollisionShape())
			delete m_rigidBody->getCollisionShape();

		if (m_rigidBody->getMotionState())
			delete m_rigidBody->getMotionState();

		delete m_rigidBody;
		m_rigidBody = 0;
	}
}

void PhysicalEntity::setLinearVelocity(Vector3 velocity)
{
	if (m_rigidBody)
	{
		m_rigidBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
	}
}

Vector3 PhysicalEntity::getLinearVelocity()
{
	if (m_rigidBody)
	{
		btVector3 vec = m_rigidBody->getLinearVelocity();
		return Vector3(vec.x(), vec.y(), vec.z());
	}

	return Vector3();
}

void PhysicalEntity::setAngularVelocity(Vector3 velocity)
{
	if (m_rigidBody)
	{
		m_rigidBody->setAngularVelocity(btVector3(velocity.x, velocity.y, velocity.z));
	}
}

Vector3 PhysicalEntity::getAngularVelocity()
{
	if (m_rigidBody)
	{
		btVector3 vec = m_rigidBody->getAngularVelocity();
		return Vector3(vec.x(), vec.y(), vec.z());
	}

	return Vector3();
}

void PhysicalEntity::setPosition(Vector3 position)
{
	if (m_rigidBody)
	{
		btTransform transform = m_rigidBody->getWorldTransform();
		transform.setOrigin(btVector3(position.x, position.y, position.z));
		m_rigidBody->setWorldTransform(transform);
	}
}

Vector3 PhysicalEntity::getPosition()
{
	if (m_rigidBody)
	{
		btVector3 vec = m_rigidBody->getWorldTransform().getOrigin();
		return Vector3(vec.x(), vec.y(), vec.z());
	}
	return Vector3();
}

void PhysicalEntity::setRotation(Quaternion rotation)
{
	if (m_rigidBody)
	{
		btTransform transform = m_rigidBody->getWorldTransform();
		transform.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
		m_rigidBody->setWorldTransform(transform);
	}
}

Quaternion PhysicalEntity::getRotation()
{
	if (m_rigidBody)
	{
		btQuaternion quat = m_rigidBody->getWorldTransform().getRotation();
		return Quaternion(quat.w(), quat.x(), quat.y(), quat.z());
	}
	return Quaternion();
}


float PhysicalEntity::getHeight()
{
	if (m_rigidBody)
	{
		btVector3 min, max;
		m_rigidBody->getAabb(min, max);
		return max.y() - min.y();
	}
	return 0;
}

float PhysicalEntity::getWidth()
{
	if (m_rigidBody)
	{
		btVector3 min, max;
		m_rigidBody->getAabb(min, max);
		return max.x() - min.x();
	}
	return 0;
}