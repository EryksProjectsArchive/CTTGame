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

#include <graphics/EditorFreeCamera.h>
#include <graphics/renderer/RenderContext.h>

#include <game/environment/Terrain.h>

Scene::Scene()
	: m_camera(0), m_terrain(0)
{
	m_camera = new EditorFreeCamera();
	Camera::setCurrent(m_camera);
	m_terrain = new Terrain(10000, 10000);

	Console::get()->addCommand(new SceneInfoCommand(this));
	Console::get()->addCommand(new ClearSceneCommand(this));
}

Scene::~Scene()
{
	clear();

	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}

	if (m_terrain)
	{
		delete m_terrain;
		m_terrain = 0;
	}
}

#include <game/Game.h>
#include <physics/PhysicsWorld.h>

void Scene::render()
{
	{
		// Separated render context for entities
		RenderContext ctx;

		if (m_terrain)
			m_terrain->render(ctx);

		for (auto entity : m_entities)
			entity->render(ctx);

		// Render physics world (debug)
		Game::get()->getPhysicsWorld()->render(ctx);
	}
}

void Scene::addEntity(Entity *entity)
{
	m_entities.pushBack(entity);
}

void Scene::clear()
{
	for (Entity * entity : m_entities)
	{
		delete entity;
	}

	m_entities.clear();
}

Scene::SceneInfoCommand::SceneInfoCommand(Scene * scene)
	: Console::ICommand(L"sceneinfo", L"Prints informations about scene")
{
	m_scene = scene;
}

void Scene::SceneInfoCommand::onExecute(const WDynString& params)
{
	m_console->output(Console::MessageType::Info, L"Scene info:");
	m_console->output(Console::MessageType::Info, WString<64>(L"There are %d spawned entities", m_scene->m_entities.size()));
	Vector3 camPos = m_scene->m_camera->getPosition();
	m_console->output(Console::MessageType::Info, WString<128>(L"Current cam pos: %f, %f, %f", camPos.x, camPos.y, camPos.z));
}

Scene::ClearSceneCommand::ClearSceneCommand(Scene * scene)
	: Console::ICommand(L"clearscene", L"Removes all entities from world")
{
	m_scene = scene;
}

void Scene::ClearSceneCommand::onExecute(const WDynString& params)
{
	if (m_scene)
		m_scene->clear();
}