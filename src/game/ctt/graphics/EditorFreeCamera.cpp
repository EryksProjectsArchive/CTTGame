//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/EditorFreeCamera.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "EditorFreeCamera.h"

#include <core/Logger.h>

#include <SDL.h>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <game/Game.h>
#include <physics/PhysicsWorld.h>

EditorFreeCamera::EditorFreeCamera()
{
	m_move = false;
	for (unsigned int i = 0; i < 6; ++i)
		m_keys[i] = false;

	m_position = Vector3(10, 10, 0);
	m_target = Vector3(0, 0, 0);
	m_speed = 25.f;
	m_sensitivity = 0.15f;
	updateMatrix();
}

EditorFreeCamera::~EditorFreeCamera()
{

}

void EditorFreeCamera::onMouseMove(int32 x, int32 y, int32 relx, int32 rely)
{
	if (!m_move)
		return;

	float _x = (float)relx * m_sensitivity;
	float _y = (float)rely * m_sensitivity;

	m_rotationX = glm::rotate(m_rotationX, glm::radians(_x), Vector3(0, 1, 0));
	m_rotationY = glm::rotate(m_rotationY, glm::radians(_y), Vector3(1, 0, 0));

	updateMatrix();
}

void EditorFreeCamera::onKeyEvent(Key::Type key, bool state)
{
	if (key == Key::SCANCODE_W)
		m_keys[0] = state;

	if (key == Key::SCANCODE_S)
		m_keys[1] = state;

	if (key == Key::SCANCODE_A)
		m_keys[2] = state;

	if (key == Key::SCANCODE_D)
		m_keys[3] = state;

	if (key == Key::SCANCODE_E)
		m_keys[4] = state;

	if (key == Key::SCANCODE_Q)
		m_keys[5] = state;

	if (key == Key::SCANCODE_LSHIFT) // shift
		m_speed = state ? 300.0f : 25.0f;

	else if (key == Key::SCANCODE_LCTRL) // ctrl
		m_speed = state ? 0.1f : 25.0f;
}

bool EditorFreeCamera::isMoving()
{
	return m_move;
}

void EditorFreeCamera::onMouseButtonEvent(uint8 button, bool state, uint8, sint32, sint32)
{
	if (button == 3)
	{
		m_move = state;	
		Input::get()->showCursor(!m_move);
	}
}

void EditorFreeCamera::update(float dt)
{
	bool processKeys = true;
	if (input()->isLocked())
	{
		for (unsigned int i = 0; i < 6; ++i)
			m_keys[i] = false;

		Input::get()->showCursor(true);

		processKeys = false;
	}

	if (processKeys)
	{
		Vector3 begin = m_position;
		Vector3 forwardVelocity;
		Vector3 sideVelocity;

		bool update = false;
		if (m_keys[0])
		{
			forwardVelocity = glm::normalize(m_target - begin);
			update = true;
		}

		if (m_keys[1])
		{
			forwardVelocity = -glm::normalize(m_target - begin);
			update = true;
		}

		if (m_keys[2])
		{
			Vector3 direction = glm::cross(m_facing - begin, Vector3(0, 1, 0));
			sideVelocity = -glm::normalize(direction);
			update = true;
		}

		if (m_keys[3])
		{
			Vector3 direction = glm::cross(m_facing - begin, Vector3(0, 1, 0));
			sideVelocity = glm::normalize(direction);
			update = true;
		}

		if (update)
		{
			m_velocity += (forwardVelocity + sideVelocity);
			m_velocity = glm::normalize(m_velocity);
		}

		if (m_keys[4])
			m_velocity.y = 1.f;

		if (m_keys[5])
			m_velocity.y = -1.f;
	}
		
	if (m_velocity.length() > 0)
	{
		m_position += m_velocity * m_speed * dt;
		updateMatrix();

		m_velocity /= Vector3(1.08f);
	}
}

void EditorFreeCamera::updateMatrix()
{
	glm::mat4 matRotationX = glm::mat4_cast(m_rotationX);
	m_viewMatrix = glm::mat4_cast(m_rotationY) * matRotationX * glm::translate(glm::mat4(), Vector3(-m_position.x, -m_position.y, -m_position.z));
	m_target = m_position + Vector3(-m_viewMatrix[0][2], -m_viewMatrix[1][2], -m_viewMatrix[2][2]);
	m_facing = m_position + Vector3(-matRotationX[0][2], -matRotationX[1][2], -matRotationX[2][2]);
}