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

#include <emergent/geometry/sphere.hpp>
#include <emergent/geometry/aabb.hpp>
#include <algorithm>

namespace Emergent
{

bool Sphere::intersects(const Sphere& sphere) const
{
	Vector3 d = center - sphere.center;
	float r = radius + sphere.radius;
	return (glm::dot(d, d) <= r * r);
}

bool Sphere::intersects(const AABB& aabb) const
{
	return aabb.intersects(*this);
}

bool Sphere::contains(const Vector3& point) const
{
	Vector3 d = center - point;
	return (glm::dot(d, d) <= radius * radius);
}

bool Sphere::contains(const Sphere& sphere) const
{
	float containmentRadius = radius - sphere.radius;
	if (containmentRadius < 0.0f)
		return false;
	
	Vector3 d = center - sphere.center;
	return (glm::dot(d, d) <= containmentRadius * containmentRadius);
}

bool Sphere::contains(const AABB& aabb) const
{
	float distance = 0.0f;
	
	Vector3 a = center - aabb.getMin();
	Vector3 b = center - aabb.getMax();
	
	distance += std::max(a.x * a.x, b.x * b.x);
	distance += std::max(a.y * a.y, b.y * b.y);
	distance += std::max(a.z * a.z, b.z * b.z);
	
	return (distance <= radius * radius);
}

} // namespace Emergent
