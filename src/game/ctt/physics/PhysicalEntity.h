//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: physics/PhysicalEntity.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////
#pragma once

#include <Prerequisites.h>

class PhysicalEntity
{
protected:
	btRigidBody *m_rigidBody;

public:
	PhysicalEntity();
	~PhysicalEntity();

	virtual void prePhysicsUpdate() = 0;
	virtual void postPhysicsUpdate() = 0;

	void setLinearVelocity(Vector3 velocity);
	Vector3 getLinearVelocity();

	void setAngularVelocity(Vector3 velocity);
	Vector3 getAngularVelocity();

	void setPosition(Vector3 position);
	Vector3 getPosition();
};