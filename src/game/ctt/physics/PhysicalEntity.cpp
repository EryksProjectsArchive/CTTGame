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

#include <core/Logger.h>

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

void PhysicalEntity::setLinearVelocity(Vector3 velocity)
{
	Warning("Physics", "%s: Setting linear velocity is not possible for static entity. (%s:%d)", FUNCTION_NAME, __FILE__, __LINE__);
}

Vector3 PhysicalEntity::getLinearVelocity()
{
	return Vector3();
}

void PhysicalEntity::setAngularVelocity(Vector3 velocity)
{
	Warning("Physics", "%s: Setting angular velocity is not possible for static entity. (%s:%d)", FUNCTION_NAME, __FILE__, __LINE__);
}

Vector3 PhysicalEntity::getAngularVelocity()
{
	return Vector3();
}

void PhysicalEntity::setPosition(Vector3 position)
{	
	if (m_rigidBody)
	{
		if (!m_rigidBody->isActive())
			m_rigidBody->activate(true);

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
		if (!m_rigidBody->isActive())
			m_rigidBody->activate(true);

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

bool PhysicalEntity::isDynamic()
{
	return false;
}

void PhysicalEntity::setMass(float mass)
{
	Warning("Physics", "%s: Setting mass is not possible for static entities. (%s:%d)", FUNCTION_NAME, __FILE__, __LINE__);
}

void PhysicalEntity::setFriction(float friction)
{
	if (m_rigidBody)
		m_rigidBody->setFriction(friction);
}

void PhysicalEntity::setRestitution(float restitution)
{
	if (m_rigidBody)
		m_rigidBody->setRestitution(restitution);
}

void PhysicalEntity::setupPhysics(btCollisionShape * shape)
{
	m_collisionShape = shape;
	if (m_rigidBody)
	{
		Game::get()->getPhysicsWorld()->registerRigidBody(m_rigidBody);
		m_rigidBody->setUserPointer(this);
	}
}