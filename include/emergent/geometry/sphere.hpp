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

#ifndef EMERGENT_GEOMETRY_SPHERE_HPP
#define EMERGENT_GEOMETRY_SPHERE_HPP

#include <emergent/geometry/bounding-volume.hpp>
#include <emergent/math/types.hpp>

namespace Emergent
{

class AABB;

/**
 * Bounding sphere.
 *
 * @ingroup geometry
 */
class Sphere: public BoundingVolume
{
public:
	Sphere() = default;
	Sphere(const Vector3& center, float radius);
	
	void setCenter(const Vector3& center);
	void setRadius(float radius);
	
	const Vector3& getCenter() const;
	float getRadius() const;
	
	virtual BoundingVolume::Type getType() const;
	virtual bool intersects(const Sphere& sphere) const;
	virtual bool intersects(const AABB& aabb) const;
	virtual bool contains(const Vector3& point) const;
	virtual bool contains(const Sphere& sphere) const;
	virtual bool contains(const AABB& aabb) const;
	
private:
	Vector3 center;
	float radius;
};

inline Sphere::Sphere(const Vector3& center, float radius):
	center(center),
	radius(radius)
{}

inline void Sphere::setCenter(const Vector3& center)
{
	this->center = center;
}

inline void Sphere::setRadius(float radius)
{
	this->radius = radius;
}

inline const Vector3& Sphere::getCenter() const
{
	return center;
}

inline float Sphere::getRadius() const
{
	return radius;
}

inline BoundingVolume::Type Sphere::getType() const
{
	return BoundingVolume::Type::SPHERE;
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_SPHERE_HPP

