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
		controllable->onKeyEvent(key, pressed);
}

void Input::onMouseScroll(sint32 horizontal, sint32 vertical)
{
	for (Controllable * controllable : m_controllables)
		controllable->onMouseScroll(horizontal, vertical);
}

void Input::onMouseMove(sint32 x, sint32 y, sint32 relx, sint32 rely)
{
	m_mouse.x = x;
	m_mouse.y = y;

	for (Controllable * controllable : m_controllables)
		controllable->onMouseMove(x, y, relx, rely);
}

void Input::onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y)
{
	for (Controllable * controllable : m_controllables)
		controllable->onMouseButtonEvent(button, state, clicks, x, y);
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