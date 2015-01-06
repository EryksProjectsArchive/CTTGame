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

#include <resources/materials/MaterialLib.h>

#include <core/Logger.h>

#include <io/fs/FileSystem.h>

#include <core/WDynString.h>

Font::Font(const FilePath& fontPath, uint32 size)
	: m_textureId(0), m_loaded(false), m_size(size)
{
	memset(m_data, 0, sizeof(m_data));

	// Init free type
	FT_Library ftLibrary;
	if (FT_Init_FreeType(&ftLibrary) != 0)
	{
		Error("font", "Cannot initialize freetype.");
		return;
	}

	File *file = FileSystem::get()->open(fontPath, FileOpenMode::Read | FileOpenMode::Binary);
	if (!file->isLoaded())
	{
		FileSystem::get()->close(file);
		Error("font", "Cannot open font file \"%s\".", fontPath.get());
		return;
	}

	file->seek(0, SeekOrigin::End);
	long _size = file->tell();
	file->rewind();
	uint8 * buffer = new uint8[_size + 1];
	file->read(buffer, _size, sizeof(uint8));
	buffer[_size] = '\0';
	
	FileSystem::get()->close(file);

	FT_Face face;
	int errid = FT_New_Memory_Face(ftLibrary, buffer, _size, 0, &face);
	if (errid != 0)
	{
		Error("font", "Cannot create new face (errid: %d).", errid);
		delete[] buffer;
		return;
	}

	FT_Set_Pixel_Sizes(face, size, 0);

	uint32 width = 2000;
	uint32 height = 1900;

	uint32 x = 0;
	uint32 y = 0;

	uint8 *texture = new uint8[width * height];
	memset(texture, 0, width * height);
	float f_Width = (float)width;
	float f_Height = (float)height;

	float lineHeight = 0;
	for (uint32 c = 0; c < 65535; ++c)
	{
		FT_UInt charIndex = FT_Get_Char_Index(face, c);
		if (!charIndex)
			continue;
	
		int32 error = FT_Load_Glyph(face, charIndex, FT_LOAD_DEFAULT);
		if (error)
		{
			Error("font", "Skiping - %d/%d", error, __LINE__);
			continue;
		}

		FT_Glyph glyph;
		FT_Get_Glyph(face->glyph, &glyph);

		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		uint8 *image = bitmap_glyph->bitmap.buffer;
	
		for (int32 _y = 0; _y < bitmap_glyph->bitmap.rows; ++_y)
			for (int32 _x = 0; _x < bitmap_glyph->bitmap.width; ++_x)
				texture[((_x + x) + width * (_y + y))] = image[_x + bitmap_glyph->bitmap.width * _y];

		m_data[c].set = 1;
		m_data[c].x = float(x) / f_Width;
		m_data[c].y = ((float(y)) / f_Height);
		m_data[c].w = (float(x) + float(bitmap_glyph->bitmap.width)) / f_Width;
		m_data[c].h = (float(y) + float(bitmap_glyph->bitmap.rows)) / f_Height;
		m_data[c].left = float(bitmap_glyph->left);
		m_data[c].top = float(bitmap_glyph->top);
		m_data[c].bmw = float(bitmap_glyph->bitmap.width);
		m_data[c].bmh = float(bitmap_glyph->bitmap.rows);

		if (lineHeight < m_data[c].bmh)
			lineHeight = m_data[c].bmh;

		x += uint32(m_data[c].bmw);
		if ((x + size) >= width)
		{
			x = 0;
			y += uint32(lineHeight);
			lineHeight = 0;
		}

		if ((y + lineHeight) >= height)
		{
			Error("Font", "Height limit of '%s' font atlas has been exceeded! (%d)", fontPath.get(), uint32(y+lineHeight));
			break;
		}
	}

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texture);

	// Free freetype
	FT_Done_Face(face);
	FT_Done_FreeType(ftLibrary);

	delete[]texture;
	delete[] buffer;

	m_material = MaterialLib::get()->findByName("font");
	m_material->acquire();

	m_loaded = true;

	if (!m_data['?'].set)
	{
		Warning("Font", "Cannot find '?' character data for font '%s'.", fontPath.get());
		return;
	}
}

Font::~Font()
{
	if (glIsTexture(m_textureId))
	{
		glDeleteTextures(1, &m_textureId);
		m_textureId = 0;
	}

	if (m_material)
		m_material->release();
}

void Font::render(const WDynString& string, const Rect& rect, const Color& color, flags32 flags)
{
	if (m_loaded)
	{
		Renderer::get()->renderFont(string, rect, color, flags, this);
	}
}

Font::GlyphData Font::getData(wchar_t c)
{
	return m_data[c];
}

float Font::calculateWidth(const WDynString& string)
{
	float w = 0;
	for (uint32 i = 0; i < string.getLength(); ++i)
	{
		wchar_t c = string[i];
		if (c == ' ')
		{
			w += m_size / 2;
			continue;
		}

		w += m_data[c].bmw + 2;
	}
	return w;
}

float Font::calculateHeight(const WDynString& string)
{
	float h = 0;
	for (uint32 i = 0; i < string.getLength(); ++i)
	{		
		wchar_t c = string[i];
		float _h = m_data[c].bmh + 2;
		if (_h > h)
			h = _h;
	}
	return h;
}