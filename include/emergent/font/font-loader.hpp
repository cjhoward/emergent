/*
 * Copyright (C) 2017  Christopher J. Howard
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

#ifndef EMERGENT_FONT_FONT_LOADER_HPP
#define EMERGENT_FONT_FONT_LOADER_HPP

#include <emergent/font/unicode-range.hpp>
#include <string>
#include <vector>

namespace Emergent
{

class Font;

/**
 * Loads fonts using the Freetype library.
 *
 * @ingroup font
 */
class FontLoader
{
public:
	/**
	 * Creates an instance of FontLoader.
	 */
	FontLoader();
	
	/**
	 * Destroys an instance of FontLoader.
	 */
	~FontLoader();
	
	/**
	 * Loads a font.
	 *
	 * @param filename Font filename.
	 * @param size Size (in pixels) of the font.
	 * @param ranges Unicode ranges to load.
	 * @param font Font to load.
	 * @return `true` if the font was loaded successfully, `false` otherwise.
	 */
	bool load(const std::string& filename, int size, const std::vector<UnicodeRange>& ranges, Font* font);

private:
	void* library;
};

} // namespace Emergent

#endif // EMERGENT_FONT_FONT_LOADER_HPP