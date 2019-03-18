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

#ifndef EMERGENT_MATH_CONSTANTS_HPP
#define EMERGENT_MATH_CONSTANTS_HPP

#include <emergent/math/matrix-types.hpp>

namespace Emergent
{

/**
 * 1x1 identity matrix.
 */
template <class T>
constexpr matrix<T, 1, 1> identity1x1 = {{{1}}};

/**
 * 2x2 identity matrix.
 */
template <class T>
constexpr matrix<T, 2, 2> identity2x2 =
{{
	{1, 0},
	{0, 1}
}};

/**
 * 3x3 identity matrix.
 */
template <class T>
constexpr matrix<T, 3, 3> identity3x3 =
{{
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
}};

/**
 * 4x4 identity matrix.
 */
template <class T>
constexpr matrix<T, 4, 4> identity4x4 =
{{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
}};

/**
 * Pi
 */
template <class T>
constexpr T pi = T(3.1415926535897932385L);

/**
 * Pi * 2
 */
template <class T>
constexpr T twoPi = pi<T> * T(2);

/**
 * Pi / 2
 */
template <typename T>
constexpr T halfPi = pi<T> * (0.5);

} // namespace Emergent

#endif // EMERGENT_MATH_CONSTANTS_HPP

