//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/UIManager.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////
#pragma once

#include <Prerequisites.h>
#include <core/List.h>

namespace UI
{
	class View;

	class Manager
	{
	private:
		List<View *> m_views;

		View *m_currentView;
	public:
		Manager();
		~Manager();

		/**
		 * @Method: createView
		 * @Return: View*
		 * @Param: name of view
		 *
		 * NOTE: View object is automatically removed while we are removing manager. It's not possible to remove view by name.
		 */
		View* createView(const DynString& name);

		View* findViewByName(const DynString& name);

		void setCurrentView(const DynString& name);
		void clearView();

		void render(UIRenderContext& context);
	};
};