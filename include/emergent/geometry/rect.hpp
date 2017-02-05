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

#ifndef EMERGENT_GEOMETRY_RECT_HPP
#define EMERGENT_GEOMETRY_RECT_HPP

#include <emergent/math/types.hpp>

namespace Emergent
{

/**
 * 2D rectangle
 *
 * @ingroup geometry
 */
class Rect
{
public:
	Rect() = default;
	
	Rect(const Vector2& min, const Vector2& max);
	
	void setMin(const Vector2& min);
	void setMax(const Vector2& max);
	
	const Vector2& getMin() const;
	const Vector2& getMax() const;
	
	bool intersects(const Rect& rect) const;
	bool contains(const Vector2& point) const;
	bool contains(const Rect& rect) const;
	
private:
	Vector2 min;
	Vector2 max;
};

inline Rect::Rect(const Vector2& min, const Vector2& max):
	min(min),
	max(max)
{}

inline void Rect::setMin(const Vector2& min)
{
	this->min = min;
}

inline void Rect::setMax(const Vector2& max)
{
	this->max = max;
}

inline const Vector2& Rect::getMin() const
{
	return min;
}

inline const Vector2& Rect::getMax() const
{
	return max;
}

inline bool Rect::intersects(const Rect& rect) const
{
	if (max.x < rect.min.x || min.x > rect.max.x)
		return false;
	if (max.y < rect.min.y || min.y > rect.max.y)
		return false;
	return true;
}

inline bool Rect::contains(const Vector2& point) const
{
	if (point.x < min.x || point.x > max.x)
		return false;
	if (point.y < min.y || point.y > max.y)
		return false;
	return true;
}

inline bool Rect::contains(const Rect& rect) const
{
	if (rect.min.x < min.x || rect.max.x > max.x)
		return false;
	if (rect.min.y < min.y || rect.max.y > max.y)
		return false;
	return true;
}


} // namespace Emergent

#endif // EMERGENT_GEOMETRY_RECT_HPP

