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
	{
		if (Game::get()->init()) 
			while (Game::get()->pulse());
	}

#ifdef _MEM_LEAKS_DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 1;
}