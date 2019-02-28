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

#ifndef EMERGENT_MATH_TYPES_HPP
#define EMERGENT_MATH_TYPES_HPP

#include <emergent/math/glm.hpp>

namespace Emergent
{

/// Two-dimensional floating-point vector
/// @ingroup math
typedef glm::vec2 Vector2;

/// Three-dimensional floating-point vector
/// @ingroup math
typedef glm::vec3 Vector3;

/// Four-dimensional floating-point vector
/// @ingroup math
typedef glm::vec4 Vector4;

/// 2x2 floating-point matrix
/// @ingroup math
typedef glm::mat2 Matrix2;

/// 3x3 floating-point matrix
/// @ingroup math
typedef glm::mat3 Matrix3;

/// 4x4 floating-point matrix
/// @ingroup math
typedef glm::mat4 Matrix4;

/// Floating-point quaternion
typedef glm::quat Quaternion;
/// @ingroup math

} // namespace Emergent

#include <emergent/math/transform.hpp>

#endif // EMERGENT_MATH_TYPES_HPP
