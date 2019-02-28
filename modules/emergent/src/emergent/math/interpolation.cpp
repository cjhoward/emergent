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

#include <emergent/math/interpolation.hpp>
#include <emergent/geometry/aabb.hpp>
#include <emergent/math/transform.hpp>

namespace Emergent
{

template <>
AABB lerp<AABB>(const AABB& x, const AABB& y, float a)
{
	AABB result;
	result.setMin(lerp<Vector3>(x.getMin(), y.getMin(), a));
	result.setMax(lerp<Vector3>(x.getMax(), y.getMax(), a));
	return result;
}

template <>
Transform lerp<Transform>(const Transform& x, const Transform& y, float a)
{
	Transform result;
	result.translation = lerp<Vector3>(x.translation, y.translation, a);
	result.rotation = glm::slerp(x.rotation, y.rotation, a);
	result.scale = lerp<Vector3>(x.scale, y.scale, a);
	return result;
}

} // namespace Emergent


