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
#include <graphics/ui/controls/UIControl.h>

namespace UI
{
	class View : public Control
	{
	public:
		View(const DynString& name, Skin* skin);
		~View();
	};
};