//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/controls/UILabel.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/WDynString.h>
#include <core/DynString.h>

#include <graphics/fonts/Font.h>

#include "UIControl.h"

enum Alignment
{
	ALIGNMENT_VERTICAL_CENTER = 1,
	ALIGNMENT_VERTICAL_TOP = 2,
	ALIGNMENT_VERTICAL_BOTTOM = 4,
	ALIGNMENT_HORIZONTAL_CENTER = 8,
	ALIGNMENT_HORIZONTAL_LEFT = 16,
	ALIGNMENT_HORIZONTAL_RIGHT = 32,
	ALIGNMENT_DEFAULT = (ALIGNMENT_VERTICAL_TOP | ALIGNMENT_HORIZONTAL_LEFT)
};

namespace UI
{
	class Label : public Control
	{
	private:
		WDynString m_text;
		Font* m_font;
		bool m_shadow;
		uint32 m_alignment;
		Vector2 m_shadowOffset;

		unsigned char m_textColorSet : 1;
		unsigned char m_shadowColorSet : 1;

		Color m_textColor;
		Color m_shadowColor;
	public:
		Label(const DynString& name, Vector2 position = Vector2(), Vector2 size = Vector2());
		virtual ~Label();

		virtual void setText(const WDynString& text);
		virtual WDynString getText();

		virtual void setShadow(bool state);
		virtual bool hasShadow();

		virtual void setAlignment(uint32 alignment);
		virtual uint32 getAlignment();

		virtual void setTextColor(const Color& color);
		virtual Color getTextColor();

		virtual void setShadowColor(const Color& color);
		virtual Color getShadowColor();

		virtual void setShadowOffset(const Vector2& offset);
		virtual Vector2 getShadowOffset();

		virtual void setSkin(Skin* skin);

		virtual void setFont(const DynString& fontName, uint32 size = 15);
		
		virtual void render(RenderContext& context);
	};
}