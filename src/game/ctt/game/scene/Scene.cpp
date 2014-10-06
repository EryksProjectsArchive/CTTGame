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

#include <graphics/FreeCamera.h>
#include <graphics/renderer/RenderContext.h>

Scene::Scene()
{
	m_camera = new FreeCamera();
	Camera::setCurrent(m_camera);	
}

Scene::~Scene()
{
	for (Entity * entity : m_entities)
		delete entity;
	
	m_entities.clear();

	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}
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