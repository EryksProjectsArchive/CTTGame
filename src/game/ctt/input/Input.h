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
#include <core/console/Console.h>
#include <core/StringUtilities.h>
#include <core/WDynString.h>

#include "KeyEnum.h"
#include "Controllable.h"

enum MouseCursor
{
	MOUSE_CURSOR_ARROW,
	MOUSE_CURSOR_HAND
};

enum MouseButton
{
	MOUSE_BUTTON_LEFT = 1,
	MOUSE_BUTTON_MIDDLE = 2,
	MOUSE_BUTTON_RIGHT = 3,
	MOUSE_BUTTON_COUNT = 3
};

enum MouseWheelAxis
{
	MOUSE_WHEEL_AXIS_X = (MouseButton::MOUSE_BUTTON_COUNT + 1),
	MOUSE_WHEEL_AXIS_Y
};

enum MouseAxis
{
	MOUSE_AXIS_X = (MouseWheelAxis::MOUSE_WHEEL_AXIS_Y + 1),
	MOUSE_AXIS_Y
};

enum InputDevice
{
	INPUT_DEVICE_KEYBOARD,
	INPUT_DEVICE_MOUSE
};

struct InputItem
{	
	bool isValid;
	InputDevice device;
	uint32 numeric;
	WDynString key;

	InputItem()
	{
		this->isValid = false;
	}

	InputItem(const InputItem& right)
	{
		this->device = right.device;
		this->numeric = right.numeric;
		this->key = right.key;
		this->isValid = right.isValid;
	}

	InputItem(InputDevice device, uint32 numeric, const WDynString& key)
	{
		this->device = device;
		this->numeric = numeric;
		this->isValid = true;
		switch (device)
		{
		case INPUT_DEVICE_KEYBOARD:
			{
				this->key = WString<256>(L"keyboard.%s", StringUtilities::toLower(key).get());
			} break;
		case INPUT_DEVICE_MOUSE:
			{
				if (numeric > MOUSE_WHEEL_AXIS_Y)
				{
					this->key = WString<256>(L"mouse.axis.%s", StringUtilities::toLower(key).get());
				}
				else if (numeric > MOUSE_BUTTON_COUNT)
				{
					this->key = WString<256>(L"mouse.wheel.%s", StringUtilities::toLower(key).get());
				}
				else
				{
					this->key = WString<256>(L"mouse.button.%s", StringUtilities::toLower(key).get());
				}
			} break;
		default:
			{
				this->key = WString<256>(L"unknown.%s", StringUtilities::toLower(key).get());
			};
		}
	}	

	bool operator==(const InputItem& item)
	{
		return (device == item.device && numeric == item.numeric && isValid == item.isValid);
	}
};

#define INPUT_ITEMS_COUNT 247

class Input : public Singleton<Input>
{
private:
	struct BindData
	{
		InputItem inputItem;
		bool pressed;
		WDynString value;

		BindData()
		{
			this->pressed = false;
		}

		BindData(const BindData& data)
		{
			this->inputItem = data.inputItem;
			this->pressed = data.pressed;
			this->value = data.value;
		}

		BindData(InputItem& inputItem, bool pressed, const WDynString& value)
		{
			this->inputItem = inputItem;
			this->pressed = pressed;
			this->value = value;
		}

		bool operator ==(const BindData& data)
		{
			return value == data.value;
		}
	};
	List<Controllable *> m_controllables;

	bool m_keyState[Key::NUM_SCANCODES];
	bool m_mouseBtnState[MouseButton::MOUSE_BUTTON_COUNT];

	struct
	{
		sint32 x;
		sint32 y;
	} m_mouse;

	int32 m_inputState;

	struct SDL_Cursor *m_cursor;
	bool m_cursorVisiblity;

	List <BindData> m_binds;

	void _processBinds(Key::Type key, bool pressed);
	void _processBinds(MouseButton button, bool pressed);
	void _processBinds(MouseAxis axis, bool up);
	void _processBinds(MouseWheelAxis axis, bool up);

	InputItem getInputItem(const WDynString& value);
public:
	Input();
	~Input();

	void registerCommands();

	void onKeyEvent(Key::Type key, bool pressed);
	void onMouseScroll(sint32 horizontal, sint32 vertical);
	void onMouseMove(sint32 x, sint32 y, sint32 relx, sint32 rely);
	void onMouseButtonEvent(uint8 button, bool state, uint8 clicks, sint32 x, sint32 y);
	void onTextInput(const WDynString& string);

	bool bind(const WDynString& inputItem, const WDynString& value);
	bool unbind(const WDynString& inputItem);

	void deserializeBinds(File *file);
	void serializeBinds(File *file);

	void lock();
	void unlock();

	bool isLocked();

	bool isKeyDown(Key::Type key);
	bool isMouseBtnPressed(MouseButton button);
	sint32 getMouseX();
	sint32 getMouseY();

	bool isCursorVisible();
	void showCursor(bool state);
	void setCursor(MouseCursor type);

	class BindCommand : public Console::ICommand
	{
	private:
		Input *m_input;
	public:
		BindCommand(Input *input);

		void onExecute(const WDynString& args);
	};

	class UnbindCommand : public Console::ICommand
	{
	private:
		Input *m_input;
	public:
		UnbindCommand(Input *input);

		void onExecute(const WDynString& args);
	};
private:
	void addControllable(Controllable *controllable);
	void removeControllable(Controllable *controllable);

	friend class Controllable;
};