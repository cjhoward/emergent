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

#ifndef EMERGENT_GEOMETRY_BOUNDING_VOLUME_HPP
#define EMERGENT_GEOMETRY_BOUNDING_VOLUME_HPP

#include <emergent/math/types.hpp>
#include <stdexcept>

namespace Emergent
{

class Sphere;
class AABB;
class ConvexHull;

/**
 * Abstract base class for bounding volumes.
 *
 * @ingroup geometry
 */
class BoundingVolume
{
public:
	enum class Type
	{
		SPHERE,
		AABB,
		CONVEX_HULL
	};
	
	virtual BoundingVolume::Type getType() const = 0;
	virtual bool intersects(const Sphere& sphere) const = 0;
	virtual bool intersects(const AABB& aabb) const = 0;
	virtual bool contains(const Sphere& sphere) const = 0;
	virtual bool contains(const AABB& aabb) const = 0;
	virtual bool contains(const Vector3& point) const = 0;

	bool intersects(const BoundingVolume& volume) const;
};

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_BOUNDING_VOLUME_HPP

