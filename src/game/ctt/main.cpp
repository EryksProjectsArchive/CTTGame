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

#undef _WIN32
#ifdef _WIN32
int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int)
#else
int main()
#endif
{
	ExceptionHandler::init();
	{
#ifdef EDITOR
		//Application *app = new Editor();
		// TODO
#else
		Application *app = new Game();
#endif
		if (app->init()) 
			while (app->pulse());

		delete app;
	}

#ifdef _MEM_LEAKS_DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 1;
}