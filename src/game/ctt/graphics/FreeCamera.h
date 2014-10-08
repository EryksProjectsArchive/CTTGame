//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/FreeCamera.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////
#pragma once

#include "Camera.h"

class FreeCamera : public Camera
{
private:
	float m_speed;
	float m_sensitivity;

	bool m_keys[6];

	Quaternion m_rotationX;
	Quaternion m_rotationY;

	Vector3 m_facing;

	void updateMatrix();
public:
	FreeCamera();
	~FreeCamera();

	void onMouseMove(int x, int y, int relx, int rely);

	void onKeyEvent(int key, bool state);

	void update(float dt);
};