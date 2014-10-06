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

#include <io/fs/FileSystem.h>

Font::Font(FilePath fontPath, uint32 size, flags32 flags)
	: m_textureId(0), m_loaded(false)
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
		Error("font", "Cannot open font file \"%s\".", *fontPath);
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

	if (FT_Set_Pixel_Sizes(face, 0, size/64) != 0)
	{
		Error("font", "Cannot set pixel size");
		delete[] buffer;
		return;
	}

	uint32 x = 0;
	uint32 y = 0;
	uint32 width = 1024;
	uint32 height = 1024;
	uint8 *texture = new uint8[2 * 1024 * 1024]; // we are using 1 channel for luminosity and 1 channel for alpha to make fonts looking better
	memset(texture, 0, 1024 * 1024);

	for (uint8 c = 32; c < 255; ++c)
	{
		FT_UInt charIndex = FT_Get_Char_Index(face, c);
		if (!charIndex)
			continue;
		//Info("font", "%d %c = %d", c, c, charIndex);

		int32 error = FT_Load_Glyph(face, charIndex, FT_LOAD_DEFAULT);
		if (error)
		{
			Error("font", "Skiping - %d/%d", error, __LINE__);
			continue;
		}

		FT_Glyph glyph;
		FT_Get_Glyph(face->glyph, &glyph);

		// Generate bitmap
		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);

		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		uint8 *image = bitmap_glyph->bitmap.buffer;


		for (uint32 _x = 0; _x < bitmap_glyph->bitmap.width; ++_x)
		{
			for (uint32 _y = 0; _y < bitmap_glyph->bitmap.rows; ++_y)
			{
				uint32 idx = (x + _x) + width * (y + _y);
				uint32 fntIdx = _x + bitmap_glyph->bitmap.width * _y;
				texture[idx + 0] = image[fntIdx + 0];
				texture[idx + 1] = image[fntIdx + 1];
			}
		}

		x += bitmap_glyph->bitmap.width;
		if (x >= width)
		{
			x = 0;
			y += bitmap_glyph->bitmap.rows;
		}
		if (y >= height)
		{
			Error("font", "Height is too long!");
		}
	}

	// Free freetype
	FT_Done_Face(face);
	FT_Done_FreeType(ftLibrary);

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, texture);

	delete[]texture;
	delete[] buffer;

	m_material = MaterialLib::get()->findByName("font");
	m_loaded = true;

	
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
	if (m_loaded)
	{
		//Renderer::get().renderFont(string, rect, color, flags, this);
	}
}
