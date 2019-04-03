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

#ifndef EMERGENT_MATH_SWIZZLE_HPP
#define EMERGENT_MATH_SWIZZLE_HPP

#include <emergent/math/vector-type.hpp>

namespace Emergent
{

/**
 * Makes an m-dimensional vector by rearranging and/or duplicating elements of an n-dimensional vector.
 *
 * @tparam Indices List of indices of elements in the vector `v`.
 * @tparam T Vector component type.
 * @tparam N Number of dimensions in vector `v`.
 * @return Vector containing elements from vector `v` in the order specified by `Indices`. The size of the returned vector is equivalent to the number of indices in `Indices`.
 */
template <std::size_t... Indices, class T, std::size_t N>
vector<T, sizeof...(Indices)> swizzle(const vector<T, N>& v);

template <std::size_t... Indices, class T, std::size_t N>
inline vector<T, sizeof...(Indices)> swizzle(const vector<T, N>& v)
{
	return { v[Indices]... };
}

} // namespace Emergent

#endif // EMERGENT_MATH_SWIZZLE_HPP

