//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/Scene.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/List.h>

#include "entities/Entity.h"

class RenderContext;

class Scene
{
private:
	List<Entity *> m_entities;
public:
	Scene();
	~Scene();

	void updatePhysics();

	void addEntity(Entity *entity);

	void render();
};