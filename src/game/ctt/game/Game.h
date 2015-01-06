//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/Game.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/Singleton.h>

#include <input/Input.h>

#include <core/application/Application.h>

#include <graphics/ui/UIEventHandler.h>

class Game : public Application, public Controllable, public UI::EventHandler
{
private:
	static Game *s_instance;

	Window* m_window;
	Renderer* m_renderer;
	Scene* m_scene;
	PhysicsWorld* m_physicsWorld;
	Config* m_config;
	class Console* m_console;
	class CrossroadEntity* m_box;

	UI::Manager* m_ui;
public:
	Game();
	~Game();

	bool init();

	void updateWindow() override;
	void render() override;
	void update(double deltaTime) override;

	void spawnBox();

	void onKeyEvent(Key::Type key, bool state) override;
	void onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y) override;

	PhysicsWorld& getPhysicsWorld();
	UI::Manager& getUI();
	Scene& getScene();

	static Game* get();
};