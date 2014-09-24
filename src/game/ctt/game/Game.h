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

	bool controlls[4];
	float distance;
public:
	Game();
	~Game();

	bool init();

	bool pulse();

	void onKeyEvent(int key, bool state);
	void onMouseScroll(int horizontal, int vertical);
};