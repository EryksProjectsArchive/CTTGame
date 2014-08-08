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

#include <graphics/Window.h>
#include <sound/SoundMgr.h>

class IRenderer;

class Game
{
private:
	bool m_isRunning;
	bool m_isInitialized;

	IWindow * m_window;
	IRenderer * m_renderer;
	ISoundMgr * m_soundMgr;
public:
	Game();
	~Game();

	bool init();

	bool pulse();
};