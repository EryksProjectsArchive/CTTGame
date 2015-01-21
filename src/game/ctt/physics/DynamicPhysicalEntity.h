//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: physics/DynamicPhysicalEntity.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////
#pragma once

#include <Prerequisites.h>

#include "PhysicsWorld.h"
#include "PhysicalEntity.h"

class DynamicPhysicalEntity : public PhysicalEntity
{
public:
	DynamicPhysicalEntity();
	virtual ~DynamicPhysicalEntity();

	virtual void setLinearVelocity(Vector3 velocity);
	virtual Vector3 getLinearVelocity();

	virtual void setAngularVelocity(Vector3 velocity);
	virtual Vector3 getAngularVelocity();

	virtual bool isDynamic();

	virtual void postPhysicsUpdate();

	virtual void setCenterOfMass(Vector3 vector);
	virtual void setMass(float mass);

protected:
	void setupPhysics(btCollisionShape * shape);
};