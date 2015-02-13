//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/UIView.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "UIControl.h"
#include "UIView.h"

namespace UI
{	
	View::View(const DynString& name, Skin *skin) : Control(name)
	{
		m_skin = skin;
	}
	
	View::~View()
	{
	}
};