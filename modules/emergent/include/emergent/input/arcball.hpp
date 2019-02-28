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

#ifndef EMERGENT_INPUT_ARCBALL_HPP
#define EMERGENT_INPUT_ARCBALL_HPP

#include <emergent/math/types.hpp>

namespace Emergent
{

/**
 * Arcball for manipulating 3D orientations
 *
 * @ingroup input
 */
class Arcball
{
public:
	/**
	 * Projects screen-space coordinates onto the arcball sphere.
	 *
	 * @param screen Screen-space coordinates
	 * @return Projected sphere-space coordinates
	 */
	Vector3 project(const Vector2& screen) const;
	
	/// Sets the center of the arcball
	void setCenter(const Vector2& center);
	
	/// Sets the radius of the arcball
	void setRadius(float radius);
	
	/// Returns the center of the arcball
	const Vector2& getCenter() const;
	
	/// Returns the radius of the arcball
	float getRadius() const;

private:
	Vector2 center;
	float radius;
};

inline void Arcball::setCenter(const Vector2& center)
{
	this->center = center;
}

inline void Arcball::setRadius(float radius)
{
	this->radius = radius;
}

inline const Vector2& Arcball::getCenter() const
{
	return center;
}

inline float Arcball::getRadius() const
{
	return radius;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_ARCBALL_HPP
