//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/EditorFreeCamera.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////
#pragma once

#include "Camera.h"

class EditorFreeCamera : public Camera
{
private:
	float m_speed;
	float m_sensitivity;

	bool m_keys[6];

	Quaternion m_rotationX;
	Quaternion m_rotationY;

	Vector3 m_facing;
	bool m_move;

	void updateMatrix();
public:
	EditorFreeCamera();
	~EditorFreeCamera();

	void onMouseMove(int32 x, int32 y, int32 relx, int32 rely) override;
	void onKeyEvent(Key::Type key, bool state) override;
	void onMouseButtonEvent(uint8 button, bool state, uint8, sint32, sint32) override;

	void update(float dt);
};