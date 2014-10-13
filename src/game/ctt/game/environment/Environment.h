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


class Environment : public Singleton<Environment>
{
private:
	Vector3 m_sunPosition;
	float m_sunLightPower;
	Vector3 m_sunLightColor;
	Vector3 m_sunAmbientColor;

	unsigned int m_time;	
	unsigned int m_timeScale;
	float m_deltaUpdate;
public:
	Environment();
	~Environment();

	void setSunPosition(const Vector3 position);
	Vector3 getSunPosition();

	bool isNight();

	void setTime(unsigned char hour, unsigned char minute);
	unsigned char getHour();
	unsigned char getMinute();

	void pulse();

	Vector3 getSunLightColor();
	float getSunLightPower();
	Vector3 getSunAmbientColor();
};