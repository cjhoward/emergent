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

#include <emergent/geometry/ray.hpp>
#include <emergent/geometry/plane.hpp>
#include <emergent/geometry/sphere.hpp>
#include <emergent/geometry/aabb.hpp>
#include <emergent/geometry/convex-hull.hpp>
#include <emergent/geometry/bounding-volume.hpp>
#include <emergent/geometry/triangle-mesh.hpp>
#include <algorithm>
#include <cmath>
#include <limits>

namespace Emergent
{

std::tuple<bool, float> Ray::intersects(const Plane& plane) const
{
	float denom = glm::dot(direction, plane.getNormal());
	if (denom != 0.0f)
	{
		float t = -(glm::dot(origin, plane.getNormal()) + plane.getDistance()) / denom;
		
		if (t >= 0.0f)
		{
			return std::make_tuple(true, t);
		}
	}
	
	return std::make_tuple(false, std::numeric_limits<float>::infinity());
}

std::tuple<bool, float, float> Ray::intersects(const Sphere& sphere) const
{
	Vector3 p = sphere.getCenter() - origin;
	float b = glm::dot(p, direction);
	float c = glm::dot(p, p) - sphere.getRadius() * sphere.getRadius();
	float d = b * b - c;
	
	if (d < 0.0f)
	{
		return std::make_tuple(false, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	}	
	
	d = std::sqrt(d);
	
	float t0 = b - d;
	float t1 = b + d;
	
	if (t0 >= 0.0f || t1 >= 0.0f)
	{
		return std::make_tuple(true, t0, t1);
	}
	
	return std::make_tuple(false, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
}

std::tuple<bool, float, float> Ray::intersects(const AABB& aabb) const
{
	float t0 = -std::numeric_limits<float>::infinity();
	float t1 = std::numeric_limits<float>::infinity();
	
	for (std::size_t i = 0; i < 3; ++i)
	{
		if (direction[i] == 0.0f)
		{
			if (origin[i] < aabb.getMin()[i] || origin[i] > aabb.getMax()[i])
			{
				return std::make_tuple(false, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());	
			}
		}
		else
		{
			float tmin = (aabb.getMin()[i] - origin[i]) / direction[i];
			float tmax = (aabb.getMax()[i] - origin[i]) / direction[i];
			
			t0 = std::max(t0, std::min(tmin, tmax));
			t1 = std::min(t1, std::max(tmin, tmax));
		}
	}
	
	if (t0 > t1 || t1 < 0.0f)
	{
		return std::make_tuple(false, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	}
	
	return std::make_tuple(true, t0, t1);
}

std::tuple<bool, float, float> Ray::intersects(const ConvexHull& hull) const
{
	float t0 = -std::numeric_limits<float>::infinity();
	float t1 = std::numeric_limits<float>::infinity();
	
	for (std::size_t i = 0; i < hull.getPlaneCount(); ++i)
	{
		const Plane& plane = hull.getPlane(i);
		
		float denom = glm::dot(direction, plane.getNormal());	
		float t = -(glm::dot(origin, plane.getNormal()) + plane.getDistance()) / denom;
		
		if (denom >= 0.0f)
		{
			t0 = std::max(t0, t);
		}
		else
		{
			t1 = std::min(t1, t);
		}
	}
	
	if (t0 > t1 || t1 < 0.0f)
	{
		return std::make_tuple(false, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	}
	
	return std::make_tuple(true, t0, t1);
}

std::tuple<bool, float, float> Ray::intersects(const BoundingVolume& bv) const
{
	switch (bv.getType())
	{
		case BoundingVolume::Type::SPHERE:
			return intersects(static_cast<const Sphere&>(bv));
			break;
		
		case BoundingVolume::Type::AABB:
			return intersects(static_cast<const AABB&>(bv));
			break;
		
		case BoundingVolume::Type::CONVEX_HULL:
			return intersects(static_cast<const ConvexHull&>(bv));
			break;
		
		default:
			break;
	}
	
	return std::make_tuple(false, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
}

std::tuple<bool, float, float, float> Ray::intersects(const Vector3& a, const Vector3& b, const Vector3& c) const
{
	// Find edges
	Vector3 edge10 = b - a;
	Vector3 edge20 = c - a;

	// Calculate determinant
	Vector3 pv = glm::cross(direction, edge20);
	float det = glm::dot(edge10, pv);

	if (!det)
	{
		return std::make_tuple(false, std::numeric_limits<float>::infinity(), 0.0f, 0.0f);
	}

	float inverseDet = 1.0f / det;

	// Calculate u
	Vector3 tv = origin - a;
	float u = glm::dot(tv, pv) * inverseDet;
	
	if (u < 0.0f || u > 1.0f)
	{
		return std::make_tuple(false, std::numeric_limits<float>::infinity(), 0.0f, 0.0f);
	}

	// Calculate v
	Vector3 qv = glm::cross(tv, edge10);
	float v = glm::dot(direction, qv) * inverseDet;

	if (v < 0.0f || u + v > 1.0f)
	{
		return std::make_tuple(false, std::numeric_limits<float>::infinity(), 0.0f, 0.0f);
	}

	// Calculate t
	float t = glm::dot(edge20, qv) * inverseDet;

	if (t > 0.0f)
	{
		return std::make_tuple(true, t, u, v);
	}

	return std::make_tuple(false, std::numeric_limits<float>::infinity(), 0.0f, 0.0f);
}

std::tuple<bool, float, float, std::size_t, std::size_t> Ray::intersects(const TriangleMesh& mesh) const
{
	const std::vector<TriangleMesh::Triangle*>& triangles = *mesh.getTriangles();
	
	bool intersection = false;
	float t0 = std::numeric_limits<float>::infinity();
	float t1 = -std::numeric_limits<float>::infinity();
	std::size_t index0 = triangles.size();
	std::size_t index1 = triangles.size();

	for (std::size_t i = 0; i < triangles.size(); ++i)
	{
		const TriangleMesh::Triangle* triangle = triangles[i];
		const Vector3& a = triangle->edge->vertex->position;
		const Vector3& b = triangle->edge->next->vertex->position;
		const Vector3& c = triangle->edge->previous->vertex->position;
		
		auto result = intersects(a, b, c);
		
		if (std::get<0>(result))
		{
			intersection = true;

			float t = std::get<1>(result);
			float cosTheta = glm::dot(direction, triangle->normal);	

			if (cosTheta <= 0.0f)
			{
				// Front-facing
				t0 = std::min(t0, t);
				index0 = i;
			}
			else
			{
				// Back-facing
				t1 = std::max(t1, t);
				index1 = i;
			}
		}
	}

	return std::make_tuple(intersection, t0, t1, index0, index1);
}

} // namespace Emergent
