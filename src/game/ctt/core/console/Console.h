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
		Line(MessageType::Type type, const WDynString& m_message);
		Line(const Line& rhs);
		Line();
		~Line();

		friend class Console;
	
	};

	List<Line*> m_lines;
	unsigned char m_state : 1;
	Font* m_font;
	Material* m_material;
	float m_scroll;
	bool m_scrollDown;
	bool m_scrollUp;
	Geometry<SimpleVertex2d>* m_background;
	Geometry<SimpleVertex2d>* m_inputBackground;
	static Console* s_instance;
	WDynString m_inputBuffer;
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