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
	s_deltaTime = s_frameTime * 0.00001f;
	s_deltaTimed = s_frameTime * 0.00001;
}