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
	: Controllable(ControllableType::Engine), m_font(0), m_material(0), m_scroll(0), m_scrollUp(false), m_scrollDown(false), m_background(0), m_inputBackground(0)
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

	for (Console::Line * line : m_lines)
	{
		delete line;
	}

	m_lines.clear();
	s_instance = 0;
}

void Console::init()
{
	m_font = new Font("fonts/tahoma.ttf", 13);
	m_material = MaterialLib::get()->findByName("console");
	if (m_material)
		m_material->acquire();

	m_background = new Geometry<SimpleVertex2d>();
	Rect rect = Renderer::get().getRect();
	float width = rect.right;
	float height = 320.f;

	SimpleVertex2d vertices[4] = {
		{ 0, 0, 0xE0000000 },
		{ width, 0, 0xE0000000 },
		{ width, height, 0xE0000000 },
		{ 0, height, 0xE0000000 }
	};

	uint16 indices[6] = {
		0, 1, 2,
		0, 2, 3
	};

	m_background->fillData(vertices, 4, indices, 2);

	m_inputBackground = new Geometry<SimpleVertex2d>();
	SimpleVertex2d inputVertices[4] = {
		{ 0, height, 0xF0000000 },
		{ width, height, 0xF0000000 },
		{ width, height + 30.0f, 0xF0000000 },
		{ 0, height + 30.0f, 0xF0000000 }
	};

	m_inputBackground->fillData(inputVertices, 4, indices, 2);
}

void Console::output(MessageType::Type type, const WDynString& message)
{
	m_lines.pushBack(new Console::Line(type, message));
	if (m_lines.size() > 30) // Limit console to 30 messages
		m_lines.remove(*m_lines.begin());	
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

			m_scrollUp = false;
			m_scrollDown = false;
			m_scroll = 0;
			m_inputBuffer.reset();
		}

		if (key == Key::SCANCODE_PAGEUP && m_state)
		{
			m_scrollUp = pressed;
			m_scrollDown = false;
		}

		if (key == Key::SCANCODE_PAGEDOWN && m_state)
		{
			m_scrollDown = pressed;
			m_scrollUp = false;
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
		float height = 320.0f;
	
		renderer->setMaterial(m_material);

		renderer->renderGeometry(m_background);
		renderer->renderGeometry(m_inputBackground);

		renderer->setMaterial(0);

		m_font->render(L"#00A0D4BIM3D #FF00001.0", Rect(width-80, height-30.0f, 0, 0), Color(1, 1, 1, 1), 0);

		m_font->render(m_inputBuffer, Rect(5, height, 0, 0), Color(1, 1, 1, 1), 0);


		glScissor(0, int32(rect.bottom-height+5), int32(width), int32(height-10.0f));
		glEnable(GL_SCISSOR_TEST);
	
		int linesToHide = m_lines.size() - 15;
		if (linesToHide < 0)
			linesToHide = 0;

		if (m_scrollUp)
		{
			if (m_lines.size() > 15)
			{
				m_scroll += 1.3f;
				if (m_scroll > (m_lines.size() - 15) * 20.0f)
				{
					m_scroll = (m_lines.size() - 15) * 20.0f;
				}
			}		
		}
		else if (m_scrollDown)
		{
			m_scroll -= 1.3f;
			if (m_scroll < 0)
				m_scroll = 0;
		}
		
		float y = 5.0f - (linesToHide * 20.0f) + m_scroll;
		for (Console::Line *line : m_lines)
		{
			m_font->render(line->m_message, Rect(10, y, 0, 0), Color(1, 1, 1, 1), 0);
			y += 20.0f;
		}

		glDisable(GL_SCISSOR_TEST);
	}
}

Console::Line::Line()
{

}

Console::Line::Line(MessageType::Type type, const WDynString& message)
{
	WString<32> string = L"#00a0d4[Info] ";
	if (type == MessageType::Error)
		string = L"#FF0000[Error] ";
	else if (type == MessageType::Warning)
		string = L"#FFBF13[Warning] ";

	m_message = WString<600>(L"%s#FFFFFF%s", string.get(), message.get());
}

Console::Line::Line(const Line& rhs)
	: m_message(rhs.m_message)
{

}

Console::Line::~Line()
{

}

Console * Console::get()
{
	return s_instance;
}