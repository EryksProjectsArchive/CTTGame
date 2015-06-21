//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: input/Controllable.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include "KeyEnum.h"
#include "ControllableType.h"

class Controllable
{
private:
	ControllableType::Type m_type;
public:
	Controllable(ControllableType::Type type);
	virtual ~Controllable();

	virtual void onKeyEvent(Key::Type keyCode, bool pressed) {}
	virtual void onMouseScroll(sint32 horizontal, sint32 vertical) {}
	virtual void onMouseMove(sint32 x, sint32 y, sint32 relx, sint32 rely) {}
	virtual void onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y) {}
	virtual void onTextInput(const WDynString& string) {}

protected:
	Input * input();

	void registerInput();
	void unregisterInput();

	friend class Input;
};