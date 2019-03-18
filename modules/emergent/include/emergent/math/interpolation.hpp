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

#ifndef EMERGENT_MATH_INTERPOLATION_HPP
#define EMERGENT_MATH_INTERPOLATION_HPP

#include <emergent/math/constants.hpp>
#include <emergent/math/math.hpp>
#include <cmath>

namespace Emergent
{

class AABB;
class Transform;

/**
 * Linearly interpolates between two variables.
 *
 * @param x Start of the interpolation range.
 * @param y End of the interpolation range.
 * @param a Interpolation ratio.
 *
 * @ingroup math
 */
template <typename T>
inline T lerp(const T& x, const T& y, float a)
{
	return x * (1.0f - a) + y * a;
}

template <>
AABB lerp<AABB>(const AABB& x, const AABB& y, float a);

template <>
Transform lerp<Transform>(const Transform& x, const Transform& y, float a);

template <typename T>
T slerp(const T& x, const T& y, float a)
{
	return glm::slerp(x, y, a);
}

template <typename T>
inline T coserp(const T& x, const T& y, float a)
{
	return lerp<T>(x, y, 1.0f - static_cast<float>(std::cos(static_cast<double>(a) * halfPi<double>)));
}

template <typename T>
inline T sinerp(const T& x, const T& y, float a)
{
	return lerp<T>(x, y, static_cast<float>(std::sin(static_cast<double>(a) * halfPi<double>)));
}

template <typename T>
inline T hermite(const T& x, const T& y, float a)
{
	return lerp<T>(x, y, a * a * (3.0f - 2.0f * a));
}

} // namespace Emergent

#endif // EMERGENT_MATH_INTERPOLATION_HPP

