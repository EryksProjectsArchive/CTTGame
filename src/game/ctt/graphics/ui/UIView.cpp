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

#include "UIView.h"
#include "controls/UIControl.h"

namespace UI
{	
	View::View(const DynString& name) : m_name(name)
	{
	}
	
	View::~View()
	{
		for (Control * control : m_controls)
		{
			delete control;
		}
		m_controls.clear();
	}

	void View::attach(Control *control)
	{
		m_controls.pushBack(control);
	}

	void View::detach(Control *control)
	{
		m_controls.remove(control);
	}

	DynString View::getName()
	{
		return m_name;
	}

	void View::render(UIRenderContext& context)
	{
		for (Control * control : m_controls)
			control->render(context);
	}
};