//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/console/Console.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/Singleton.h>
#include <input/Controllable.h>

#include <graphics/Material.h>

#include <core/WDynString.h>
#include <core/WString.h>
#include <core/List.h>

#include <graphics/Vertex2d.h>
#include <graphics/Geometry.h>

#define CONSOLE_LINES 10

class Console : public Controllable
{
public:
	struct MessageType
	{
		enum Type
		{
			Invalid = 0,
			Info,
			Error,
			Warning
		};
	};
private:
	class Line
	{
	private:
		WString<600> m_message;
	public:	
		Line(const Line& rhs);
		Line();
		~Line();

		void Set(MessageType::Type type, const WDynString& m_message);
		Line& operator=(const Line& line);

		friend class Console;	
	};


	bool m_isInitialized;
	Line m_lines[CONSOLE_LINES];
	bool m_state;
	Font* m_font;
	Material* m_material;
	Geometry<SimpleVertex2d>* m_background;
	Geometry<SimpleVertex2d>* m_inputBackground;
	static Console* s_instance;
	WDynString m_inputBuffer;
	float m_height;
public:
	Console();
	~Console();

	void init();

	void output(MessageType::Type type, const WDynString& message);

	void onKeyEvent(Key::Type key, bool pressed) override;
	void onTextInput(const WDynString& string) override;

	void render(Renderer *renderer);

	static Console* get();
};