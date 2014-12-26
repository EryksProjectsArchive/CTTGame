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
#define CONSOLE_HISTORY 10

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

	class ICommand
	{
	protected:
		WDynString m_name;
		Console *m_console;
	public:
		ICommand() : m_console(0) {}
		ICommand(const WDynString& name);
		ICommand(const ICommand& command);
		virtual ~ICommand();

		virtual void onExecute(const WDynString& params) {};

		friend class Console;
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

	struct
	{
		struct
		{
			uint8 m_used;
			WDynString m_value;
		} m_entry[CONSOLE_HISTORY];

		void reset()
		{
			for (uint32 i = 0; i < CONSOLE_HISTORY; ++i)
			{
				m_entry[i].m_used = 0;
				m_entry[i].m_value.reset();
			}
			m_current = -1;
		}

		void add(const WDynString& value)
		{
			for (uint32 i = CONSOLE_HISTORY-1; i >= 1; --i)
			{
				m_entry[i].m_used = m_entry[i - 1].m_used;
				m_entry[i].m_value = m_entry[i - 1].m_value;
			}

			m_entry[0].m_used = 1;
			m_entry[0].m_value = value;

			m_current = -1;
		}

		int32 m_current;
	} m_history;

	List<ICommand *> m_commands;
public:
	Console();
	~Console();

	void init();

	void addCommand(ICommand* command);
	void removeCommand(const WDynString& name);

	void output(MessageType::Type type, const WDynString& message);

	void onKeyEvent(Key::Type key, bool pressed) override;
	void onTextInput(const WDynString& string) override;

	void render(Renderer *renderer);

	static Console* get();
};