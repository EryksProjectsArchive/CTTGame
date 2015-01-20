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
	Timer::frameStart();

	updateWindow();

	double time = double(OS::getMicrosecondsCount() / 1000000.f);
	double frameTime = time - m_time;
	if (frameTime > 0.25)
		frameTime = 0.25;
	m_time = time;

	m_accumulator += frameTime;

	while (m_accumulator >= m_deltaTime)
	{
		update(m_deltaTime);
		m_accumulator -= m_deltaTime;
	}

	render();

	Timer::frameEnd();
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