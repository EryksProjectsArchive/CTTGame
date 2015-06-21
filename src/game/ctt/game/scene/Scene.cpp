//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/Scene.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <core/List.h>
#include <core/Timer.h>
#include <core/Logger.h>

#include "entities/Entity.h"
#include "Scene.h"

#include <graphics/Camera.h>
#include <graphics/renderer/RenderContext.h>

#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

Scene::Scene()
{
	m_camera = new Camera();
	Camera::setCurrent(m_camera);

	// Setup bullet
	m_broadphase = new btDbvtBroadphase();
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	btGImpactCollisionAlgorithm::registerAlgorithm(m_dispatcher);

	m_solver = new btSequentialImpulseConstraintSolver();

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

	m_dynamicsWorld->setGravity(btVector3(0, -6, 0));
}

Scene::~Scene()
{
	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
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

	if (m_dynamicsWorld)
	{
		delete m_dynamicsWorld;
		m_dynamicsWorld = 0;
	}
}

void Scene::updatePhysics()
{
	float delta = Timer::getDeltaTime();
	
	// Update bullet: TODO: Fixed time step calculation
	if (m_dynamicsWorld)
		m_dynamicsWorld->stepSimulation(delta / 10000.0f);
	
	for (auto entity : m_entities)
		entity->updatePhysics();
}

void Scene::render()
{
	// Separated render context for entities
	RenderContext ctx;
	for (auto entity : m_entities)
		entity->render(ctx);
}

void Scene::addEntity(Entity *entity)
{
	m_entities.pushBack(entity);
}