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

#include <core/Logger.h>
#include <math/Matrix.h>

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