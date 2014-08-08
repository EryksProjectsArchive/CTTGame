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
	Game game;
	if (game.init()) while (game.pulse());
	return 1;
}