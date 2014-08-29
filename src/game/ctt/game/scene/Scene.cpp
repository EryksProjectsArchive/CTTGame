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

Scene::Scene()
{
	m_camera = new Camera();
	Camera::setCurrent(m_camera);
}

Scene::~Scene()
{
	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}
}

void Scene::updatePhysics()
{
	for (auto entity : m_entities)
		entity->updatePhysics();
}

void Scene::render()
{
	for (auto entity : m_entities)
		entity->render();
}

void Scene::addEntity(Entity *entity)
{
	m_entities.pushBack(entity);
}