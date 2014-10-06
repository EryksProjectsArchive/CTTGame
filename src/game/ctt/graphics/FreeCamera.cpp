//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/FreeCamera.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "FreeCamera.h"

#include <core/Logger.h>

#include <SDL.h>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

FreeCamera::FreeCamera()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(0);
	for (unsigned int i = 0; i < 4; ++i)
		m_keys[i] = false;

	m_position = Vector3(10, 10, 0);
	m_target = Vector3(0, 0, 0);
	m_speed = 25.f;
	m_sensitivity = 0.75f;
}

FreeCamera::~FreeCamera()
{

}

void FreeCamera::onMouseMove(int x, int y, int relx, int rely)
{
	float _x = (float)relx * m_sensitivity;
	float _y = (float)rely * m_sensitivity;

	Vector3 axis = glm::normalize(glm::cross(m_target - m_position, Vector3(0, 1, 0)));

	m_rotation = glm::rotate(m_rotation, _y, axis);
	m_rotation = glm::rotate(m_rotation, _x, Vector3(0,1,0));

	glm::mat3 rot = glm::mat3_cast(m_rotation);
	m_target = m_position + Vector3(rot[0][2], rot[1][2], rot[2][2]);
	m_viewMatrix = glm::lookAt(m_position, m_target, Vector3(0, 1, 0));
}

void FreeCamera::onKeyEvent(int key, bool state)
{
	if (key == 'w')
		m_keys[0] = state;

	if (key == 's')
		m_keys[1] = state;

	if (key == 'a')
		m_keys[2] = state;

	if (key == 'd')
		m_keys[3] = state;
}

void FreeCamera::update(float dt)
{
	bool update = false;
	if (m_keys[0])
	{
		m_position += ((m_target - m_position) * m_speed) * dt;
		update = true;
	}

	if (m_keys[1])
	{
		m_position -= ((m_target - m_position) * m_speed) * dt;
		update = true;
	}

	if (m_keys[2])
	{
		Vector3 direction = glm::cross(m_target - m_position, Vector3(0,1,0));
		m_position -= (direction * m_speed) * dt;
		update = true;
	}

	if (m_keys[3])
	{
		Vector3 direction = glm::cross(m_target - m_position, Vector3(0, 1, 0));
		m_position += (direction * m_speed) * dt;
		update = true;
	}

	if (update)
	{
		glm::mat4 rot = glm::mat4_cast(m_rotation);
		m_target = m_position + Vector3(rot[0][2], rot[1][2], rot[2][2]);
		m_viewMatrix = glm::lookAt(m_position, m_target, Vector3(0, 1, 0));
	}
}