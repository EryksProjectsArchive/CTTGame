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

Environment::Environment() : m_time(0)
{
	m_states[EnvironmentStates::Day] = EnvironmentState(Vector3(30.0f, 10.0f, 0.0f), glm::vec3(1, 1, 1), glm::vec3(0.96f, 0.92f, 0.76f), 100.0f, 5, 6);
	m_states[EnvironmentStates::Night] = EnvironmentState(Vector3(30.0f, 10.0f, 0.0f), glm::vec3(1, 1, 1), glm::vec3(0.03f, 0.09f, 0.25f), 50.0f, 20, 22);

	m_currentState = EnvironmentStates::Day;
	m_nextState = EnvironmentStates::Night;

	m_sunAmbientColor = m_states[m_currentState].sunAmbientColor;
	m_sunLightColor = m_states[m_currentState].sunLightColor;
	m_sunLightPower = m_states[m_currentState].sunLightPower;
	m_sunPosition = m_states[m_currentState].sunPosition;

	m_timeScale = 1000; // 1 minute per 1 second (To be fixed soon)
	m_lastTimeUpdate = OS::getMicrosecondsCount() / 1000;
}

Environment::~Environment()
{

}

void Environment::setSunPosition(glm::vec3 position)
{
	m_sunPosition = position;
}

glm::vec3 Environment::getSunPosition()
{
	return m_sunPosition;
}

bool Environment::isNight()
{
	return m_currentState == 1;
}

void Environment::setTime(unsigned char hour, unsigned char minute)
{
	m_time = (hour << 8) | minute;
}

unsigned char Environment::getHour()
{
	return (m_time >> 8) & 0xFF;
}

unsigned char Environment::getMinute()
{
	return m_time & 0xFF;
}

void Environment::pulse()
{
	unsigned char minute = m_time & 0xFF;
	unsigned char hour = (m_time >> 8) & 0xFF;

	unsigned long long now = OS::getMicrosecondsCount() / 1000;
	unsigned char minElapsed = ((now - m_lastTimeUpdate) / m_timeScale) &0xFF;
	
	if (minElapsed > 0)
	{
		minute += minElapsed;
		if (minute > 59)
		{
			minute = 0;
			if (++hour >= 24)
			{
				hour = 0;
			}
		}
		m_lastTimeUpdate = now;
	}

	m_time = (hour << 8) | minute;

	interpolateStates();
}

glm::vec3 Environment::getSunLightColor()
{
	return m_sunLightColor;
}

float Environment::getSunLightPower()
{
	return m_sunLightPower;
}

glm::vec3 Environment::getSunAmbientColor()
{
	return m_sunAmbientColor;
}

void Environment::interpolateStates()
{
	if (true) // disable interpolateStates - we dont need it for now
		return;

	bool interpStart = getHour() == m_states[m_nextState].interpStart;
	bool start = interpStart && !m_stateInterpolation.interpolating;

	if (m_stateInterpolation.interpolating || start)
	{
		unsigned char hour = getHour();
		unsigned char minutes = getMinute();
		if (start)
		{
			m_stateInterpolation.start = hour * 60 + minutes;
			m_stateInterpolation.end = m_stateInterpolation.start + m_states[m_nextState].interpEnd * 60;
			m_stateInterpolation.interpolating = true;
		}
		m_stateInterpolation.current = hour * 60 + minutes;

		float alpha = (float)(m_stateInterpolation.current - m_stateInterpolation.start) / (m_stateInterpolation.end - m_stateInterpolation.start);

		bool interpEnd = false;
		if (alpha >= 1.0f)
		{
			alpha = 1.0f;

			interpEnd = true;
		}

		glm::vec3 start = m_states[m_currentState].sunLightColor;
		glm::vec3 end = m_states[m_nextState].sunLightColor;
		m_sunLightColor = start + (end - start) * alpha;

		start = m_states[m_currentState].sunAmbientColor;
		end = m_states[m_nextState].sunAmbientColor;
		m_sunAmbientColor = start + (end - start) * alpha;

		float _start = m_states[m_currentState].sunLightPower;
		float _end = m_states[m_nextState].sunLightPower;
		m_sunLightPower = _start + (_end - _start) * alpha;

		start = m_states[m_currentState].sunPosition;
		end = m_states[m_nextState].sunPosition;
		m_sunPosition = start + (end - start) * alpha;

		if (interpEnd)
		{
			EnvironmentStates::Type tmp = m_currentState;
			m_currentState = m_nextState;
			m_nextState = tmp;
			m_stateInterpolation.interpolating = false;
		}
	}
}