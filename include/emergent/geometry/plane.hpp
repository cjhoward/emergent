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

#ifndef EMERGENT_GEOMETRY_PLANE_HPP
#define EMERGENT_GEOMETRY_PLANE_HPP

#include <emergent/math/types.hpp>

namespace Emergent
{

/**
 * Three-dimensional plane.
 *
 * @ingroup geometry
 */
class Plane
{
public:
	Plane() = default;
	
	Plane(const Vector3& a, const Vector3& b, const Vector3& c);
	Plane(const Vector3& normal, const Vector3& offset);
	Plane(const Vector4& coefficients);
	
	// Calculates the distance to point v
	float distance(const Vector3& v) const;
	
	void set(const Vector3& a, const Vector3& b, const Vector3& c);
	void set(const Vector3& normal, const Vector3& offset);
	void set(const Vector4& coefficients);
	
	const Vector3& getNormal() const;
	float getDistance() const;
	
	// Calculates the point of intersection between three planes
	static Vector3 intersection(const Plane& p0, const Plane& p1, const Plane& p2);
	
private:
	Vector3 n;
	float d;
};

inline Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c)
{
	set(a, b, c);
}

inline Plane::Plane(const Vector3& normal, const Vector3& offset)
{
	set(normal, offset);
}

inline Plane::Plane(const Vector4& coefficients)
{
	set(coefficients);
}

inline float Plane::distance(const Vector3& v) const
{
	return d + glm::dot(n, v);
}

inline const Vector3& Plane::getNormal() const
{
	return n;
}

inline float Plane::getDistance() const
{
	return d;
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_PLANE_HPP

