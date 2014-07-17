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

#include <core/Game.h>

int main()
{
	Game *game = new Game();
	if (game->init())
	{
		while (game->pulse());
	}
	delete game;
	return 1;
}