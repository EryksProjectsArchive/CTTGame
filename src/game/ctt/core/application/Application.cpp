//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/application/Application.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Application.h"

#include <os/OS.h>
#include <core/Timer.h>

#include <core/performance/Profiler.h>

Profiler g_frameProfiler;
Profiler g_physicsUpdateProfiler;

Application::Application() : m_isInitialized(false), m_isRunning(false)
{

}

Application::~Application()
{

}

bool Application::init()
{
	if (m_isInitialized)
		return false;

	m_time = double(OS::getMicrosecondsCount() / 1000000);
	m_accumulator = 0.0;
	m_deltaTime = 1 / 60.0f;
	return true;
}

bool Application::pulse()
{
	g_frameProfiler.start();
	Timer::frameStart();

	updateWindow();

	g_physicsUpdateProfiler.start();
	double time = double(OS::getMicrosecondsCount() / double(1000 * 1000));
	double frameTime = time - m_time;
	if (frameTime > m_deltaTime)
		frameTime = m_deltaTime;
	m_time = time;

	m_accumulator += frameTime;
	m_physicsTicks = 0;
	while (m_accumulator >= m_deltaTime)
	{
		update(m_deltaTime);
		m_accumulator -= m_deltaTime;
		m_physicsTicks++;
	}
	g_physicsUpdateProfiler.end();

	render();

	Timer::frameEnd();
	g_frameProfiler.end();
	return m_isRunning;
}

void Application::updateWindow()
{
}

void Application::render()
{
}

void Application::update(double deltaTime)
{
}

void Application::shutdown()
{
	m_isRunning = false;
}