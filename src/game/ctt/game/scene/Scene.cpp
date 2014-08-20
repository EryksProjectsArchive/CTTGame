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

Scene::Scene()
{
}

Scene::~Scene()
{
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