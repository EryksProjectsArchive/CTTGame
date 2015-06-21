//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/environment/Environment.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Environment.h"

#include <core/Logger.h>
#include <os/OS.h>
#include <core/Timer.h>

Environment::Environment() : m_time(5*60)
{
	m_sunAmbientColor = Vector3(0.8f, 0.8f, 0.8f);
	m_sunLightColor = Vector3(1.0f, 207/255, 114/255);
	m_sunLightPower = 10.0f;
	m_sunPosition = Vector3(0.0f, 10.0f, 0.0f);

	m_timeScale = 1000;
	m_deltaUpdate = 0;
}

Environment::~Environment()
{

}

void Environment::setSunPosition(Vector3 position)
{
	m_sunPosition = position;
}

glm::vec3 Environment::getSunPosition()
{
	return m_sunPosition;
}

bool Environment::isNight()
{
	return m_time <= 5 * 60 && m_time >= 20 * 60;
}

void Environment::setTime(unsigned char hour, unsigned char minute)
{
	m_time = hour * 60 + minute;
}

unsigned char Environment::getHour()
{
	return m_time / 60 % 24;
}

unsigned char Environment::getMinute()
{
	return m_time % 60;
}

void Environment::pulse()
{
	int timeElapsed = 0;
	float timeScale = (float)m_timeScale / 100.0f;

	m_deltaUpdate += Timer::getDeltaTime();
	while(m_deltaUpdate >= timeScale)
	{
		timeElapsed++;
		m_deltaUpdate -= timeScale;
	}
		
	if (timeElapsed > 0)
	{
		m_time += timeElapsed;
	}
}

Vector3 Environment::getSunLightColor()
{
	return m_sunLightColor;
}

float Environment::getSunLightPower()
{
	return m_sunLightPower;
}

Vector3 Environment::getSunAmbientColor()
{
	return m_sunAmbientColor;
}