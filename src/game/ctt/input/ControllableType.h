//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: input/ControllableType.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

struct ControllableType
{
	enum Type
	{
		// Highest priority - unable to "freeze etc etc"
		Engine = 0, 
		
		// Lowest priority - gameplay controllables
		Gameplay = 1
	};
};