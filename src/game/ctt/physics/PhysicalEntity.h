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

class PhysicalEntity
{
protected:
	btRigidBody *m_rigidBody;

public:
	PhysicalEntity();
	~PhysicalEntity();

	virtual void prePhysicsUpdate() = 0;
	virtual void postPhysicsUpdate() = 0;
};