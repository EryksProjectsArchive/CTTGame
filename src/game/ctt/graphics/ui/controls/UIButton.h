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
#include "../UIEventHandler.h"

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

		struct OnPressData
		{
			EventHandler * handler;
			EventHandler::eventCallback callback;
			EventHandler::eventCallbackEmpty callbackEmpty;

			OnPressData()
			{
				handler = 0;
				callback = 0;
				callbackEmpty = 0;
			}

			OnPressData(const OnPressData& data)
			{
				handler = data.handler;
				callback = data.callback;
				callbackEmpty = data.callbackEmpty;
			}

			void call(UI::Control * source)
			{
				if (callbackEmpty)
					(handler->*callbackEmpty)();

				if (callback)
					(handler->*callback)(source);
			}
		};
		List<OnPressData> m_onPressData;

		void onPressInternal(EventHandler * handler, EventHandler::eventCallback fn);
		void onPressInternal(EventHandler * handler, EventHandler::eventCallbackEmpty fn);
	public:
		Button(const DynString& name, Vector2 position = Vector2(), Vector2 size = Vector2());
		virtual ~Button();

		virtual void setText(const WDynString& text);
		virtual WDynString getText();

		virtual void render(UIRenderContext& context);

		virtual bool handleInput();

		template <typename T>
		void onPressSubscribe(EventHandler * handler, void (T::*fn)()) { onPressInternal(handler, static_cast<EventHandler::eventCallbackEmpty>(fn)); }		

		template <typename T>
		void onPressSubscribe(EventHandler * handler, void (T::*fn)(Control)) { onPressInternal(handler, static_cast<EventHandler::eventCallback>(fn)); }
	};
}