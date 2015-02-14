//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/UISkin.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/DynString.h>

namespace UI
{
	class Skin
	{
	public:
		struct Colors
		{
			Color buttonNormal;
			Color buttonHover;
			Color labelNormal;
			Color labelShadow;
		};

		struct ButtonGeometryData
		{
			float x, y, w, h;

			ButtonGeometryData()
			{
				x = y = 0;
				w = h = 1;
			}
		};
	private:
		DynString m_name;

		Material * m_material;

		Colors m_colors;

		struct
		{
			ButtonGeometryData buttonNormal;
			ButtonGeometryData buttonHover;
		} m_geometry;

		void setupDefaults();
		void setup();
	public:
		Skin(const DynString& name);
		virtual ~Skin();

		virtual DynString getName();

		virtual Material *getMaterial();

		virtual const Colors& colors();
		
		virtual Geometry<Vertex2d>* generateButtonGeometry(const Rect& rect, bool hover);		
	};
}