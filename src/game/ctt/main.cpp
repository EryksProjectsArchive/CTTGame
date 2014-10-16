//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: main.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <game/Game.h>
#include <core/ExceptionHandler.h>

#include <list>
#include <stdio.h>
#include <cstring>

#ifdef _WIN32
#include <Windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main()
#endif
{
	ExceptionHandler::init();
	{
		Game game;
		if (game.init()) 
			while (game.pulse());
	}

#ifdef _MEM_LEAKS_DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 1;
}