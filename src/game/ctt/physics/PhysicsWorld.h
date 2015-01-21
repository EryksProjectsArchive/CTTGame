//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: physics/PhysicsWorld.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <btBulletDynamicsCommon.h>

#include <core/List.h>

#include "PhysicalEntity.h"

class PhysicsWorld
{
private:
	btBroadphaseInterface* m_broadphase;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btCollisionDispatcher* m_dispatcher;
	btSequentialImpulseConstraintSolver* m_solver;
	btDiscreteDynamicsWorld* m_dynamicsWorld;
	btIDebugDraw * m_debugDrawer;

	bool m_initialized;

	List<PhysicalEntity *> m_entities;

	void internalPulse(float delta);
public:
	PhysicsWorld();
	~PhysicsWorld();

	bool init();

	void pulse(float dt);
	void render(RenderContext& context);

	void registerEntity(PhysicalEntity * entity);
	void unregisterEntity(PhysicalEntity * entity);

	void registerRigidBody(btRigidBody *rigidBody);
	void unregisterRigidBody(btRigidBody *rigidBody);

	bool rayTest(Vector3 begin, Vector3 end, Vector3 * position, PhysicalEntity ** entity = 0);

	btDiscreteDynamicsWorld * getDynamicsWorld();
};