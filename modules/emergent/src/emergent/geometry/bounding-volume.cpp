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

#include <emergent/geometry/bounding-volume.hpp>
#include <emergent/geometry/aabb.hpp>
#include <emergent/geometry/sphere.hpp>
#include <emergent/geometry/convex-hull.hpp>
#include <stdexcept>

namespace Emergent
{

bool BoundingVolume::intersects(const BoundingVolume& volume) const
{
	BoundingVolume::Type type = volume.getType();
	switch (type)
	{
		case BoundingVolume::Type::AABB:
			return intersects(static_cast<const AABB&>(volume));
			break;

		case BoundingVolume::Type::SPHERE:
			return intersects(static_cast<const Sphere&>(volume));
			break;

		default:
			throw std::runtime_error("unimplemented");
			break;
	}
}

} // namespace Emergent

