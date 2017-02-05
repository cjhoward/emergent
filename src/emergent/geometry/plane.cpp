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

#include <emergent/geometry/plane.hpp>

namespace Emergent
{

void Plane::set(const Vector3& a, const Vector3& b, const Vector3& c)
{
	n = glm::normalize(glm::cross(c - b, a - b));
	d = -(glm::dot(n, b));
}

void Plane::set(const Vector3& normal, const Vector3& offset)
{
	n = normal;
	d = -glm::dot(n, offset);
}

void Plane::set(const Vector4& coefficients)
{
	Vector3 normal(coefficients);
	float distance = coefficients.w;
	
	float inverseLength = 1.0f / glm::length(normal);
	n = normal * inverseLength;
	d = distance * inverseLength;
}

Vector3 Plane::intersection(const Plane& p0, const Plane& p1, const Plane& p2)
{
	return -(p0.d * glm::cross(p1.n, p2.n) + p1.d * glm::cross(p2.n, p0.n) + p2.d * glm::cross(p0.n, p1.n)) / glm::dot(p0.n, glm::cross(p1.n, p2.n));
}

} // namespace Emergent

