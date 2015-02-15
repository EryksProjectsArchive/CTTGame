//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/controls/UILabel.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "../UISkin.h"
#include "UILabel.h"

#include <graphics/renderer/RenderContext.h>
#include "../renderer/tasks/UILabelRenderTask.h"

#include <resources/materials/MaterialLib.h>

#include <input/Input.h>

namespace UI
{	
	Label::Label(const DynString& name, Vector2 position, Vector2 size)
		: Control(name, position, size), m_text(L"Label"), m_font(0), m_shadow(true), m_alignment(ALIGNMENT_DEFAULT),
		m_textColorSet(0), m_shadowColorSet(0), m_shadowOffset(Vector2(1,1))
	{
		m_font = new Font("fonts/Tahoma.ttf", 15);
	}

	Label::~Label()
	{
		if (m_font)
		{
			delete m_font;
			m_font = 0;
		}
	}

	void Label::setText(const WDynString& text)
	{
		m_text = text;
	}

	WDynString Label::getText()
	{
		return m_text;
	}

	void Label::render(RenderContext& context)
	{
		Control::render(context);

		if (!m_skin)
			return;

		LabelRenderTask * task = context.newTask<LabelRenderTask>();

		Rect rct(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
		task->setSkin(m_skin);
		task->setRect(rct);
		task->setLabel(m_font, m_text);
		task->setShadow(m_shadow);
		task->setAlignment(m_alignment);

		if (m_textColorSet)
			task->setTextColor(m_textColor);

		if (m_shadowColorSet)
			task->setShadowColor(m_shadowColor);
		
		task->setShadowOffset(m_shadowOffset);
	}

	void Label::setShadow(bool state)
	{
		m_shadow = state;
	}

	bool Label::hasShadow()
	{
		return m_shadow;
	}

	void Label::setAlignment(uint32 alignment)
	{
		m_alignment = alignment;
	}

	uint32 Label::getAlignment()
	{
		return m_alignment;
	}

	void Label::setFont(const DynString& fontName, uint32 size)
	{
		if (m_font)
		{
			delete m_font;
			m_font = 0;
		}
		m_font = new Font(FilePath("fonts/%s.ttf", fontName.get()), size);
	}

	void Label::setShadowColor(const Color& color)
	{
		m_shadowColorSet = 1;
		m_shadowColor = color;
	}

	Color Label::getShadowColor()
	{
		return m_shadowColorSet ? m_shadowColor : m_skin->colors().labelShadow;
	}

	void Label::setShadowOffset(const Vector2& offset)
	{
		m_shadowOffset = offset;
	}

	Vector2 Label::getShadowOffset()
	{
		return m_shadowOffset;
	}

	void Label::setTextColor(const Color& color)
	{
		m_textColorSet = 1;
		m_textColor = color;
	}

	Color Label::getTextColor()
	{
		return m_textColorSet ? m_textColor : m_skin->colors().labelNormal;
	}

	void Label::setSkin(Skin* skin)
	{
		Control::setSkin(skin);

		Skin::Data data = m_skin->data();

		m_shadowOffset = data.label.shadowOffset;
		m_shadow = data.label.shadow;
	}
};