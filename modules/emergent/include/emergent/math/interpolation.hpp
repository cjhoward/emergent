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

#ifndef EMERGENT_MATH_INTERPOLATION_HPP
#define EMERGENT_MATH_INTERPOLATION_HPP

namespace Emergent
{

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

} // namespace Emergent

#endif // EMERGENT_MATH_INTERPOLATION_HPP

