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

#include <emergent/geometry/aabb.hpp>
#include <emergent/geometry/sphere.hpp>
#include <algorithm>

namespace Emergent
{

void AABB::add(const Vector3& v)
{
	minPoint.x = std::min(minPoint.x, v.x);
	minPoint.y = std::min(minPoint.y, v.y);
	minPoint.z = std::min(minPoint.z, v.z);
	maxPoint.x = std::max(maxPoint.x, v.x);
	maxPoint.y = std::max(maxPoint.y, v.y);
	maxPoint.z = std::max(maxPoint.z, v.z);
}

AABB AABB::transformed(const Matrix4& m) const
{
	Vector3 corners[7] =
	{
		Vector3(minPoint.x, minPoint.y, maxPoint.z),
		Vector3(minPoint.x, maxPoint.y, minPoint.z),
		Vector3(minPoint.x, maxPoint.y, maxPoint.z),
		Vector3(maxPoint.x, minPoint.y, minPoint.z),
		Vector3(maxPoint.x, minPoint.y, maxPoint.z),
		Vector3(maxPoint.x, maxPoint.y, minPoint.z),
		maxPoint
	};
	
	Vector3 transformedCorner = Vector3(m * Vector4(minPoint, 1.0f));
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
		Vector3(minPoint.x, minPoint.y, maxPoint.z),
		Vector3(minPoint.x, maxPoint.y, minPoint.z),
		Vector3(minPoint.x, maxPoint.y, maxPoint.z),
		Vector3(maxPoint.x, minPoint.y, minPoint.z),
		Vector3(maxPoint.x, minPoint.y, maxPoint.z),
		Vector3(maxPoint.x, maxPoint.y, minPoint.z),
		maxPoint
	};
	
	Vector3 transformedCorner = transform.transform(minPoint);
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
	return AABB(minPoint - sphere.getRadius(), maxPoint + sphere.getRadius()).contains(sphere.getCenter());
}

bool AABB::intersects(const AABB& aabb) const
{
	if (maxPoint.x < aabb.minPoint.x || minPoint.x > aabb.maxPoint.x)
		return false;
	if (maxPoint.y < aabb.minPoint.y || minPoint.y > aabb.maxPoint.y)
		return false;
	if (maxPoint.z < aabb.minPoint.z || minPoint.z > aabb.maxPoint.z)
		return false;
	return true;
}

bool AABB::contains(const Vector3& point) const
{
	if (point.x < minPoint.x || point.x > maxPoint.x)
		return false;
	if (point.y < minPoint.y || point.y > maxPoint.y)
		return false;
	if (point.z < minPoint.z || point.z > maxPoint.z)
		return false;
	return true;
}

bool AABB::contains(const Sphere& sphere) const
{
	const Vector3& center = sphere.getCenter();
	float radius = sphere.getRadius();
	
	if (center.x - radius < minPoint.x || center.x + radius > maxPoint.x)
		return false;
	if (center.y - radius < minPoint.y || center.y + radius > maxPoint.y)
		return false;
	if (center.z - radius < minPoint.z || center.z + radius > maxPoint.z)
		return false;
	return true;
}

bool AABB::contains(const AABB& aabb) const
{
	if (aabb.minPoint.x < minPoint.x || aabb.maxPoint.x > maxPoint.x)
		return false;
	if (aabb.minPoint.y < minPoint.y || aabb.maxPoint.y > maxPoint.y)
		return false;
	if (aabb.minPoint.z < minPoint.z || aabb.maxPoint.z > maxPoint.z)
		return false;
	return true;
}

} // namespace Emergent

