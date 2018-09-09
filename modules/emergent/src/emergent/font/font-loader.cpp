/*
 * Copyright (C) 2017-2018  Christopher J. Howard
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

#include <emergent/font/font-loader.hpp>
#include <emergent/font/font.hpp>
#include <emergent/font/font-metrics.hpp>
#include <emergent/font/glyph.hpp>
#include <emergent/font/glyph-metrics.hpp>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Emergent
{
	
FontLoader::FontLoader()
{
}

FontLoader::~FontLoader()
{
}

bool FontLoader::load(const std::string& filename, int size, const std::vector<UnicodeRange>& ranges, Font* font)
{
	FT_Library library;
	FT_Error error = FT_Init_FreeType(&library);
	if (error != 0)
	{		
		std::cerr << "Failed to initialize FreeType: error code (" << error << ")" << std::endl;
	}

	// Create typeface
	FT_Face face;
	error = FT_New_Face(library, filename.c_str(), 0, &face);
	if (0 != error)
	{
		std::cerr << "Failed to load FreeType font: error code (" << error << ")" << std::endl;
		return false;
	}
	
	// Set font size
	error = FT_Set_Pixel_Sizes(face, 0, size);
	if (0 != error)
	{
		FT_Done_Face(face);

		std::cerr << "Failed to set FreeType face size: error code (" << error << ")" << std::endl;
		return false;
	}
	
	// Get font metrics
	FontMetrics fontMetrics;
	fontMetrics.setAscender(face->size->metrics.ascender / 64.0f);
	fontMetrics.setDescender(face->size->metrics.descender / 64.0f);
	fontMetrics.setHeight(face->size->metrics.height / 64.0f);
	fontMetrics.setMaxAdvance(face->size->metrics.max_advance / 64.0f);
	fontMetrics.setUnderlineOffset(face->underline_position / 64.0f);
	fontMetrics.setUnderlineWeight(face->underline_thickness / 64.0f);
	font->setMetrics(fontMetrics);
	
	// Set glyph loading flags
	FT_Int32 flags = FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT;
	
	// Load glyphs from specified Unicode ranges
	for (const UnicodeRange& range: ranges)
	{
		for (char32_t charcode = range.start; charcode <= range.end; ++charcode)
		{
			FT_UInt index = FT_Get_Char_Index(face, charcode);
			
			error = FT_Load_Glyph(face, index, flags);
			if (0 != error)
			{
				std::cerr << "Failed to load glyph " << charcode << ": error code (" << error << ")" << std::endl;
				continue;
			}
			
			// Load glyph metrics
			GlyphMetrics glyphMetrics;
			glyphMetrics.setWidth(face->glyph->metrics.width / 64.0f);
			glyphMetrics.setHeight(face->glyph->metrics.height / 64.0f);
			glyphMetrics.setHorizontalBearing(
				Vector2(
					face->glyph->metrics.horiBearingX / 64.0f,
					face->glyph->metrics.horiBearingY / 64.0f));
			glyphMetrics.setHorizontalAdvance(face->glyph->metrics.horiAdvance / 64.0f);
			glyphMetrics.setVerticalBearing(
				Vector2(
					face->glyph->metrics.vertBearingX / 64.0f,
					face->glyph->metrics.vertBearingY / 64.0f));
			glyphMetrics.setVerticalAdvance(face->glyph->metrics.vertAdvance / 64.0f);
			
			// Load glyph image
			const FT_Bitmap& bitmap = face->glyph->bitmap;
			
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
			
			// Create glyph
			font->createGlyph(charcode, glyphMetrics, pixels, bitmap.width, bitmap.rows);
			
			delete[] pixels;
		}
	}

	// Build kerning table
	if (FT_HAS_KERNING(face))
	{
		for (const UnicodeRange& firstRange: ranges)
		{
			for (char32_t first = firstRange.start; first <= firstRange.end; ++first)
			{
				FT_UInt firstIndex = FT_Get_Char_Index(face, first);
				
				for (const UnicodeRange& secondRange: ranges)
				{
					for (char32_t second = secondRange.start; second <= secondRange.end; ++second)
					{
						FT_UInt secondIndex = FT_Get_Char_Index(face, second);

						FT_Vector kerning;
						error = FT_Get_Kerning(face, firstIndex, secondIndex, FT_KERNING_DEFAULT, &kerning);
						if (0 != error)
						{
							continue;
						}
						
						font->getKerningTable()->setKerning(first, second, Vector2(kerning.x, kerning.y) / 64.0f);
					}
				}
			}
		}
	}
	
	FT_Done_Face(face);
	FT_Done_FreeType(library);

	return true;
}

} // namespace Emergent
