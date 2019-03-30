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

#ifndef EMERGENT_MATH_ANGLES_HPP
#define EMERGENT_MATH_ANGLES_HPP

#include <emergent/math/constants.hpp>

namespace Emergent
{

/**
 * Converts radians to degrees.
 *
 * @param radians Angle in radians.
 * @return Angle in degrees.
 */
template <class T>
T degrees(T radians);

/**
 * Converts degrees to radians.
 *
 * @param degrees Angle in degrees.
 * @return Angle in radians.
 */
template <class T>
T radians(T degrees);

template <class T>
inline T degrees(T radians)
{
	return radians * (T(180) / pi<T>);
}

template <class T>
inline T radians(T degrees)
{
	return degrees * (pi<T> / T(180));
}

} // namespace Emergent

#endif // EMERGENT_MATH_ANGLES_HPP
