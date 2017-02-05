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

#include <emergent/geometry/aabb.hpp>
#include <emergent/geometry/sphere.hpp>
#include <algorithm>

namespace Emergent
{

void AABB::add(const Vector3& v)
{
	min.x = std::min(min.x, v.x);
	min.y = std::min(min.y, v.y);
	min.z = std::min(min.z, v.z);
	max.x = std::max(max.x, v.x);
	max.y = std::max(max.y, v.y);
	max.z = std::max(max.z, v.z);
}

AABB AABB::transformed(const Matrix4& m) const
{
	Vector3 corners[7] =
	{
		Vector3(min.x, min.y, max.z),
		Vector3(min.x, max.y, min.z),
		Vector3(min.x, max.y, max.z),
		Vector3(max.x, min.y, min.z),
		Vector3(max.x, min.y, max.z),
		Vector3(max.x, max.y, min.z),
		max
	};
	
	Vector3 transformedCorner = Vector3(m * Vector4(min, 1.0f));
	AABB result(transformedCorner, transformedCorner);
	for (std::size_t i = 0; i < 7; ++i)
	{
		transformedCorner = Vector3(m * Vector4(corners[i], 1.0f));
		result.add(transformedCorner);
	}
	
	return result;
}

AABB AABB::transformed(const Transform& transform) const
{
	Vector3 corners[7] =
	{
		Vector3(min.x, min.y, max.z),
		Vector3(min.x, max.y, min.z),
		Vector3(min.x, max.y, max.z),
		Vector3(max.x, min.y, min.z),
		Vector3(max.x, min.y, max.z),
		Vector3(max.x, max.y, min.z),
		max
	};
	
	Vector3 transformedCorner = transform.transform(min);
	AABB result(transformedCorner, transformedCorner);
	for (std::size_t i = 0; i < 7; ++i)
	{
		transformedCorner = transform.transform(corners[i]);
		result.add(transformedCorner);
	}
	
	return result;
}

bool AABB::intersects(const Sphere& sphere) const
{
	return AABB(min - sphere.getRadius(), max + sphere.getRadius()).contains(sphere.getCenter());
}

bool AABB::intersects(const AABB& aabb) const
{
	if (max.x < aabb.min.x || min.x > aabb.max.x)
		return false;
	if (max.y < aabb.min.y || min.y > aabb.max.y)
		return false;
	if (max.z < aabb.min.z || min.z > aabb.max.z)
		return false;
	return true;
}

bool AABB::contains(const Vector3& point) const
{
	if (point.x < min.x || point.x > max.x)
		return false;
	if (point.y < min.y || point.y > max.y)
		return false;
	if (point.z < min.z || point.z > max.z)
		return false;
	return true;
}

bool AABB::contains(const Sphere& sphere) const
{
	const Vector3& center = sphere.getCenter();
	float radius = sphere.getRadius();
	
	if (center.x - radius < min.x || center.x + radius > max.x)
		return false;
	if (center.y - radius < min.y || center.y + radius > max.y)
		return false;
	if (center.z - radius < min.z || center.z + radius > max.z)
		return false;
	return true;
}

bool AABB::contains(const AABB& aabb) const
{
	if (aabb.min.x < min.x || aabb.max.x > max.x)
		return false;
	if (aabb.min.y < min.y || aabb.max.y > max.y)
		return false;
	if (aabb.min.z < min.z || aabb.max.z > max.z)
		return false;
	return true;
}

} // namespace Emergent

