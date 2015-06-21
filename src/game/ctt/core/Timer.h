//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/Timer.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

class Timer
{
private:
	static unsigned long long s_frameTime;
	static unsigned long long s_startFrameTime;
	static double s_deltaTimed;
	static float s_deltaTime;
public:
	static double getDeltaTimed();
	static float getDeltaTime();

	static void frameStart();
	static void frameEnd();
};