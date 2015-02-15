//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/renderer/tasks/UILabelRenderTask.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <Prerequisites.h>

#include <core/WDynString.h>

#include <math/Rect.h>
#include <graphics/renderer/tasks/UIRenderTask.h>

namespace UI
{
	class LabelRenderTask : public UIRenderTask
	{
	protected:
		Font *m_font;
		WDynString m_text;
		Rect m_rect;
		bool m_shadow;
		uint32 m_alignment;
		Color m_textColor;
		Color m_shadowColor;
		Vector2 m_shadowOffset;
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

		virtual void setShadowOffset(const Vector2& offset)
		{
			m_shadowOffset = offset;
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

			if (alignment & ALIGNMENT_HORIZONTAL_CENTER)
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
						Rect r(m_rect.left + m_shadowOffset.x, m_rect.top + m_shadowOffset.y, m_rect.right + m_shadowOffset.x, m_rect.bottom + m_shadowOffset.y);
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
};