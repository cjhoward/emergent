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

#ifndef EMERGENT_FONT_GLYPH_HPP
#define EMERGENT_FONT_GLYPH_HPP

#include <emergent/font/glyph-metrics.hpp>
#include <emergent/geometry/rect.hpp>
#include <cstdlib>

namespace Emergent
{

/**
 * Contains glyph information.
 *
 * @ingroup font
 */
class Glyph
{
public:
	/**
	 * Sets the glyph metrics.
	 *
	 * @param metrics Specifies glyph metrics.
	 */
	void setMetrics(const GlyphMetrics& metrics);
	
	/**
	 * Sets the rect containing the glyph texture.
	 *
	 * @param bounds Specifies a rect.
	 */
	void setBounds(const Rect& bounds);

	/**
	 * Returns the glyph metrics.
	 *
	 * @return Glyph metrics.
	 */
	const GlyphMetrics& getMetrics() const;

	/**
	 * Returns a rect containing the glyph texture.
	 *
	 * @return Rect containing the glyph texture.
	 */
	const Rect& getBounds() const;

private:
	GlyphMetrics metrics;
	Rect bounds;
};

inline void Glyph::setMetrics(const GlyphMetrics& metrics)
{
	this->metrics = metrics;
}

inline void Glyph::setBounds(const Rect& bounds)
{
	this->bounds = bounds;
}

inline const GlyphMetrics& Glyph::getMetrics() const
{
	return metrics;
}

inline const Rect& Glyph::getBounds() const
{
	return bounds;
}

} // namespace Emergent

#endif // EMERGENT_FONT_GLYPH_HPP
