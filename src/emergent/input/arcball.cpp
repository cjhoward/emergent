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

#include <emergent/input/arcball.hpp>

namespace Emergent
{

Vector3 Arcball::project(const Vector2& screen) const
{
	Vector3 point;
	
	point.x = (screen.x - center.x) / radius;
	point.y = (screen.y - center.y) / radius;
	
	float distanceSquared = point.x * point.x + point.y * point.y;
	if (distanceSquared > 1.0f)
	{
		// Projected point is outside of radius, constrain it
		float inverseDistance = 1.0f / std::sqrt(distanceSquared);
		point.x *= inverseDistance;
		point.y *= inverseDistance;
		point.z = 0.0f;
	}
	else
	{
		point.z = std::sqrt(1.0f - distanceSquared);
	}
	
	return point;
}

} // namespace Emergent
