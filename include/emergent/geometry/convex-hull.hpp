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

#ifndef EMERGENT_GEOMETRY_CONVEX_HULL_HPP
#define EMERGENT_GEOMETRY_CONVEX_HULL_HPP

#include <emergent/geometry/bounding-volume.hpp>
#include <emergent/geometry/plane.hpp>
#include <cstdlib>

namespace Emergent
{

class Sphere;
class AABB;

/**
 * Convex hull defined by a collection of planes
 *
 * @ingroup geometry
 */
class ConvexHull: public BoundingVolume
{
public:
	explicit ConvexHull(std::size_t planeCount);
	~ConvexHull();
	
	void setPlane(std::size_t index, const Plane& plane);
	
	std::size_t getPlaneCount() const;
	const Plane& getPlane(std::size_t index) const;
	
	virtual BoundingVolume::Type getType() const;
	virtual bool intersects(const Sphere& sphere) const;
	virtual bool intersects(const AABB& aabb) const;
	virtual bool contains(const Vector3& point) const;
	virtual bool contains(const Sphere& sphere) const;
	virtual bool contains(const AABB& aabb) const;
	
private:
	Plane* planes;
	std::size_t planeCount;
};

inline void ConvexHull::setPlane(std::size_t index, const Plane& plane)
{
	planes[index] = plane;
}

inline std::size_t ConvexHull::getPlaneCount() const
{
	return planeCount;
}

inline const Plane& ConvexHull::getPlane(std::size_t index) const
{
	return planes[index];
}

inline BoundingVolume::Type ConvexHull::getType() const
{
	return BoundingVolume::Type::CONVEX_HULL;
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_CONVEX_HULL_HPP

