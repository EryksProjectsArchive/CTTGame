//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/UIView.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <core/DynString.h>
#include <core/List.h>

namespace UI
{
	class View
	{
	private:
		DynString m_name;

		List<Control *> m_controls;
	public:
		View(const DynString& name);
		~View();

		void attach(Control *control);
		void detach(Control *control);

		DynString getName();

		void render(UIRenderContext& context);
	};
};