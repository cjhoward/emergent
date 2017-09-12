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

#ifndef EMERGENT_GEOMETRY_AABB_HPP
#define EMERGENT_GEOMETRY_AABB_HPP

#include <emergent/geometry/bounding-volume.hpp>
#include <emergent/math/types.hpp>

namespace Emergent
{

class Sphere;

/**
 * Axis-aligned bounding box.
 *
 * @ingroup geometry
 */
class AABB: public BoundingVolume
{
public:
	AABB() = default;
	
	AABB(const Vector3& minPoint, const Vector3& maxPoint);
	
	void setMin(const Vector3& minPoint);
	void setMax(const Vector3& maxPoint);
	
	const Vector3& getMin() const;
	const Vector3& getMax() const;
	
	void add(const Vector3& v);
	
	AABB transformed(const Matrix4& m) const;
	AABB transformed(const Transform& transform) const;
	
	virtual BoundingVolume::Type getType() const;
	virtual bool intersects(const Sphere& sphere) const;
	virtual bool intersects(const AABB& aabb) const;
	virtual bool contains(const Vector3& point) const;
	virtual bool contains(const Sphere& sphere) const;
	virtual bool contains(const AABB& aabb) const;
	
private:
	Vector3 minPoint;
	Vector3 maxPoint;
};

inline AABB::AABB(const Vector3& minPoint, const Vector3& maxPoint):
	minPoint(minPoint),
	maxPoint(maxPoint)
{}

inline void AABB::setMin(const Vector3& minPoint)
{
	this->minPoint = minPoint;
}

inline void AABB::setMax(const Vector3& maxPoint)
{
	this->maxPoint = maxPoint;
}

inline const Vector3& AABB::getMin() const
{
	return minPoint;
}

inline const Vector3& AABB::getMax() const
{
	return maxPoint;
}

inline BoundingVolume::Type AABB::getType() const
{
	return BoundingVolume::Type::AABB;
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_AABB_HPP

