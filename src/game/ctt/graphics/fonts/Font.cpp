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

Font::Font(FilePath fontPath, uint32 size, flags32 flags)
	: m_textureId(0), m_loaded(false), m_size(size)
{
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

	uint32 width = 1280;
	uint32 height = 720;

	uint32 x = 0;
	uint32 y = 0;

	uint8 *texture = new uint8[width * height];
	memset(texture, 0, width * height);
	float f_Width = (float)width;
	float f_Height = (float)height;

	for (uint8 c = 32; c < 255; ++c)
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
		{
			for (int32 _x = 0; _x < bitmap_glyph->bitmap.width; ++_x)
			{
				int32 xpadding = 0;// bitmap_glyph->left;
				int32 ypadding = 0;// bitmap_glyph->top;
				
				texture[((_x + x + xpadding) + width * (_y + y + ypadding))] = image[_x + bitmap_glyph->bitmap.width * _y];
			}
		}

		
		GlyphData *data = new GlyphData;
		data->set = 1;
		data->code = c;
		data->x = float(x) / f_Width;
		data->y = ((float(y)) / f_Height);
		data->w = (float(x) + float(bitmap_glyph->bitmap.width)) / f_Width;
		data->h = ((float(y) + float(bitmap_glyph->bitmap.rows))) / f_Height;
		data->left = float(bitmap_glyph->left);
		data->top = float(bitmap_glyph->top);
		data->advance.x = float(glyph->advance.x);
		data->advance.y = float(glyph->advance.y);
		data->bmw = float(bitmap_glyph->bitmap.width);
		data->bmh = float(bitmap_glyph->bitmap.rows);
		m_data.pushBack(data);

		x += size + 5;
		if ((x + size + 5) >= width)
		{
			x = 0;
			y += size + 5;
		}

		if ((y + size + 5) >= height)
		{
			Error("Font", "Height limit of font atlas has been exceeded!");
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
}

Font::~Font()
{
	if (glIsTexture(m_textureId))
	{
		glDeleteTextures(1, &m_textureId);
		m_textureId = 0;
	}

	if (m_material)
		m_material->free();

	for (GlyphData *data : m_data)
		delete data;

	m_data.clear();
}

void Font::render(DynString string, const Rect& rect, const Color& color, flags32 flags)
{
	if (m_loaded)
	{
		Renderer::get().renderFont(string, rect, color, flags, this);
	}
}


Font::GlyphData& Font::getData(unsigned char xc)
{
	for (GlyphData * data : m_data)
	{
		if (data->code == xc)
			return *data;
	}

	return Font::GlyphData();
}