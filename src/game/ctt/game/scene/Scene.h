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

#include <Prerequisites.h>

#include <core/List.h>
#include <core/Singleton.h>

#include <core/console/Console.h>

class Scene
{
private:
	List<Entity *> m_entities;

	Camera * m_camera;

	Terrain *m_terrain;
public:
	Scene();
	~Scene();

	void addEntity(Entity *entity);

	void render();

	class SceneInfoCommand : public Console::ICommand
	{
	private:
		Scene * m_scene;
	public:
		SceneInfoCommand(Scene * scene);
		void onExecute(const WDynString& params);
	};
};