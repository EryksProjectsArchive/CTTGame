//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: physics/StaticPhysicalEntity.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////
#pragma once

#include <Prerequisites.h>

#include "PhysicsWorld.h"
#include "PhysicalEntity.h"

class StaticPhysicalEntity : public PhysicalEntity
{
private:
	void internalStaticTransformUpdate();
public:
	StaticPhysicalEntity();
	virtual ~StaticPhysicalEntity();

	virtual void setPosition(Vector3 position);
	virtual void setRotation(Quaternion rotation);

protected:
	void setupPhysics(btCollisionShape * shape);
};