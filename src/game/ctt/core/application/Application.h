//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/application/Application.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

class Application
{
protected:
	bool m_isRunning;
	bool m_isInitialized;

	double m_deltaTime;
	double m_accumulator;
	double m_time;

	uint32 m_physicsTicks;

	virtual void render();
	virtual void update(double deltaTime);
	virtual void updateWindow();
public:
	Application();
	virtual ~Application();
	virtual bool init();

	virtual bool pulse();
	virtual void shutdown();
};