//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/fonts/Font.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Font.h"

#include <math/Rect.h>

#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>

#include <graphics/renderer/Renderer.h>
#include <graphics/Material.h>
#include <graphics/MaterialLib.h>

#include <core/Logger.h>

Font::Font(FilePath fontPath, uint32 size, flags32 flags)
	: m_textureId(0)
{
	// Basic charset
	char *_charset = "abcdefghijklmnopqrstuwxyz"\
		"ABCDEFGHIJKLMNOPQRSTUWXYZ"\
		"0123456789";

	uint32 characters = strlen(_charset);

	// Init free type
	FT_Library ftLibrary;
	if (FT_Init_FreeType(&ftLibrary) != 0)
	{
		Error("font", "Cannot initialize freetype.");
		return;
	}

	FT_Face face;
	if (FT_New_Face(ftLibrary, fontPath, 0, &face) != 0)
	{
		Error("font", "Cannot open font file %s.", *fontPath);
		return;
	}

	size *= 64; // ft size = 1/64th of pixel
	if (FT_Set_Char_Size(face, size, size, 96, 96) != 0)
	{
		Error("font", "Cannot set size of character");
		return;
	}

	if (FT_Set_Pixel_Sizes(face, 0, size/64) != 0)
	{
		Error("font", "Cannot set pixel size");
		return;
	}

	uint32 penX = 0;
	uint32 penY = 0;
	uint32 width = 1024;
	uint32 height = 1024;
	uint8 *texture = new uint8[1024 * 1024];
	memset(texture, 0, 1024 * 1024);

	for (uint32 i = 0; i < characters; ++i)
	{
		FT_UInt charIndex = FT_Get_Char_Index(face, _charset[i]);
		Info("font", "%c = %d", _charset[i], charIndex);

		int32 error = FT_Load_Glyph(face, charIndex, FT_LOAD_DEFAULT);
		if (error)
		{
			Error("font", "Skiping - %d/%d", error, __LINE__);
			continue;
		}

		if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
		{
			error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
			if (error)
			{
				Error("font", "Skiping - %d/%d", error, __LINE__);
				continue;
			}
		}

		//FT_Glyph_To_Bitmap(&face->glyph, FT_RENDER_MODE_NORMAL, NULL, TRUE);

		uint32 x = penX + face->glyph->bitmap_left;
		uint32 y = penY - face->glyph->bitmap_top;
		for (; x < penX + face->glyph->advance.x; ++x)
		{
			for (; y < penY - face->glyph->advance.y; ++y)
			{
				texture[x + height * y] = face->glyph->bitmap.buffer[x * height * y];
			}
		}

		penX += face->glyph->advance.x >> 6;
		penY += face->glyph->advance.y >> 6;
	}

	// Free freetype
	FT_Done_Face(face);
	FT_Done_FreeType(ftLibrary);

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA8, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, texture);

	delete[]texture;

	m_material = MaterialLib::get()->findByName("font");
}

Font::~Font()
{
	if (glIsTexture(m_textureId))
	{
		glDeleteTextures(1, &m_textureId);
		m_textureId = 0;
	}
}

void Font::render(DynString string, const Rect& rect, const Color& color, flags32 flags)
{
	Renderer::get().renderFont(string, rect, color, flags, this);
}
