//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/controls/UIButton.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////
#pragma once

#include <Prerequisites.h>

#include <core/WDynString.h>
#include <core/DynString.h>

#include <graphics/fonts/Font.h>

#include "UIControl.h"

#include <graphics/Geometry.h>

namespace UI
{
	class Button : public Control
	{
	private:
		WDynString m_text;
		Geometry<Vertex2d>* m_geometry;
		Material *m_material;

		Font *m_font;
		bool m_pressed;
	public:
		Button(const DynString& name, Vector2 position = Vector2(), Vector2 size = Vector2());
		virtual ~Button();

		virtual void setText(const WDynString& text);
		virtual WDynString getText();

		virtual void render(UIRenderContext& context);
	};
}