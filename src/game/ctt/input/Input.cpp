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

}

Input::~Input()
{

}

void Input::onKeyEvent(uint32 keyCode, bool pressed)
{
	for (Controllable * controllable : m_controllables)
		controllable->onKeyEvent(keyCode, pressed);
}

void Input::onMouseScroll(sint32 horizontal, sint32 vertical)
{
	for (Controllable * controllable : m_controllables)
		controllable->onMouseScroll(horizontal, vertical);
}

void Input::onMouseMove(sint32 x, sint32 y, sint32 relx, sint32 rely)
{
	for (Controllable * controllable : m_controllables)
		controllable->onMouseMove(x, y, relx, rely);
}

void Input::onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y)
{
	for (Controllable * controllable : m_controllables)
		controllable->onMouseButtonEvent(button, state, clicks, x, y);
}

void Input::addControllable(Controllable *controllable)
{
	m_controllables.pushBack(controllable);
}

void Input::removeControllable(Controllable *controllable)
{
	m_controllables.remove(controllable);
}