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

#include <functional>

int function1(int x)
{
	return 0;
}

std::function<void()> f;
void testFunction2(void)
{
	f = std::bind(function1, 2);
}

int main()
{
	testFunction2();

	Game *game = new Game();
	if (game->init())
	{
		while (game->pulse());
	}
	delete game;
	return 1;
}