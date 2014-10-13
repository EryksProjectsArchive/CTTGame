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
	: m_textureId(0), m_loaded(false)
{
	// Reset glyph data
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

	FT_Set_Char_Size(face, size<<6, size<<6, 96, 96);


	uint32 width = 1280;
	uint32 height = 720;

	uint32 x = 0;
	uint32 y = 0;

	uint8 *texture = new uint8[2 * width * height]; // we are using 1 channel for luminosity and 1 channel for alpha to make fonts looking better
	memset(texture, 0, width * height * 2);
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

		uint8 idx = charIndex % 256;
		Info("f", "%c / %d", idx ,charIndex);
		m_data[idx].set = 1;
		m_data[idx].code = idx;
		m_data[idx].x = (float)x / f_Width;
		m_data[idx].y = 1 - ((float)y / f_Height);
		m_data[idx].w = ((float)x + (float)bitmap_glyph->bitmap.width) / (float)f_Width;
		m_data[idx].h = 1 - (((float)y + (float)bitmap_glyph->bitmap.rows) / (float)f_Height);
		Info("f", "%fx%fx%fx%f", m_data[idx].x, m_data[idx].y, m_data[idx].w, m_data[idx].h);

		x += size + 16;
		if ((x + size + 16) >= width)
		{
			x = 0;
			y += size + 16;
		}

		if ((y + size + 16) >= height)
		{
			Error("Font", "Height limit of font atlas has been exceeded!");
			break;
		}
	}

	// Free freetype
	FT_Done_Face(face);
	FT_Done_FreeType(ftLibrary);

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R, width, height, 0, GL_R, GL_UNSIGNED_BYTE, texture);

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
}

void Font::render(DynString string, const Rect& rect, const Color& color, flags32 flags)
{
	if (m_loaded)
	{
		//Renderer::get().renderFont(string, rect, color, flags, this);
	}
}
