//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: input/Input.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/Singleton.h>
#include <core/List.h>

#include "KeyEnum.h"
#include "Controllable.h"

class Input : public Singleton<Input>
{
private:
	List<Controllable *> m_controllables;

	bool m_keyState[Key::NUM_SCANCODES];

	struct
	{
		sint32 x;
		sint32 y;
	} m_mouse;
public:
	Input();
	~Input();

	void onKeyEvent(Key::Type key, bool pressed);
	void onMouseScroll(sint32 horizontal, sint32 vertical);
	void onMouseMove(sint32 x, sint32 y, sint32 relx, sint32 rely);
	void onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y);

	bool isKeyDown(Key::Type key);
	sint32 getMouseX();
	sint32 getMouseY();
private:
	void addControllable(Controllable *controllable);
	void removeControllable(Controllable *controllable);

	friend class Controllable;
};