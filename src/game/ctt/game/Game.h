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
#include <graphics/ui/controls/UILabel.h>

enum ActiveMoveAxis
{
	None,
	X,
	Y,
	Z
};

class Game : 
	public UI::EventHandler,
	public Application, 
	public Controllable
{
private:
	static Game *s_instance;

	Window* m_window;
	Renderer* m_renderer;
	Scene* m_scene;
	PhysicsWorld* m_physicsWorld;
	Config* m_config;
	class Console* m_console;

	UI::Manager* m_ui;
	UI::Skin* m_skin;
	UI::Label* m_profilerInfo;

	class PhysicalEntity * m_currentPickedEntity;
	bool m_rotate;
	ActiveMoveAxis m_activeMoveAxis;
	Vector3 m_lastMouseWorldPos;
public:
	Game();
	~Game();

	bool init();

	void updateWindow() override;
	void render() override;
	void update(double deltaTime) override;

	void spawnBox();
	void spawnBusStop();

	virtual bool onKeyEvent(Key::Type key, bool state);
	virtual bool onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y);
	virtual bool onMouseScroll(sint32 horizontal, sint32 vertical);

	PhysicsWorld* getPhysicsWorld();
	UI::Manager* getUI();
	Scene* getScene();

	static Game* get();
};
