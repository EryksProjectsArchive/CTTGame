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

// Application stuffs.
#include <game/Game.h>

// Engine stuffs.
#include <core/ExceptionHandler.h>

#include <os/OS.h>

#ifdef _WIN32
int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int)
#else
int main()
#endif
{
	// Initialize exception handler
	ExceptionHandler::init();

	// Initialize time
	OS::initTime();

#ifdef EDITOR
	//Application *app = new Editor();
#else
	Application *app = new Game();
#endif
	if (app->init())
	{
		while (app->pulse());
	}

	delete app;

#ifdef _MEM_LEAKS_DEBUG
	_CrtDumpMemoryLeaks();
#endif

#ifdef _WIN32
	return S_OK;
#else
	return 1;
#endif
}