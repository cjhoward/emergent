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

#ifndef EMERGENT_GEOMETRY_RAY_HPP
#define EMERGENT_GEOMETRY_RAY_HPP

#include <emergent/math/types.hpp>
#include <tuple>

namespace Emergent
{

class Plane;
class Sphere;
class AABB;
class ConvexHull;
class BoundingVolume;
class TriangleMesh;

/**
 * A 3D ray.
 *
 * @ingroup geometry
 */
struct Ray
{
public:
	/**
	 * Calculates a position on the ray.
	 *
	 * @param t Distance from the ray origin
	 * @return Extrapolated position
	 */
	Vector3 extrapolate(float t) const;
	
	/**
	 * Checks for intersection between this ray and a plane.
	 *
	 * @param plane Plane with which to check for intersection.
	 * @return The first element in the tuple indicates whether or not an intersection occurred, the second element indicates the distance from the origin to point of intersection.
	 */
	std::tuple<bool, float> intersects(const Plane& plane) const;
	
	/**
	 * Checks for intersection between this ray and a sphere.
	 *
	 * @param sphere Sphere with which to check for intersection.
	 * @return The first element in the tuple indicates whether or not an intersection occurred, the second and third elements indicate the distance from the origin to the nearest and farthest points of intersection, respectively.
	 */
	std::tuple<bool, float, float> intersects(const Sphere& sphere) const;
	
	/**
	 * Checks for intersection between this ray and an AABB.
	 *
	 * @param aabb AABB with which to check for intersection.
	 * @return The first element in the tuple indicates whether or not an intersection occurred, the second and third elements indicate the distance from the origin to the nearest and farthest points of intersection, respectively.
	 */
	std::tuple<bool, float, float> intersects(const AABB& aabb) const;
	
	/**
	 * Checks for intersection between this ray and a convex hull.
	 *
	 * @param hull Convex hull with which to check for intersection.
	 * @return The first element in the tuple indicates whether or not an intersection occurred, the second and third elements indicate the distance from the origin to the nearest and farthest points of intersection, respectively.
	 */
	std::tuple<bool, float, float> intersects(const ConvexHull& hull) const;
	
	/**
	 * Checks for intersection between this ray and a bounding volume.
	 *
	 * @param bv Bounding volume with which to check for intersection.
	 * @return The first element in the tuple indicates whether or not an intersection occurred, the second and third elements indicate the distance from the origin to the nearest and farthest points of intersection, respectively.
	 */
	std::tuple<bool, float, float> intersects(const BoundingVolume& bv) const;
	
	/**
	 * Checks for intersection between this ray and a triangle.
	 *
	 * @param a First vertex in the triangle.
	 * @param b Second vertex in the triangle.
	 * @param c Third vertex in the triangle.
	 * @return The first element in the tuple indicates whether or not an intersection occurred. The second element indicates the distance from the origin to point of intersection. The third element is the barycentric U coordinate. The fourth element is the barycentric V coordinate.
	 *
	 * @see http://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
	 * @see http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/
	 */
	std::tuple<bool, float, float, float> intersects(const Vector3& a, const Vector3& b, const Vector3& c) const;
	
	/**
	 * Checks for intersection between this ray and a triangle mesh.
	 *
	 * @param mesh Mesh with which to check for intersection.
	 * @return The first element in the tuple indicates whether or not an intersection occurred. The second and third elements indicate the distance from the origin to the nearest and farthest points of intersection, respectively. The fourth and fifth elements contain the indices of the nearest and farthest intersected triangles, respectively.
	 */
	std::tuple<bool, float, float, std::size_t, std::size_t> intersects(const TriangleMesh& mesh) const;
	
	/// Origin of the ray
	Vector3 origin;
	
	/// Normalized direction of the ray
	Vector3 direction;
};

inline Vector3 Ray::extrapolate(float t) const
{
	return origin + direction * t;
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_RAY_HPP
