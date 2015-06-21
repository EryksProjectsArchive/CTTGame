//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Camera.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <input/Controllable.h>

#include "CameraManager.h"

class Camera : public Controllable
{
protected:
	glm::mat4x4 m_viewMatrix;

	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::quat m_rotation;
	float m_fov;

	bool m_isActive;
public:
	Camera();
	virtual ~Camera();

	virtual void activate();
	virtual void deactivate();
	virtual bool isActive();

	virtual void setPosition(const glm::vec3 & position);
	virtual glm::vec3 getPosition();

	virtual void setTarget(const glm::vec3 & position);
	virtual glm::vec3 getTarget();

	virtual void setRotation(const glm::quat & rotation);
	virtual glm::quat getRotation();

	virtual void setFov(float fov);
	virtual float getFov();

	virtual void update(float dt) {};
	
	virtual glm::mat4x4 getViewMatrix();

	DEFINE_CAMERA_TYPE(STATIC);
};