//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/fonts/Font.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/String.h>
#include <core/DynString.h>
#include <core/SharedPtr.h>
#include <core/List.h>

class Font
{
private:	
	struct GlyphData
	{
		unsigned char set;
		float x;
		float y;
		float w;
		float h;
		float top;
		float left;
		float bmw;
		float bmh;
	};

	uint32 m_textureId;

	Material* m_material;

	bool m_loaded;

	GlyphData m_data[65535];
	uint32 m_size;
public:
	Font(const FilePath& fontPath, uint32 size);
	~Font();

	void render(const WDynString& string, const Rect& rect, const Color& color, flags32 flags);

	Font::GlyphData getData(wchar_t c);
public:
	struct DrawFlags
	{
		enum Type
		{
			None = 0,
			NoClip = 1,

			// Separated position enum?
			VerticalCenter = 2,
			HorizontalCenter = 3,
		};
	};

	friend class Renderer;
};