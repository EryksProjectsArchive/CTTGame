//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: physics/PhysicsWorld.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "PhysicsWorld.h"

#include <core/Timer.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

PhysicsWorld::PhysicsWorld()
	: m_dynamicsWorld(0), m_broadphase(0), m_collisionConfiguration(0), m_dispatcher(0), m_solver(0), m_initialized(false)
{

}

PhysicsWorld::~PhysicsWorld()
{
	if (m_dynamicsWorld)
	{
		delete m_dynamicsWorld;
		m_dynamicsWorld = 0;
	}

	if (m_broadphase)
	{
		delete m_broadphase;
		m_broadphase = 0;
	}

	if (m_collisionConfiguration)
	{
		delete m_collisionConfiguration;
		m_collisionConfiguration = 0;
	}

	if (m_dispatcher)
	{
		delete m_dispatcher;
		m_dispatcher = 0;
	}

	if (m_solver)
	{
		delete m_solver;
		m_solver = 0;
	}
}

bool PhysicsWorld::init()
{
	if (m_initialized)
		return false;

	// Setup bullet
	if (!(m_broadphase = new btDbvtBroadphase()))
	{
		return false;
	}

	if (!(m_collisionConfiguration = new btDefaultCollisionConfiguration()))
	{
		return false;
	}

	if (m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration))
	{
		btGImpactCollisionAlgorithm::registerAlgorithm(m_dispatcher);
	}
	else
	{
		return false;
	}

	if (!(m_solver = new btSequentialImpulseConstraintSolver()))
	{
		return false;
	}

	if (m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration))
	{
		// Set basic world paramters
		m_dynamicsWorld->setGravity(btVector3(0, -10, 0));
	}
	else
	{
		return false;
	}

	m_initialized = true;
	return true;
}

void PhysicsWorld::pulse()
{
	for (PhysicalEntity *entity : m_entities)
		entity->prePhysicsUpdate();

	// TODO: Fixed timestep
	if (m_dynamicsWorld)
	{
		m_dynamicsWorld->stepSimulation(Timer::getDeltaTime() / 40.0f, 1);
	}

	for (PhysicalEntity *entity : m_entities)
		entity->postPhysicsUpdate();
}

void PhysicsWorld::registerEntity(PhysicalEntity * entity)
{
	m_entities.pushBack(entity);
}

void PhysicsWorld::unregisterEntity(PhysicalEntity * entity)
{
	m_entities.remove(entity);
}

void PhysicsWorld::registerRigidBody(btRigidBody *rigidBody)
{
	if (m_dynamicsWorld)
		m_dynamicsWorld->addRigidBody(rigidBody);
}

void PhysicsWorld::unregisterRigidBody(btRigidBody *rigidBody)
{
	if (m_dynamicsWorld)
		m_dynamicsWorld->removeRigidBody(rigidBody);
}