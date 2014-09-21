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

class Camera
{
protected:
	glm::mat4x4 m_viewMatrix;

	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::quat m_rotation;
	float m_fov;
public:
	Camera();
	~Camera();

	void setPosition(const glm::vec3 & position);
	glm::vec3 getPosition();

	void setTarget(const glm::vec3 & position);
	glm::vec3 getTarget();

	void setRotation(const glm::quat & rotation);
	glm::quat getRotation();

	void setFov(float fov);
	float getFov();
	
	glm::mat4x4 getViewMatrix();
	
	static void setCurrent(Camera *);
	static Camera * current;
};