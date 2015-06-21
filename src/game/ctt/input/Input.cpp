//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: input/Input.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Input.h"
#include "Controllable.h"

Input::Input()
	: m_inputState(0)
{
	memset(m_keyState, 0, Key::NUM_SCANCODES);
	m_mouse.x = 0;
	m_mouse.y = 0;
}

Input::~Input()
{

}

void Input::onKeyEvent(Key::Type key, bool pressed)
{
	m_keyState[key] = pressed;

	for (Controllable * controllable : m_controllables)
	{
		if (!isLocked() || controllable->m_type == ControllableType::Engine)
			controllable->onKeyEvent(key, pressed);
	}
}

void Input::onMouseScroll(sint32 horizontal, sint32 vertical)
{
	for (Controllable * controllable : m_controllables)
	{
		if (!isLocked() || controllable->m_type == ControllableType::Engine)
			controllable->onMouseScroll(horizontal, vertical);
	}
}

void Input::onMouseMove(sint32 x, sint32 y, sint32 relx, sint32 rely)
{
	m_mouse.x = x;
	m_mouse.y = y;

	for (Controllable * controllable : m_controllables)
	{
		if (!isLocked() || controllable->m_type == ControllableType::Engine)
			controllable->onMouseMove(x, y, relx, rely);
	}
}

void Input::onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y)
{
	for (Controllable * controllable : m_controllables)
	{
		if (!isLocked() || controllable->m_type == ControllableType::Engine)
			controllable->onMouseButtonEvent(button, state, clicks, x, y);
	}
}

void Input::onTextInput(const WDynString& string)
{
	for (Controllable * controllable : m_controllables)
	{
		if (!isLocked() || controllable->m_type == ControllableType::Engine)
			controllable->onTextInput(string);
	}
}

void Input::lock()
{
	m_inputState++;
}

void Input::unlock()
{
	m_inputState--;
	if (m_inputState < 0)
		m_inputState = 0;
}

bool Input::isLocked()
{
	return m_inputState > 0;
}

bool Input::isKeyDown(Key::Type key)
{
	return m_keyState[key];
}

sint32 Input::getMouseX()
{
	return m_mouse.x;
}

sint32 Input::getMouseY()
{
	return m_mouse.y;
}

void Input::addControllable(Controllable *controllable)
{
	m_controllables.pushBack(controllable);
}

void Input::removeControllable(Controllable *controllable)
{
	m_controllables.remove(controllable);
}