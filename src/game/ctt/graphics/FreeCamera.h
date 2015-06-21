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

	Vector3 m_velocity;
	Vector3 m_facing;

	void updateMatrix();
public:
	FreeCamera();
	~FreeCamera();

	virtual bool onMouseMove(int32 x, int32 y, int32 relx, int32 rely);
	virtual bool onKeyEvent(Key::Type key, bool state);

	void update(float dt);

	DEFINE_CAMERA_TYPE(FREE);
};