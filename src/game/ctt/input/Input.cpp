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

#include <SDL.h>
#include <json/json.h>

#include <Debugging.h>

#include <io/fs/FileSystem.h>

#include "Input.h"
#include "Controllable.h"

#define TO_UNICODE(s) L##s
#define DEFINE_KEY_ITEM(s)\
	{ INPUT_DEVICE_KEYBOARD, Key::SCANCODE_##s, TO_UNICODE(#s) }

InputItem g_inputItems[INPUT_ITEMS_COUNT] = {
	DEFINE_KEY_ITEM(A),
	DEFINE_KEY_ITEM(B),
	DEFINE_KEY_ITEM(C),
	DEFINE_KEY_ITEM(D),
	DEFINE_KEY_ITEM(E),
	DEFINE_KEY_ITEM(F),
	DEFINE_KEY_ITEM(G),
	DEFINE_KEY_ITEM(H),
	DEFINE_KEY_ITEM(I),
	DEFINE_KEY_ITEM(J),
	DEFINE_KEY_ITEM(K),
	DEFINE_KEY_ITEM(L),
	DEFINE_KEY_ITEM(M),
	DEFINE_KEY_ITEM(N),
	DEFINE_KEY_ITEM(O),
	DEFINE_KEY_ITEM(P),
	DEFINE_KEY_ITEM(Q),
	DEFINE_KEY_ITEM(R),
	DEFINE_KEY_ITEM(S),
	DEFINE_KEY_ITEM(T),
	DEFINE_KEY_ITEM(U),
	DEFINE_KEY_ITEM(V),
	DEFINE_KEY_ITEM(W),
	DEFINE_KEY_ITEM(X),
	DEFINE_KEY_ITEM(Y),
	DEFINE_KEY_ITEM(Z),
	DEFINE_KEY_ITEM(1),
	DEFINE_KEY_ITEM(2),
	DEFINE_KEY_ITEM(3),
	DEFINE_KEY_ITEM(4),
	DEFINE_KEY_ITEM(5),
	DEFINE_KEY_ITEM(6),
	DEFINE_KEY_ITEM(7),
	DEFINE_KEY_ITEM(8),
	DEFINE_KEY_ITEM(9),
	DEFINE_KEY_ITEM(0),
	DEFINE_KEY_ITEM(RETURN),
	DEFINE_KEY_ITEM(ESCAPE),
	DEFINE_KEY_ITEM(BACKSPACE),
	DEFINE_KEY_ITEM(TAB),
	DEFINE_KEY_ITEM(SPACE),
	DEFINE_KEY_ITEM(MINUS),
	DEFINE_KEY_ITEM(EQUALS),
	DEFINE_KEY_ITEM(LEFTBRACKET),
	DEFINE_KEY_ITEM(RIGHTBRACKET),
	DEFINE_KEY_ITEM(BACKSLASH),
	DEFINE_KEY_ITEM(NONUSHASH),
	DEFINE_KEY_ITEM(SEMICOLON),
	DEFINE_KEY_ITEM(APOSTROPHE),
	DEFINE_KEY_ITEM(GRAVE),
	DEFINE_KEY_ITEM(COMMA),
	DEFINE_KEY_ITEM(PERIOD),
	DEFINE_KEY_ITEM(SLASH),
	DEFINE_KEY_ITEM(CAPSLOCK),
	DEFINE_KEY_ITEM(F1),
	DEFINE_KEY_ITEM(F2),
	DEFINE_KEY_ITEM(F3),
	DEFINE_KEY_ITEM(F4),
	DEFINE_KEY_ITEM(F5),
	DEFINE_KEY_ITEM(F6),
	DEFINE_KEY_ITEM(F7),
	DEFINE_KEY_ITEM(F8),
	DEFINE_KEY_ITEM(F9),
	DEFINE_KEY_ITEM(F10),
	DEFINE_KEY_ITEM(F11),
	DEFINE_KEY_ITEM(F12),
	DEFINE_KEY_ITEM(PRINTSCREEN),
	DEFINE_KEY_ITEM(SCROLLLOCK),
	DEFINE_KEY_ITEM(PAUSE),
	DEFINE_KEY_ITEM(INSERT),
	DEFINE_KEY_ITEM(HOME),
	DEFINE_KEY_ITEM(PAGEUP),
	DEFINE_KEY_ITEM(DELETE),
	DEFINE_KEY_ITEM(END),
	DEFINE_KEY_ITEM(PAGEDOWN),
	DEFINE_KEY_ITEM(RIGHT),
	DEFINE_KEY_ITEM(LEFT),
	DEFINE_KEY_ITEM(DOWN),
	DEFINE_KEY_ITEM(UP),
	DEFINE_KEY_ITEM(NUMLOCKCLEAR),
	DEFINE_KEY_ITEM(KP_DIVIDE),
	DEFINE_KEY_ITEM(KP_MULTIPLY),
	DEFINE_KEY_ITEM(KP_MINUS),
	DEFINE_KEY_ITEM(KP_PLUS),
	DEFINE_KEY_ITEM(KP_ENTER),
	DEFINE_KEY_ITEM(KP_1),
	DEFINE_KEY_ITEM(KP_2),
	DEFINE_KEY_ITEM(KP_3),
	DEFINE_KEY_ITEM(KP_4),
	DEFINE_KEY_ITEM(KP_5),
	DEFINE_KEY_ITEM(KP_6),
	DEFINE_KEY_ITEM(KP_7),
	DEFINE_KEY_ITEM(KP_8),
	DEFINE_KEY_ITEM(KP_9),
	DEFINE_KEY_ITEM(KP_0),
	DEFINE_KEY_ITEM(KP_PERIOD),
	DEFINE_KEY_ITEM(NONUSBACKSLASH),
	DEFINE_KEY_ITEM(APPLICATION),
	DEFINE_KEY_ITEM(POWER),
	DEFINE_KEY_ITEM(KP_EQUALS),
	DEFINE_KEY_ITEM(F13),
	DEFINE_KEY_ITEM(F14),
	DEFINE_KEY_ITEM(F15),
	DEFINE_KEY_ITEM(F16),
	DEFINE_KEY_ITEM(F17),
	DEFINE_KEY_ITEM(F18),
	DEFINE_KEY_ITEM(F19),
	DEFINE_KEY_ITEM(F20),
	DEFINE_KEY_ITEM(F21),
	DEFINE_KEY_ITEM(F22),
	DEFINE_KEY_ITEM(F23),
	DEFINE_KEY_ITEM(F24),
	DEFINE_KEY_ITEM(EXECUTE),
	DEFINE_KEY_ITEM(HELP),
	DEFINE_KEY_ITEM(MENU),
	DEFINE_KEY_ITEM(SELECT),
	DEFINE_KEY_ITEM(STOP),
	DEFINE_KEY_ITEM(AGAIN),
	DEFINE_KEY_ITEM(UNDO),
	DEFINE_KEY_ITEM(CUT),
	DEFINE_KEY_ITEM(COPY),
	DEFINE_KEY_ITEM(PASTE),
	DEFINE_KEY_ITEM(FIND),
	DEFINE_KEY_ITEM(MUTE),
	DEFINE_KEY_ITEM(VOLUMEUP),
	DEFINE_KEY_ITEM(VOLUMEDOWN),
	DEFINE_KEY_ITEM(KP_COMMA),
	DEFINE_KEY_ITEM(KP_EQUALSAS400),
	DEFINE_KEY_ITEM(INTERNATIONAL1),
	DEFINE_KEY_ITEM(INTERNATIONAL2),
	DEFINE_KEY_ITEM(INTERNATIONAL3),
	DEFINE_KEY_ITEM(INTERNATIONAL4),
	DEFINE_KEY_ITEM(INTERNATIONAL5),
	DEFINE_KEY_ITEM(INTERNATIONAL6),
	DEFINE_KEY_ITEM(INTERNATIONAL7),
	DEFINE_KEY_ITEM(INTERNATIONAL8),
	DEFINE_KEY_ITEM(INTERNATIONAL9),
	DEFINE_KEY_ITEM(LANG1),
	DEFINE_KEY_ITEM(LANG2),
	DEFINE_KEY_ITEM(LANG3),
	DEFINE_KEY_ITEM(LANG4),
	DEFINE_KEY_ITEM(LANG5),
	DEFINE_KEY_ITEM(LANG6),
	DEFINE_KEY_ITEM(LANG7),
	DEFINE_KEY_ITEM(LANG8),
	DEFINE_KEY_ITEM(LANG9),
	DEFINE_KEY_ITEM(ALTERASE),
	DEFINE_KEY_ITEM(SYSREQ),
	DEFINE_KEY_ITEM(CANCEL),
	DEFINE_KEY_ITEM(CLEAR),
	DEFINE_KEY_ITEM(PRIOR),
	DEFINE_KEY_ITEM(RETURN2),
	DEFINE_KEY_ITEM(SEPARATOR),
	DEFINE_KEY_ITEM(OUT),
	DEFINE_KEY_ITEM(OPER),
	DEFINE_KEY_ITEM(CLEARAGAIN),
	DEFINE_KEY_ITEM(CRSEL),
	DEFINE_KEY_ITEM(EXSEL),
	DEFINE_KEY_ITEM(KP_00),
	DEFINE_KEY_ITEM(KP_000),
	DEFINE_KEY_ITEM(THOUSANDSSEPARATOR),
	DEFINE_KEY_ITEM(DECIMALSEPARATOR),
	DEFINE_KEY_ITEM(CURRENCYUNIT),
	DEFINE_KEY_ITEM(CURRENCYSUBUNIT),
	DEFINE_KEY_ITEM(KP_LEFTPAREN),
	DEFINE_KEY_ITEM(KP_RIGHTPAREN),
	DEFINE_KEY_ITEM(KP_LEFTBRACE),
	DEFINE_KEY_ITEM(KP_RIGHTBRACE),
	DEFINE_KEY_ITEM(KP_TAB),
	DEFINE_KEY_ITEM(KP_BACKSPACE),
	DEFINE_KEY_ITEM(KP_A),
	DEFINE_KEY_ITEM(KP_B),
	DEFINE_KEY_ITEM(KP_C),
	DEFINE_KEY_ITEM(KP_D),
	DEFINE_KEY_ITEM(KP_E),
	DEFINE_KEY_ITEM(KP_F),
	DEFINE_KEY_ITEM(KP_XOR),
	DEFINE_KEY_ITEM(KP_POWER),
	DEFINE_KEY_ITEM(KP_PERCENT),
	DEFINE_KEY_ITEM(KP_LESS),
	DEFINE_KEY_ITEM(KP_GREATER),
	DEFINE_KEY_ITEM(KP_AMPERSAND),
	DEFINE_KEY_ITEM(KP_DBLAMPERSAND),
	DEFINE_KEY_ITEM(KP_VERTICALBAR),
	DEFINE_KEY_ITEM(KP_DBLVERTICALBAR),
	DEFINE_KEY_ITEM(KP_COLON),
	DEFINE_KEY_ITEM(KP_HASH),
	DEFINE_KEY_ITEM(KP_SPACE),
	DEFINE_KEY_ITEM(KP_AT),
	DEFINE_KEY_ITEM(KP_EXCLAM),
	DEFINE_KEY_ITEM(KP_MEMSTORE),
	DEFINE_KEY_ITEM(KP_MEMRECALL),
	DEFINE_KEY_ITEM(KP_MEMCLEAR),
	DEFINE_KEY_ITEM(KP_MEMADD),
	DEFINE_KEY_ITEM(KP_MEMSUBTRACT),
	DEFINE_KEY_ITEM(KP_MEMMULTIPLY),
	DEFINE_KEY_ITEM(KP_MEMDIVIDE),
	DEFINE_KEY_ITEM(KP_PLUSMINUS),
	DEFINE_KEY_ITEM(KP_CLEAR),
	DEFINE_KEY_ITEM(KP_CLEARENTRY),
	DEFINE_KEY_ITEM(KP_BINARY),
	DEFINE_KEY_ITEM(KP_OCTAL),
	DEFINE_KEY_ITEM(KP_DECIMAL),
	DEFINE_KEY_ITEM(KP_HEXADECIMAL),
	DEFINE_KEY_ITEM(LCTRL),
	DEFINE_KEY_ITEM(LSHIFT),
	DEFINE_KEY_ITEM(LALT),
	DEFINE_KEY_ITEM(LGUI),
	DEFINE_KEY_ITEM(RCTRL),
	DEFINE_KEY_ITEM(RSHIFT),
	DEFINE_KEY_ITEM(RALT),
	DEFINE_KEY_ITEM(RGUI),
	DEFINE_KEY_ITEM(MODE),
	DEFINE_KEY_ITEM(AUDIONEXT),
	DEFINE_KEY_ITEM(AUDIOPREV),
	DEFINE_KEY_ITEM(AUDIOSTOP),
	DEFINE_KEY_ITEM(AUDIOPLAY),
	DEFINE_KEY_ITEM(AUDIOMUTE),
	DEFINE_KEY_ITEM(MEDIASELECT),
	DEFINE_KEY_ITEM(WWW),
	DEFINE_KEY_ITEM(MAIL),
	DEFINE_KEY_ITEM(CALCULATOR),
	DEFINE_KEY_ITEM(COMPUTER),
	DEFINE_KEY_ITEM(AC_SEARCH),
	DEFINE_KEY_ITEM(AC_HOME),
	DEFINE_KEY_ITEM(AC_BACK),
	DEFINE_KEY_ITEM(AC_FORWARD),
	DEFINE_KEY_ITEM(AC_STOP),
	DEFINE_KEY_ITEM(AC_REFRESH),
	DEFINE_KEY_ITEM(AC_BOOKMARKS),
	DEFINE_KEY_ITEM(BRIGHTNESSDOWN),
	DEFINE_KEY_ITEM(BRIGHTNESSUP),
	DEFINE_KEY_ITEM(DISPLAYSWITCH),
	DEFINE_KEY_ITEM(KBDILLUMTOGGLE),
	DEFINE_KEY_ITEM(KBDILLUMDOWN),
	DEFINE_KEY_ITEM(KBDILLUMUP),
	DEFINE_KEY_ITEM(EJECT),
	DEFINE_KEY_ITEM(SLEEP),
	DEFINE_KEY_ITEM(APP1),
	DEFINE_KEY_ITEM(APP2)
};

Input::Input()
{
	m_inputState = 0;
	memset(m_keyState, 0, Key::NUM_SCANCODES);
	m_mouse.x = 0;
	m_mouse.y = 0;
	m_cursor = 0;
	m_cursorVisiblity = true;
}

Input::~Input()
{
	m_binds.clear();
}

InputItem Input::getInputItem(const WDynString& value)
{
	for (uint32 i = 0; i < INPUT_ITEMS_COUNT; ++i)
	{
		if (g_inputItems[i].key == value)
		{
			return g_inputItems[i];
		}
	}
	return InputItem();
}

void Input::_processBinds(Key::Type key, bool pressed)
{
	for (BindData data : m_binds)
	{
		if (((Key::Type)data.inputItem.numeric) == key && data.pressed == pressed)
		{
			if (!Console::get()->execute(data.value))
			{
				Error("Input", "Unable to execute bind '%s'", data.value.get());
			}
			break;
		}
	}
}

void Input::deserializeBinds(File *file)
{
	BIM_ASSERT(file, "Null file pointer.");

	if (file->isLoaded())
	{
		DynString data = file->getContent();
		if (data.getLength() > 0)
		{
			Json::Reader reader;
			Json::Value root;
			if (reader.parse(data.get(), root))
			{
				for (std::string names : root.getMemberNames())
				{
					Json::Value _bind = root[names.c_str()];
					if (_bind.isString())
					{
						std::string str = _bind.asString();
						bool pressed = (str[0] == '+');
						
						Info("Input", "New bind loaded. %s, %s, %s", str.substr(1, str.length()).c_str(), pressed ? "press" : "release", names.c_str());
						bind(StringUtilities::toWideChar(str.substr(1, str.length()).c_str()), pressed, StringUtilities::toWideChar(names.c_str()));
					}
				}
			}
			else
			{
				Error("Input", "Cannot deserialize configuration file. %s", reader.getFormatedErrorMessages().c_str());
			}
		}
	}
}

void Input::serializeBinds(File *file)
{
	BIM_ASSERT(file, "Null file pointer.");

	Json::StyledWriter writer;
	Json::Value root;

	for (BindData bind : m_binds)
	{
		WDynString combination;
		if (bind.pressed)
		{
			combination.append(L"+");
		}
		else 
		{
			combination.append(L"-");
		}
		combination.append(bind.inputItem.key);
		root[StringUtilities::toMultiByte(bind.value).get()] = StringUtilities::toMultiByte(combination).get();
	}

	std::string data = writer.write(root);	
	file->write(data.c_str(), data.length(), sizeof(uint8));
	file->flush();
}

void Input::onKeyEvent(Key::Type key, bool pressed)
{
	m_keyState[key] = pressed;

	for (Controllable * controllable : m_controllables)
	{
		if (!isLocked() || controllable->m_type == ControllableType::Engine)
		{
			if (controllable->onKeyEvent(key, pressed)) 
			{
				return;
			}
		}
	}

	if (!isLocked())
		_processBinds(key, pressed);
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
	m_mouseBtnState[button] = state;

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

void Input::bind(const WDynString& inputItem, bool pressed, const WDynString& value)
{
	InputItem item = getInputItem(inputItem);
	if (item.isValid && item.device == INPUT_DEVICE_KEYBOARD)
	{
		// Remove duplicate actions.
		for (BindData data : m_binds)
		{
			if (data.value == value)
			{
				m_binds.remove(data);
				break;
			}
		}

		m_binds.pushBack(BindData(item, pressed, value));
	}
}

void Input::unbind(const WDynString& value)
{
	for (BindData data : m_binds)
	{
		if (data.value == value)
		{
			m_binds.remove(data);
			break;
		}
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
	{
		Warning("Input", "Input state reached bellow zero.");
		m_inputState = 0;
	}
}

bool Input::isLocked()
{
	return m_inputState > 0;
}

bool Input::isKeyDown(Key::Type key)
{
	return m_keyState[key];
}

bool Input::isMouseBtnPressed(MouseButton::Type button)
{
	return m_mouseBtnState[button];
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

bool Input::isCursorVisible()
{
	return m_cursorVisiblity;
}

void Input::showCursor(bool state)
{
	SDL_ShowCursor(state ? 1 : 0);
	m_cursorVisiblity = state;
	
	SDL_SetRelativeMouseMode(m_cursorVisiblity ? SDL_FALSE : SDL_TRUE);

	if (!m_cursorVisiblity)
	{
		for (uint32 i = 0; i < MouseButton::Count; ++i)
			m_mouseBtnState[i] = false;
	}
}

void Input::setCursor(Cursor::Type type)
{
	if (m_cursor)
	{
		SDL_FreeCursor(m_cursor);
		m_cursor = 0;
	}

	SDL_SystemCursor cursor = SDL_SYSTEM_CURSOR_ARROW;
	switch (type)
	{
	case Cursor::Hand:
		cursor = SDL_SYSTEM_CURSOR_HAND;
		break;
	}

	m_cursor = SDL_CreateSystemCursor(cursor);
	SDL_SetCursor(m_cursor);
}