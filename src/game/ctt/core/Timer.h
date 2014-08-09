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

class Timer
{
private:
	static unsigned long long s_frameTime;
	static unsigned long long s_startFrameTime;
	static double s_deltaTime;
	static float s_deltaTimeF;
public:
	static double getDeltaTime();
	static float getDeltaTimef();

	static void frameStart();
	static void frameEnd();
};