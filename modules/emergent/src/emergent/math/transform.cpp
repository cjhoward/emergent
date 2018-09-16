/*
 * Copyright (C) 2017-2018  Christopher J. Howard
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

#include <emergent/math/transform.hpp>
#include <emergent/math/interpolation.hpp>
#include <emergent/math/glm.hpp>

namespace Emergent
{

Transform Transform::inverse() const
{
	Transform result;
	
	result.scale = 1.0f / scale;
	result.rotation = glm::conjugate(rotation);
	result.translation = -(result.rotation * translation);
	
	return result;
}

Vector3 Transform::transform(const Vector3& v) const
{
	return translation + (rotation * (v * scale));
}

Transform Transform::transform(const Transform& other) const
{
	Transform result;
	result.translation = transform(other.translation);
	result.rotation = glm::normalize(rotation * other.rotation);
	result.scale = scale * other.scale;
	return result;
}

Matrix4 Transform::toMatrix() const
{
	Matrix4 result = glm::mat4_cast(rotation);
	result[3] = Vector4(translation, 1.0f);
	return result * glm::scale(scale);
}

} // namespace Emergent

