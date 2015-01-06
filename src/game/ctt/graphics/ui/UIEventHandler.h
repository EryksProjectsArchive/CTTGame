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
	public:
		typedef void(EventHandler::*eventCallbackEmpty)();
		typedef void(EventHandler::*eventCallback)(UI::Control *source);
	};
};
