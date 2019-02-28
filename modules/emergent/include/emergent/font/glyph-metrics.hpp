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

#ifndef EMERGENT_FONT_GLYPH_METRICS_HPP
#define EMERGENT_FONT_GLYPH_METRICS_HPP

#include <emergent/math/types.hpp>

namespace Emergent
{

/**
 * Contains the metrics of a glyph.
 *
 * @ingroup font
 */
class GlyphMetrics
{
public:
	/**
	 * Sets the width of the glyph.
	 *
	 * @param width Specifies the width of the glyph.
	 */
	void setWidth(float width);

	/**
	 * Sets the height of the glyph.
	 *
	 * @param height Specifies the height of the glyph.
	 */
	void setHeight(float height);

	/**
	 * Sets the bearing for a horizontal layout.
	 *
	 * @param bearing Specifies the left and top side bearings.
	 */
	void setHorizontalBearing(const Vector2& bearing);
	
	/**
	 * Sets the advance width for a horizontal layout.
	 *
	 * @param advance Specifies the advance width.
	 */
	void setHorizontalAdvance(float advance);

	/**
	 * Sets the bearing for a vertical layout.
	 *
	 * @param bearing Specifies the left and top side bearings.
	 */
	void setVerticalBearing(const Vector2& bearing);

	/**
	 * Sets the advance height for a vertical layout.
	 *
	 * @param advance Specifies the advance height.
	 */
	void setVerticalAdvance(float advance);

	/**
	 * Returns the width of the glyph.
	 */
	float getWidth() const;

	/**
	 * Returns the height of the glyph.
	 */
	float getHeight() const;
	
	/**
	 * Returns the bearing for a horizontal layout.
	 */
	const Vector2& getHorizontalBearing() const;

	/**
	 * Returns the advance width for a horizontal layout.
	 */
	float getHorizontalAdvance() const;
	
	/**
	 * Returns the bearing for a vertical layout.
	 */
	const Vector2& getVerticalBearing() const;
	
	/**
	 * Returns the advance height for a vertical layout.
	 */
	float getVerticalAdvance() const;

private:
	float width;
	float height;
	Vector2 horizontalBearing;
	float horizontalAdvance;
	Vector2 verticalBearing;
	float verticalAdvance;
};

inline void GlyphMetrics::setWidth(float width)
{
	this->width = width;
}

inline void GlyphMetrics::setHeight(float height)
{
	this->height = height;
}

inline void GlyphMetrics::setHorizontalBearing(const Vector2& bearing)
{
	this->horizontalBearing = bearing;
}

inline void GlyphMetrics::setHorizontalAdvance(float advance)
{
	this->horizontalAdvance = advance;
}

inline void GlyphMetrics::setVerticalBearing(const Vector2& bearing)
{
	this->verticalBearing = bearing;
}

inline void GlyphMetrics::setVerticalAdvance(float advance)
{
	this->verticalAdvance = advance;
}

inline float GlyphMetrics::getWidth() const
{
	return width;
}

inline float GlyphMetrics::getHeight() const
{
	return height;
}

inline const Vector2& GlyphMetrics::getHorizontalBearing() const
{
	return horizontalBearing;
}

inline float GlyphMetrics::getHorizontalAdvance() const
{
	return horizontalAdvance;
}

inline const Vector2& GlyphMetrics::getVerticalBearing() const
{
	return verticalBearing;
}

inline float GlyphMetrics::getVerticalAdvance() const
{
	return verticalAdvance;
}

} // namespace Emergent

#endif // EMERGENT_FONT_GLYPH_METRICS_HPP

