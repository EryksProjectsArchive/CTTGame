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
	Vector3 m_velocity;
	bool m_move;

	void updateMatrix();
public:
	EditorFreeCamera();
	~EditorFreeCamera();

	bool onMouseMove(int32 x, int32 y, int32 relx, int32 rely) override;
	bool onKeyEvent(Key::Type key, bool state) override;
	bool onMouseButtonEvent(uint8 button, bool state, uint8, sint32, sint32) override;

	bool isMoving();
	void update(float dt);

	DEFINE_CAMERA_TYPE(EDITOR_FREE);
};