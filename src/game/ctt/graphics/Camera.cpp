//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Camera.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Camera.h"

Camera * Camera::current = 0;

Camera::Camera() : m_viewMatrix(glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0,1,0)))
{
}

Camera::~Camera()
{

}

void Camera::setPosition(const glm::vec3 & position)
{
	m_position = position;
	m_viewMatrix = glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0));
}

glm::vec3 Camera::getPosition()
{
	return m_position;
}

void Camera::setTarget(const glm::vec3 & position)
{
	m_target = position;
	m_viewMatrix = glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0));
}

glm::vec3 Camera::getTarget()
{
	return m_target;
}

glm::mat4x4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}

void Camera::setCurrent(Camera * camera)
{
	current = camera;
}