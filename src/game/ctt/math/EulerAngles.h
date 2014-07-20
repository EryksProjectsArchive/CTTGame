//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: math/EulerAngles.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class EulerAngles
{
public:
	float yaw, pitch, roll;

	EulerAngles()
	{
		yaw = pitch = roll = 0;
	}

	EulerAngles(const EulerAngles& angles)
	{
		yaw = angles.yaw;
		pitch = angles.pitch;
		roll = angles.roll;
	}

	EulerAngles(float yaw, float pitch, float roll)
	{
		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
	}
};