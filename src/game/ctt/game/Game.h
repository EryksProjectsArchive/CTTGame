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

class Game : public Singleton<Game>
{
private:
	bool m_isRunning;
	bool m_isInitialized;

	Window* m_window;
	Renderer* m_renderer;
	Scene *m_scene;
	PhysicsWorld *m_physicsWorld;

	bool controlls[4];
	float distance;
	int vertical;

	double m_deltaTime;
	double m_accumulator;
	double m_time;
public:
	Game();
	~Game();

	bool init();

	bool pulse();

	void onKeyEvent(int key, bool state);
	void onMouseScroll(int horizontal, int vertical);

	PhysicsWorld * getPhysicsWorld();
};