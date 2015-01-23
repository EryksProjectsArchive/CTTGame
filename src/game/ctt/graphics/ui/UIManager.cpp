//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/UIManager.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "controls/UIView.h"

#include "UIManager.h"

namespace UI
{
	Manager::Manager() : m_currentView(0)
	{

	}

	Manager::~Manager()
	{
		for (View *view : m_views)
			delete view;
		m_views.clear();
		m_currentView = 0;
	}

	View* Manager::createView(const DynString& name)
	{
		View* view = new View(name);
		m_views.pushBack(view);
		return view;
	}

	View * Manager::findViewByName(const DynString& name)
	{
		for (View * view : m_views)
		{
			if (view->getName() == name)
			{
				return view;
			}
		}
		return 0;
	}

	void Manager::setCurrentView(const DynString& name)
	{
		for (View * view : m_views)		
			if (view->getName() == name)			
				m_currentView = view;
	}

	void Manager::clearView()
	{
		m_currentView = 0;
	}

	void Manager::handleInput()
	{
		if (m_currentView)
			m_currentView->handleInput();			
	}

	void Manager::render(RenderContext& context)
	{
		if (m_currentView)
			m_currentView->render(context);
	}
}