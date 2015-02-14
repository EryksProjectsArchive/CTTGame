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

#include <math/Rect.h>
#include <graphics/renderer/RenderContext.h>
#include <graphics/renderer/tasks/UIRenderTask.h>

#include <resources/materials/MaterialLib.h>

#include <input/Input.h>

namespace UI
{
	class LabelRenderTask : public UIRenderTask
	{
	private:
		Font *m_font;
		WDynString m_text;
		Rect m_rect;
		bool m_shadow;
		uint32 m_alignment;
		Color m_textColor;
		Color m_shadowColor;
	public:
		LabelRenderTask()
		{
			m_font = 0;
			m_shadow = false;
		}

		virtual void setRect(const Rect& rect)
		{
			m_rect = rect;
		}

		virtual void setLabel(Font *font, const WDynString& text)
		{
			m_font = font;
			m_text = text;
		}

		virtual void setShadow(bool shadow)
		{
			m_shadow = shadow;
		}

		virtual void setSkin(Skin * skin)
		{
			UIRenderTask::setSkin(skin);

			Skin::Colors colors = m_skin->colors();

			m_textColor = colors.labelNormal;
			m_shadowColor = colors.labelShadow;
		}

		virtual void setAlignment(uint32 alignment)
		{
			if (alignment & ALIGNMENT_VERTICAL_CENTER)
			{
				m_alignment |= Font::DrawFlags::VerticalCenter;
			}

			if (m_alignment & ALIGNMENT_HORIZONTAL_CENTER)
			{
				m_alignment |= Font::DrawFlags::HorizontalCenter;
			}
			// TODO: Support for more alignments
		}

		virtual void setTextColor(const Color& textColor)
		{
			m_textColor = textColor;
		}

		virtual void setShadowColor(const Color& shadowColor)
		{
			m_shadowColor = shadowColor;
		}

		virtual void performRender(Renderer * renderer)
		{
			if (m_skin)
			{
				renderer->setScissor(true, m_rect);
				if (m_font)
				{
					if (m_shadow)
					{
						Rect r(m_rect.left+2,m_rect.top+2,m_rect.right+2,m_rect.bottom+2);
						m_font->render(m_text, r, m_shadowColor, m_alignment);
					}

					m_font->render(m_text, m_rect, m_textColor, m_alignment);
				}
				renderer->setScissor(false);
			}
			else
			{
				Warning("UILabelRenderTask", "Unable to preform render task. No skin set.");
			}
		}
	};

	Label::Label(const DynString& name, Vector2 position, Vector2 size)
		: Control(name, position, size), m_text(L"Label"), m_font(0), m_shadow(true), m_alignment(ALIGNMENT_DEFAULT),
		  m_textColorSet(0), m_shadowColorSet(0)
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

	void Label::setTextColor(const Color& color)
	{
		m_textColorSet = 1;
		m_textColor = color;
	}

	Color Label::getTextColor()
	{
		return m_textColorSet ? m_textColor : m_skin->colors().labelNormal;
	}
};