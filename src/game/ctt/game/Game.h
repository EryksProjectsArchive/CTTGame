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

class Window;
class Renderer;
class ISoundMgr;
class FileSystem;
class Scene;

class Game
{
private:
	bool m_isRunning;
	bool m_isInitialized;

	Window* m_window;
	Renderer* m_renderer;
	ISoundMgr* m_soundMgr;

	FileSystem *m_fileSystem;

	Scene *m_scene;
public:
	Game();
	~Game();

	bool init();

	bool pulse();
};