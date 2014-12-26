//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: physics/StaticPhysicalEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "StaticPhysicalEntity.h"

StaticPhysicalEntity::StaticPhysicalEntity()
{

}

StaticPhysicalEntity::~StaticPhysicalEntity()
{

}

void StaticPhysicalEntity::setPosition(Vector3 position)
{
	PhysicalEntity::setPosition(position);
	internalStaticTransformUpdate();
}

void StaticPhysicalEntity::setRotation(Quaternion rotation)
{
	PhysicalEntity::setRotation(rotation);
	internalStaticTransformUpdate();
}

void StaticPhysicalEntity::internalStaticTransformUpdate()
{
	if (m_rigidBody)
	{
		m_rigidBody->getWorldTransform().getOpenGLMatrix((float *)&m_transform[0][0]);
	}
}

void StaticPhysicalEntity::setupPhysics(btCollisionShape * shape)
{
	m_rigidBody = new btRigidBody(0.0f, NULL, shape);
	PhysicalEntity::setupPhysics(shape);
}