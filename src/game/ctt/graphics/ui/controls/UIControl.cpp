//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/control/UIControl.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "UIControl.h"

namespace UI
{
	Control::Control(const DynString& name, Vector2 position, Vector2 size)
		: m_name(name), m_parent(0), m_position(position), m_size(size)
	{

	}

	Control::~Control()
	{
		for (Control *control : m_children)		
			control->m_parent = 0;

		if (m_parent)
			m_parent->m_children.remove(this);
	}

	DynString Control::getName()
	{
		return m_name;
	}

	Control * Control::getParent()
	{
		return m_parent;
	}

	void Control::setParent(Control *control)
	{
		if (m_parent)
			m_parent->m_children.remove(control);

		m_parent = control;
		m_parent->m_children.pushBack(control);
	}

	void Control::addChild(Control *control)
	{
		if (control->m_parent)
			control->m_parent->m_children.remove(control);

		control->m_parent = this;
		m_children.pushBack(control);
	}

	void Control::removeChild(Control *control)
	{
		control->m_parent = 0;
		m_children.remove(control);
	}

	bool Control::isChildOf(Control *control)
	{
		for (Control *child : control->m_children)
		{
			if (child == this)
				return true;
		}
		return false;
	}

	bool Control::isParentOf(Control *control)
	{
		return control->m_parent == this;
	}

	void Control::render(UIRenderContext& context)
	{
		for (Control *child : m_children)
			child->render(context);

		//Info("control", "render %s", m_name.get());
	}
};