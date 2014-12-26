//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: physics/DynamicPhysicalEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "DynamicPhysicalEntity.h"

DynamicPhysicalEntity::DynamicPhysicalEntity()
{

}

DynamicPhysicalEntity::~DynamicPhysicalEntity()
{

}

void DynamicPhysicalEntity::setLinearVelocity(Vector3 velocity)
{
	if (m_rigidBody)
	{
		m_rigidBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
	}
}

Vector3 DynamicPhysicalEntity::getLinearVelocity()
{
	if (m_rigidBody)
	{
		btVector3 vec = m_rigidBody->getLinearVelocity();
		return Vector3(vec.x(), vec.y(), vec.z());
	}
	return Vector3();
}


void DynamicPhysicalEntity::setAngularVelocity(Vector3 velocity)
{
	if (m_rigidBody)
	{
		m_rigidBody->setAngularVelocity(btVector3(velocity.x, velocity.y, velocity.z));
	}
}

Vector3 DynamicPhysicalEntity::getAngularVelocity()
{
	if (m_rigidBody)
	{
		btVector3 vec = m_rigidBody->getAngularVelocity();
		return Vector3(vec.x(), vec.y(), vec.z());
	}

	return Vector3();
}

bool DynamicPhysicalEntity::isDynamic()
{
	return true;
}

void DynamicPhysicalEntity::postPhysicsUpdate()
{	
	if (m_rigidBody)
	{
		btTransform transform;
		btDefaultMotionState *motionState = (btDefaultMotionState *)m_rigidBody->getMotionState();
		if (motionState)
			motionState->m_graphicsWorldTrans.getOpenGLMatrix((float *)&m_transform[0][0]);
	}
}

void DynamicPhysicalEntity::setMass(float mass)
{
	if (m_rigidBody)
	{
		if (!mass)
		{
			Warning("Physics", "%s (%s:%d): Requested zero mass on dynamic physical entity. Aborting this change.", FUNCTION_NAME, __FILE__, __LINE__);
			return;
		}
		
		btVector3 inertia;
		m_collisionShape->calculateLocalInertia(mass, inertia);
		m_rigidBody->setMassProps(mass, inertia);
		
		m_rigidBody->updateInertiaTensor();
	}
}

void DynamicPhysicalEntity::setupPhysics(btCollisionShape * shape)
{
	btDefaultMotionState *fallMotionState = new btDefaultMotionState();

	btVector3 inertia(1, 1, 1);
	shape->calculateLocalInertia(1, inertia);

	m_rigidBody = new btRigidBody(1, fallMotionState, shape, inertia);

	PhysicalEntity::setupPhysics(shape);
}