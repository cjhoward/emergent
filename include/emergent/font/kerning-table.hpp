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

#ifndef EMERGENT_FONT_KERNING_TABLE_HPP
#define EMERGENT_FONT_KERNING_TABLE_HPP

#include <emergent/math/types.hpp>
#include <map>

namespace Emergent
{

/**
 * Contains kerning information for a font.
 *
 * @ingroup font
 */
class KerningTable
{
public:
	/**
	 * Sets the kerning vector for a specified pair of glyphs.
	 *
	 * @param first Specifies the first glyph in the pair.
	 * @param second Specifies the second glyph in the pair.
	 * @param kerning Specifies the kerning vector.
	 */
	void setKerning(char32_t first, char32_t second, const Vector2& kerning);

	/**
	 * Deletes all kerning information.
	 */
	void clear();

	/**
	 * Returns the kerning vector for a specified pair of glyphs.
	 *
	 * @param first Specifies the first glyph in the pair.
	 * @param second Specifies the second glyph in the pair.
	 * @return Kerning vector.
	 */
	Vector2 getKerning(char32_t first, char32_t second) const;
	
	/**
	 * Returns `true` if the kerning table is empty.
	 *
	 * @return `true` if the kerning table is empty, `false` otherwise.
	 */
	bool isEmpty() const;
	
private:
	std::map<char32_t, std::map<char32_t, Vector2>> pairs;
};

inline void KerningTable::setKerning(char32_t first, char32_t second, const Vector2& kerning)
{
	pairs[first][second] = kerning;
}

inline void KerningTable::clear()
{
	pairs.clear();
}

inline Vector2 KerningTable::getKerning(char32_t first, char32_t second) const
{
	auto firstIt = pairs.find(first);
	if (firstIt != pairs.end())
	{
		auto secondIt = (*firstIt).second.find(second);
		if (secondIt != (*firstIt).second.end())
		{
			return (*secondIt).second;
		}
	}
	
	return Vector2(0.0f, 0.0f);
}

inline bool KerningTable::isEmpty() const
{
	return pairs.empty();
}

} // namespace Emergent

#endif // EMERGENT_FONT_KERNING_TABLE_HPP
