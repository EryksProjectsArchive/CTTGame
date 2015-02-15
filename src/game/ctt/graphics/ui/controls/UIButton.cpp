//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/controls/UIButton.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "../UISkin.h"
#include "UIButton.h"

#include <math/Rect.h>
#include <graphics/renderer/RenderContext.h>
#include "../renderer/tasks/UILabelRenderTask.h"

#include <resources/materials/MaterialLib.h>

#include <input/Input.h>

namespace UI
{
	class ButtonRenderTask : public LabelRenderTask
	{
	public:
		ButtonRenderTask()
		{
		}

		virtual void performRender(Renderer * renderer)
		{
			if (m_skin)
			{
				UIRenderTask::performRender(renderer);				
				LabelRenderTask::performRender(renderer);
			}
			else
			{
				Warning("UIButtonRenderTask", "Unable to preform render task. No skin set.");
			}
		}
	};

	Button::Button(const DynString& name, Vector2 position, Vector2 size)
		: Label(name, position, size)
	{
		setAlignment(ALIGNMENT_HORIZONTAL_CENTER | ALIGNMENT_VERTICAL_CENTER);
		setText(L"button");
		setShadow(true);
	}

	Button::~Button()
	{
		m_onPressData.clear();
	}

	void Button::render(RenderContext& context)
	{			
		Control::render(context);

		if (!m_skin)
			return;

		ButtonRenderTask * task = context.newTask<ButtonRenderTask>();

		Rect rct(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
		Geometry<Vertex2d> *geometry = m_skin->generateButtonGeometry(rct, m_hover);
		task->setAlignment(m_alignment);
		task->setGeometry(geometry);
		task->setSkin(m_skin);
		task->setRect(rct);
		task->setShadow(m_shadow);
		task->setLabel(m_font, m_text);

		if (m_shadowColorSet)
		{
			task->setShadowColor(m_shadowColor);
		}
		
		if (m_textColorSet)
		{
			task->setTextColor(m_textColor);
		}
		else 
		{
			Skin::Colors colors = m_skin->colors();
			task->setTextColor(m_hover ? colors.buttonHover : colors.buttonNormal);
		}
	}

	bool Button::handleInput()
	{
		if (Input::get()->isLocked())
			return false;

		if (Control::handleInput())
			return true;

		if (!Input::get()->isCursorVisible())
			return false;

		Rect rct(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);

		sint32 x = Input::get()->getMouseX();
		sint32 y = Input::get()->getMouseY();

		bool hover = (x >= rct.left && x <= rct.right) && (y >= rct.top && y <= rct.bottom);
		if (m_hover != hover)
		{
			Input::get()->setCursor(hover ? MOUSE_CURSOR_HAND : MOUSE_CURSOR_ARROW);
			m_hover = hover;
			if (!m_hover)
				m_pressed = false;

			return true;
		}

		bool leftButtonState = Input::get()->isMouseBtnPressed(MOUSE_BUTTON_LEFT);	
		if (m_hover && !m_pressed && leftButtonState)
		{
			for (OnPressData& data : m_onPressData)
			{
				data.call(this);				
			}

			m_pressed = true;
			return true;
		}

		if (m_pressed && !leftButtonState)
			m_pressed = false;

		return false;
	}

	void Button::onPressInternal(EventHandler * handler, EventHandler::eventCallback fn)
	{
		OnPressData data;
		data.handler = handler;
		data.callback = fn;
		m_onPressData.pushBack(data);
		handler->registerCaller(this);
	}

	void Button::onPressInternal(EventHandler * handler, EventHandler::eventCallbackEmpty fn)
	{
		OnPressData data;
		data.handler = handler;
		data.callbackEmpty = fn;
		m_onPressData.pushBack(data);
		handler->registerCaller(this);
	}
};