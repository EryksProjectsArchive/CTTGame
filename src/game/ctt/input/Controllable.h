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

	virtual bool onKeyEvent(Key::Type keyCode, bool pressed) { return false; }
	virtual bool onMouseScroll(sint32 horizontal, sint32 vertical) { return false; }
	virtual bool onMouseMove(sint32 x, sint32 y, sint32 relx, sint32 rely) { return false;  }
	virtual bool onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y) { return false;  }
	virtual bool onTextInput(const WDynString& string) { return false; }

protected:
	Input * input();

	void registerInput();
	void unregisterInput();

	friend class Input;
};