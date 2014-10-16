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

class Game : public Controllable
{
private:
	static Game *s_instance;

	bool m_isRunning;
	bool m_isInitialized;

	Window* m_window;
	Renderer* m_renderer;
	Scene *m_scene;
	PhysicsWorld *m_physicsWorld;
	Config *m_config;
	class Console *m_console;

	double m_deltaTime;
	double m_accumulator;
	double m_time;
public:
	Game();
	~Game();

	bool init();

	bool pulse();
	void shutdown();

	void onKeyEvent(Key::Type key, bool state) override;
	void onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y) override;

	PhysicsWorld * getPhysicsWorld();

	static Game * get();
};