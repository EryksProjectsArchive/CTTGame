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

#include "Scene.h"

#include <core/Timer.h>
#include <core/Logger.h>

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

void Scene::render(RenderContext& renderContext)
{
	for (auto entity : m_entities)
		entity->render(renderContext);
}

void Scene::addEntity(Entity *entity)
{
	m_entities.pushBack(entity);
}