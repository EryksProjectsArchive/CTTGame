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

Camera::Camera() : m_viewMatrix(glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))), m_fov(45.f)
{
}

Camera::~Camera()
{

}

void Camera::setPosition(const glm::vec3 & position)
{
	m_position = position;
	m_viewMatrix = glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0)) * glm::mat4_cast(m_rotation);
}

glm::vec3 Camera::getPosition()
{
	return m_position;
}

void Camera::setTarget(const glm::vec3 & position)
{
	m_target = position;
	m_viewMatrix = glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0)) * glm::mat4_cast(m_rotation);
}

glm::vec3 Camera::getTarget()
{
	return m_target;
}

void Camera::setRotation(const glm::quat & rotation)
{
	m_rotation = rotation;	
	m_viewMatrix *= glm::mat4_cast(m_rotation);
}

glm::quat Camera::getRotation()
{
	return m_rotation;
}

void Camera::setFov(float fov)
{
	m_fov = fov;
}

float Camera::getFov()
{
	return m_fov;
}

glm::mat4x4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}

void Camera::setCurrent(Camera * camera)
{
	current = camera;
}