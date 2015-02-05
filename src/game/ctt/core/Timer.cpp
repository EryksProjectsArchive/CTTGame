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
float Timer::s_timeToUpdateFPS = 1.0f;

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

	s_timeToUpdateFPS -= s_deltaTime;
	if (s_timeToUpdateFPS <= 0.0f)
	{
		s_fps = float(float(1000 * 1000) / s_frameTime);
		s_timeToUpdateFPS = 1.0f;
	}
}

float Timer::getFPS()
{
	return s_fps;
}