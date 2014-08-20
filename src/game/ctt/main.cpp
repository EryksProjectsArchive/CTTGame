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

int main()
{
	Game *game = new Game();
	if (game->init()) while (game->pulse());
	delete game;

#ifdef _MEM_LEAKS_DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 1;
}