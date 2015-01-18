//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/controls/UIEventHandler.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "controls/UIControl.h"

namespace UI
{
	class EventHandler
	{
	private:
		List<UI::Control *> m_callers;
	public:
		void registerCaller(UI::Control * caller)
		{
			m_callers.pushBack(caller);
		}
		
		void unregisterCaller(UI::Control * caller)
		{
			m_callers.remove(caller);
		}

		EventHandler()
		{
		}

		virtual ~EventHandler()
		{
			m_callers.clear();
		}

		typedef void(EventHandler::*eventCallbackEmpty)();
		typedef void(EventHandler::*eventCallback)(UI::Control *source);
	};
};
