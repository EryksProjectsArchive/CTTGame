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

struct Cursor
{
	enum Type
	{
		Arrow,
		Hand
	};
};

struct MouseButton
{
	enum Type
	{
		Left = 1,
		Middle = 2,
		Right = 3,
		Count = 3
	};
};

class Input : public Singleton<Input>
{
private:
	List<Controllable *> m_controllables;

	bool m_keyState[Key::NUM_SCANCODES];
	bool m_mouseBtnState[MouseButton::Type::Count];

	struct
	{
		sint32 x;
		sint32 y;
	} m_mouse;

	int32 m_inputState;

	struct SDL_Cursor *m_cursor;
	bool m_cursorVisiblity;
public:
	Input();
	~Input();

	void onKeyEvent(Key::Type key, bool pressed);
	void onMouseScroll(sint32 horizontal, sint32 vertical);
	void onMouseMove(sint32 x, sint32 y, sint32 relx, sint32 rely);
	void onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y);
	void onTextInput(const WDynString& string);

	void lock();
	void unlock();

	bool isLocked();

	bool isKeyDown(Key::Type key);
	bool isMouseBtnPressed(MouseButton::Type button);
	sint32 getMouseX();
	sint32 getMouseY();

	bool isCursorVisible();
	void showCursor(bool state);
	void setCursor(Cursor::Type type);
private:
	void addControllable(Controllable *controllable);
	void removeControllable(Controllable *controllable);

	friend class Controllable;
};