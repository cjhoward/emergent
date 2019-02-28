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

#ifndef EMERGENT_FONT_FONT_METRICS_HPP
#define EMERGENT_FONT_FONT_METRICS_HPP

#include <cstdlib>

namespace Emergent
{

/**
 * Contains the metrics of a font.
 *
 * @ingroup font
 */
class FontMetrics
{
public:
	/**
	 * Sets the position of the ascender.
	 *
	 * @param ascender Specifies the ascender.
	 */
	void setAscender(float ascender);

	/**
	 * Sets the position of the descender.
	 *
	 * @param descender Specifies the descender.
	 */
	void setDescender(float descender);

	/**
	 * Sets the height of the font.
	 *
	 * @param height Specifies the font height.
	 */
	void setHeight(float height);

	/**
	 * Sets the maximum advance.
	 *
	 * @param maxAdvance Specifies the maximum advance.
	 */
	void setMaxAdvance(float maxAdvance);

	/**
	 * Sets the distance from the baseline to the underline.
	 *
	 * @param offset Specifies an offset from the baseline.
	 */
	void setUnderlineOffset(float offset);

	/**
	 * Sets the underline weight.
	 *
	 * @param weight Specifies a weight.
	 */
	void setUnderlineWeight(float weight);
	
	/**
	 * Returns the position of the ascender.
	 */
	float getAscender() const;

	/**
	 * Returns the position of the descender.
	 */
	float getDescender() const;

	/**
	 * Returns the height of the font.
	 */
	float getHeight() const;

	/**
	 * Returns the maximum advance.
	 */
	float getMaxAdvance() const;
	
	/**
	 * Returns the distance from the baseline to the underline.
	 */
	float getUnderlineOffset() const;

	/**
	 * Returns the underline weight.
	 */
	float getUnderlineWeight() const;
	
private:
	float ascender;
	float descender;
	float height;
	float maxAdvance;
	float underlineOffset;
	float underlineWeight;
};

inline void FontMetrics::setAscender(float ascender)
{
	this->ascender = ascender;
}

inline void FontMetrics::setDescender(float descender)
{
	this->descender = descender;
}

inline void FontMetrics::setHeight(float height)
{
	this->height = height;
}

inline void FontMetrics::setMaxAdvance(float maxAdvance)
{
	this->maxAdvance = maxAdvance;
}

inline void FontMetrics::setUnderlineOffset(float offset)
{
	this->underlineOffset = offset;
}

inline void FontMetrics::setUnderlineWeight(float weight)
{
	this->underlineWeight = weight;
}

inline float FontMetrics::getAscender() const
{
	return ascender;
}

inline float FontMetrics::getDescender() const
{
	return descender;
}

inline float FontMetrics::getHeight() const
{
	return height;
}

inline float FontMetrics::getMaxAdvance() const
{
	return maxAdvance;
}

inline float FontMetrics::getUnderlineOffset() const
{
	return underlineOffset;
}

inline float FontMetrics::getUnderlineWeight() const
{
	return underlineWeight;
}

} // namespace Emergent

#endif // EMERGENT_FONT_FONT_METRICS_HPP
