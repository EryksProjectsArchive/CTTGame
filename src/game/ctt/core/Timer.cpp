//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/Timer.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Timer.h"
#include "Logger.h"

#include <os/OS.h>

unsigned long long Timer::s_frameTime = 0ull;
unsigned long long Timer::s_startFrameTime = 0ull;
float Timer::s_deltaTime = 0.0f;
double Timer::s_deltaTimed = 0.0;
float Timer::s_fps = 0;

double Timer::getDeltaTimed()
{
	return s_deltaTimed;
}

float Timer::getDeltaTime()
{
	return s_deltaTime;
}

void Timer::frameStart()
{
	s_startFrameTime = OS::getMicrosecondsCount();
}

void Timer::frameEnd()
{
	s_frameTime = OS::getMicrosecondsCount() - s_startFrameTime;
	s_deltaTime = s_frameTime / 1000000.0f;
	s_deltaTimed = s_frameTime / 1000000.0;

	s_fps = float(1000000 / s_frameTime);
}

float Timer::getFPS()
{
	return s_fps;
}