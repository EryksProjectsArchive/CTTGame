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
	btCollisionShape *m_collisionShape;

	Matrix4x4 m_transform;
public:
	PhysicalEntity();
	~PhysicalEntity();

	virtual void prePhysicsUpdate() {};
	virtual void postPhysicsUpdate() {};

	virtual void setLinearVelocity(Vector3 velocity);
	virtual Vector3 getLinearVelocity();

	virtual void setAngularVelocity(Vector3 velocity);
	virtual Vector3 getAngularVelocity();

	virtual void setPosition(Vector3 position);
	virtual Vector3 getPosition();

	virtual void setRotation(Quaternion rotation);
	virtual Quaternion getRotation();

	virtual float getHeight();
	virtual float getWidth();

	virtual bool isDynamic();

	virtual void setMass(float mass);
	virtual void setFriction(float friction);

protected:
	// ---- Methods for all class that inherits from physical entity -----
	virtual void setupPhysics(btCollisionShape * shape);
};