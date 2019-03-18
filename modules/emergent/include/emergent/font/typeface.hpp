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

#ifndef EMERGENT_FONT_TYPEFACE_HPP
#define EMERGENT_FONT_TYPEFACE_HPP

#include <emergent/font/unicode-range.hpp>
#include <istream>
#include <map>
#include <set>

namespace Emergent
{

class Font;

/**
 * Loads fonts using the Freetype library.
 *
 * @ingroup font
 */
class Typeface
{
public:
	/**
	 * Creates a typeface.
	 *
	 * @param is Input stream containing TTF, OTF, or other font file data.
	 */
	Typeface(std::istream* is);
	
	/**
	 * Destroys a typeface.
	 */
	~Typeface();
	
	/**
	 * Creates a font with the specified size.
	 *
	 * @param size Size of the font (in pixels)
	 * @return Font of the specified size.
	 */
	Font* createFont(int size);

	/**
	 * Loads each glyph of a character set into a font.
	 *
	 * @param font Font into which the glyphs will be loaded.
	 * @param charset Character set defined by a range of unicode characters.
	 * @return Number of characters which were unable to be loaded.
	 */
	std::size_t loadCharset(Font* font, const UnicodeRange& charset);

	/**
	 * Loads each glyph of a character set into a font.
	 *
	 * @param font Font into which the glyphs will be loaded.
	 * @param charset Character set defined by a set of character codes.
	 * @return Number of characters which were unable to be loaded.
	 */
	std::size_t loadCharset(Font* font, const std::set<char32_t>& charset);

private:
	/**
	 * Loads a single glyph into a font.
	 *
	 * @param font Font into which the glyph will be loaded.
	 * @param charcode Character code of the glyph to load.
	 * @return true if the glyph was loaded successfully, false otherwise.
	 */
	bool loadGlyph(Font* font, char32_t charcode);

	/**
	 * Rebuilds the kerning table of a font.
	 *
	 * @param font Font whose kerning table should be rebuilt.
	 */
	void rebuildKerningTable(Font* font);

	unsigned char* fileBuffer;
	void* library;
	void* face;
};

} // namespace Emergent

#endif // EMERGENT_FONT_TYPEFACE_HPP

