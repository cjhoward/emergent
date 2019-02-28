/*
 * Copyright (C) 2017-2019  Christopher J. Howard
 *
 * This file is part of Emergent.
 *
 * Emergent is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Emergent is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emergent.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <emergent/font/typeface.hpp>
#include <emergent/font/font.hpp>
#include <emergent/font/font-metrics.hpp>
#include <emergent/font/glyph.hpp>
#include <emergent/font/glyph-metrics.hpp>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Emergent
{
	
Typeface::Typeface(std::istream* is):
	library(nullptr),
	face(nullptr)
{
	// Init FreeType library
	FT_Library ftLibrary;
	FT_Error error = FT_Init_FreeType(&ftLibrary);
	if (error != 0)
	{
		std::stringstream stream;
		stream << std::string("Typeface::Typeface(): Failed to init FreeType: error code (") << error << std::string(")");
		throw std::runtime_error(stream.str().c_str());
	}

	// Read input stream into buffer
	is->seekg(0, is->end);
	std::size_t fileSize = is->tellg();
	unsigned char* fileBuffer = new unsigned char[fileSize];
	is->seekg(0, is->beg);
	is->read(reinterpret_cast<char*>(&fileBuffer[0]), fileSize);

	// Load FreeType face
	FT_Face ftFace;
	error = FT_New_Memory_Face(ftLibrary, fileBuffer, static_cast<FT_Long>(fileSize), 0, &ftFace);

	// WARNING!!!!!!!!!!!!!!!!!!!!!!!!
	// Free file buffer
	//delete[] fileBuffer;

	if (error != 0)
	{
		std::stringstream stream;
		stream << std::string("Typeface::Typeface(): Failed to load FreeType font: error code (") << error << std::string(")");
		FT_Done_FreeType(ftLibrary);
		throw std::runtime_error(stream.str().c_str());
	}

	// Store pointer to initialized FreeType library
	this->library = ftLibrary;

	// Store pointer to FreeType face
	this->face = ftFace;
}

Typeface::~Typeface()
{
	// Free FreeType face
	FT_Done_Face(static_cast<FT_Face>(face));
	
	// Free FreeType library
	FT_Done_FreeType(static_cast<FT_Library>(library));
}

Font* Typeface::createFont(int size)
{
	FT_Face ftFace = static_cast<FT_Face>(this->face);

	// Set FreeType face size
	FT_Error error = FT_Set_Pixel_Sizes(ftFace, 0, size);
	if (error != 0)
	{
		std::stringstream stream;
		stream << std::string("Typeface::createFont(): Failed to set FreeType face size: error code (") << error << std::string(")");
		throw std::runtime_error(stream.str().c_str());
	}

	// Create font metrics
	FontMetrics metrics;
	metrics.setAscender(ftFace->size->metrics.ascender / 64.0f);
	metrics.setDescender(ftFace->size->metrics.descender / 64.0f);
	metrics.setHeight(ftFace->size->metrics.height / 64.0f);
	metrics.setMaxAdvance(ftFace->size->metrics.max_advance / 64.0f);
	metrics.setUnderlineOffset(ftFace->underline_position / 64.0f);
	metrics.setUnderlineWeight(ftFace->underline_thickness / 64.0f);

	// Create font
	Font* font = new Font(metrics, 1024, 1024);

	return font;
}

std::size_t Typeface::loadCharset(Font* font, const UnicodeRange& charset)
{
	std::size_t unloaded = 0;
	for (char32_t charcode = charset.start; charcode <= charset.end; ++charcode)
	{
		if (!loadGlyph(font, charcode))
		{
			++unloaded;
		}
	}

	rebuildKerningTable(font);

	return unloaded;
}

std::size_t Typeface::loadCharset(Font* font, const std::set<char32_t>& charset)
{
	std::size_t unloaded = 0;
	for (char32_t charcode: charset)
	{
		if (!loadGlyph(font, charcode))
		{
			++unloaded;
		}
	}

	rebuildKerningTable(font);

	return unloaded;
}

bool Typeface::loadGlyph(Font* font, char32_t charcode)
{
	// Get size of the font, in pixels
	int size = font->getMetrics().getHeight();

	// Set FreeType face size
	FT_Face ftFace = static_cast<FT_Face>(this->face);
	FT_Error error = FT_Set_Pixel_Sizes(ftFace, 0, size);
	if (error != 0)
	{
		std::stringstream stream;
		stream << std::string("Typeface::loadGlyph(): Failed to set FreeType face size: error code (") << error << std::string(")");
		throw std::runtime_error(stream.str().c_str());
	}
	
	// Set glyph loading flags
	FT_Int32 flags = FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT;
	
	// Get glyph index from character code
	FT_UInt index = FT_Get_Char_Index(ftFace, charcode);

	//std::cout << "charcode: " << charcode << std::endl;
	//std::cout << "index: " << index << std::endl;
	
	// Load glyph
	error = FT_Load_Glyph(ftFace, index, flags);
	if (error != 0)
	{
		return false;
	}
	
	// Load glyph metrics
	GlyphMetrics glyphMetrics;
	glyphMetrics.setWidth(ftFace->glyph->metrics.width / 64.0f);
	glyphMetrics.setHeight(ftFace->glyph->metrics.height / 64.0f);
	glyphMetrics.setHorizontalBearing(
		Vector2(
			ftFace->glyph->metrics.horiBearingX / 64.0f,
			ftFace->glyph->metrics.horiBearingY / 64.0f));
	glyphMetrics.setHorizontalAdvance(ftFace->glyph->metrics.horiAdvance / 64.0f);
	glyphMetrics.setVerticalBearing(
		Vector2(
			ftFace->glyph->metrics.vertBearingX / 64.0f,
			ftFace->glyph->metrics.vertBearingY / 64.0f));
	glyphMetrics.setVerticalAdvance(ftFace->glyph->metrics.vertAdvance / 64.0f);

	//std::cout << glyphMetrics.getWidth() << std::endl;
	//std::cout << glyphMetrics.getHeight() << std::endl;
	
	// Load glyph image data
	const FT_Bitmap& bitmap = ftFace->glyph->bitmap;
	unsigned int pixelCount = bitmap.width * bitmap.rows;
	unsigned char* pixels = new unsigned char[pixelCount * 2];	
	for (unsigned int y = 0; y < bitmap.rows; ++y)
	{
		for (unsigned int x = 0; x < bitmap.width; ++x)
		{
			std::size_t index0 = (bitmap.rows - y - 1) * bitmap.width + x;
			std::size_t index1 = (y * bitmap.width + x) * 2;
			
			pixels[index1] = 255;
			pixels[index1 + 1] = bitmap.buffer[index0];
		}
	}
	
	// Add glyph to font
	font->addGlyph(charcode, glyphMetrics, pixels, bitmap.width, bitmap.rows);
	
	// Free glyph image data
	delete[] pixels;

	return true;
}

void Typeface::rebuildKerningTable(Font* font)
{
	// Get size of the font, in pixels
	int size = font->getMetrics().getHeight();

	// Set FreeType face size
	FT_Face ftFace = static_cast<FT_Face>(this->face);
	FT_Error error = FT_Set_Pixel_Sizes(ftFace, 0, size);
	if (error != 0)
	{
		std::stringstream stream;
		stream << std::string("Typeface::rebuildKerningTable(): Failed to set FreeType face size: error code (") << error << std::string(")");
		throw std::runtime_error(stream.str().c_str());
	}

	// Check if typeface has kerning data
	if (!FT_HAS_KERNING(ftFace))
	{
		return;
	}

	// Rebuild kerning table
	const std::set<char32_t>& charset = font->getCharset();
	for (char32_t first: charset)
	{
		FT_UInt firstIndex = FT_Get_Char_Index(ftFace, first);
		
		for (char32_t second: charset)
		{
			FT_UInt secondIndex = FT_Get_Char_Index(ftFace, second);

			FT_Vector kerning;
			error = FT_Get_Kerning(ftFace, firstIndex, secondIndex, FT_KERNING_DEFAULT, &kerning);
			if (error != 0)
			{
				continue;
			}
			
			font->getKerningTable()->setKerning(first, second, Vector2(kerning.x, kerning.y) / 64.0f);
		}
	}
}

} // namespace Emergent
