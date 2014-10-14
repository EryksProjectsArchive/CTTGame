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

#include "Controllable.h"

class Input : public Singleton<Input>
{
private:
	List<Controllable *> m_controllables;
public:
	Input();
	~Input();

	void onKeyEvent(uint32 keyCode, bool pressed);
	void onMouseScroll(sint32 horizontal, sint32 vertical);
	void onMouseMove(sint32 x, sint32 y, sint32 relx, sint32 rely);
	void onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y);

private:
	void addControllable(Controllable *controllable);
	void removeControllable(Controllable *controllable);

	friend class Controllable;
};