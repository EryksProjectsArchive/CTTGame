//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/environment/Environment.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <core/Singleton.h>

struct EnvironmentStates
{
	enum Type
	{
		Day,
		Night,
		Count
	};
};

struct EnvironmentState
{
	glm::vec3 sunPosition;
	glm::vec3 sunLightColor;
	glm::vec3 sunAmbientColor;
	float sunLightPower;
	unsigned char interpStart;
	unsigned char interpEnd;

	EnvironmentState()
	{
		sunLightPower = 0;
	}

	EnvironmentState(glm::vec3 position, glm::vec3 lightColor, glm::vec3 ambientColor, float lightPower, unsigned char _interpStart, unsigned char _interpEnd)
	{
		sunPosition = position;
		sunLightColor = lightColor;
		sunAmbientColor = ambientColor;
		sunLightPower = lightPower;
		interpStart = _interpStart;
		interpEnd = _interpEnd;
	}
};

class Environment : public Singleton < Environment >
{
private:
	glm::vec3 m_sunPosition;
	float m_sunLightPower;
	glm::vec3 m_sunLightColor;
	glm::vec3 m_sunAmbientColor;

	unsigned int m_time;	

	EnvironmentState m_states[EnvironmentStates::Count];
	EnvironmentStates::Type m_currentState;
	EnvironmentStates::Type m_nextState;
	struct
	{
		unsigned char start;
		unsigned char end;
		unsigned char current;
		bool interpolating;
	} m_stateInterpolation;

	unsigned int m_timeScale;
	unsigned long long m_lastTimeUpdate;

	void interpolateStates();
public:
	Environment();
	~Environment();

	void setSunPosition(glm::vec3 position);
	glm::vec3 getSunPosition();

	bool isNight();

	void setTime(unsigned char hour, unsigned char minute);
	unsigned char getHour();
	unsigned char getMinute();

	void pulse();

	glm::vec3 getSunLightColor();
	float getSunLightPower();
	glm::vec3 getSunAmbientColor();
};