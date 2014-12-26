//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/console/Console.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Console.h"

#include <core/WString.h>
#include <io/Config.h>
#include <graphics/fonts/Font.h>
#include <math/Rect.h>

#include <resources/materials/MaterialLib.h>

#include <input/Input.h>
#include <core/Timer.h>

#include <os/OS.h>
#include <game/Game.h>

Console * Console::s_instance = 0;

Console::Console()
	: Controllable(ControllableType::Engine), m_font(0), m_material(0), m_background(0), m_inputBackground(0), m_height(CONSOLE_LINES * 20.0f + 10.0f), m_isInitialized(false)
{
	s_instance = this;
}

Console::~Console()
{
	if (m_material)
		m_material->release();

	if (m_font)
	{
		delete m_font;
		m_font = 0;
	}

	if (m_background)
	{
		delete m_background;
		m_background = 0;
	}

	if (m_inputBackground)
	{
		delete m_inputBackground;
		m_inputBackground = 0;
	}
	s_instance = 0;
}

void Console::init()
{
	m_font = new Font("fonts/tahoma-bold.ttf", 13);
	m_material = MaterialLib::get()->findByName("console");
	if (m_material)
		m_material->acquire();

	m_background = new Geometry<SimpleVertex2d>();
	Rect rect = Renderer::get()->getRect();
	float width = rect.right;

	SimpleVertex2d vertices[4] = {
		{ 0, 0, 0xE0000000 },
		{ width, 0, 0xE0000000 },
		{ width, m_height, 0xE0000000 },
		{ 0, m_height, 0xE0000000 }
	};

	uint16 indices[6] = {
		0, 1, 2,
		0, 2, 3
	};

	m_background->fillData(vertices, 4, indices, 2);

	m_inputBackground = new Geometry<SimpleVertex2d>();
	SimpleVertex2d inputVertices[4] = {
		{ 0, m_height, 0xF0000000 },
		{ width, m_height, 0xF0000000 },
		{ width, m_height + 30.0f, 0xF0000000 },
		{ 0, m_height + 30.0f, 0xF0000000 }
	};

	m_inputBackground->fillData(inputVertices, 4, indices, 2);
	m_isInitialized = true;
}

void Console::output(MessageType::Type type, const WDynString& message)
{
	for (uint32 i = 0; i < CONSOLE_LINES-1; ++i)
		m_lines[i] = m_lines[i + 1];

	m_lines[CONSOLE_LINES - 1].Set(type, message);
}

void Console::onKeyEvent(Key::Type key, bool pressed)
{
	if (Config::get()["engine"]["console"].getBool(false))
	{
		if (key == Key::SCANCODE_GRAVE && pressed)
		{
			m_state = !m_state;
			if (m_state)
				input()->lock();
			else
				input()->unlock();


			m_inputBuffer.reset();
		}
		
		if (key == Key::SCANCODE_RETURN && m_state && pressed)
		{
			// TODO: Commands processor and config variables management via conole
			if (m_inputBuffer.getLength() > 0)
			{
				if (m_inputBuffer == L"quit")
				{
					Game::get()->shutdown();
				}
				else
				{
					output(MessageType::Error, WString<256>(L"Cannot find command: %s", m_inputBuffer.get()));
				}
				m_inputBuffer.reset();
			}
		}

		if (key == Key::SCANCODE_BACKSPACE && pressed)
		{
			m_inputBuffer = m_inputBuffer.substr(0, m_inputBuffer.getLength() - 1);
		}
	}
}

void Console::onTextInput(const WDynString& string)
{	
	if (m_state)
	{
		if (string[0]!='`')// hardcoded hotfix for doubled keys
			m_inputBuffer += string;
	}
}

void Console::render(Renderer *renderer)
{
	if (m_state)
	{
		Rect rect = renderer->getRect();
		float width = rect.right;
		
		renderer->setMaterial(m_material);

		renderer->renderGeometry(m_background);
		renderer->renderGeometry(m_inputBackground);

		renderer->setMaterial(0);

		m_font->render(L"#00A0D4BIM3D #FF00001.0", Rect(width-80, m_height-20.0f, 0, 0), Color(1, 1, 1, 0.2), 0);

		m_font->render(m_inputBuffer, Rect(5, m_height, 0, 0), Color(1, 1, 1, 1), 0);
		
		float y = 5.0f;
		for (uint32 i = 0; i < CONSOLE_LINES; ++i)
		{
			m_font->render(m_lines[i].m_message, Rect(10, y, 0, 0), Color(1, 1, 1, 1), 0);
			y += 20.0f;
		}
	}
}

Console::Line::Line()
{

}

Console::Line::Line(const Line& rhs)
	: m_message(rhs.m_message)
{

}

Console::Line::~Line()
{

}

void Console::Line::Set(MessageType::Type type, const WDynString& message)
{
	WString<32> string = L"#00a0d4[Info] ";
	if (type == MessageType::Error)
		string = L"#FF0000[Error] ";
	else if (type == MessageType::Warning)
		string = L"#FFBF13[Warning] ";

	m_message.clear();
	m_message = WString<600>(L"%s#FFFFFF%s", string.get(), message.get());
}

Console::Line& Console::Line::operator=(const Console::Line& line)
{
	m_message = line.m_message;
	return *this;
}

Console * Console::get()
{
	return s_instance;
}