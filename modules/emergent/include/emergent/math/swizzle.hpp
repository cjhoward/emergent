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

#include <emergent/math/vector-types.hpp>

namespace Emergent
{

/**
 * Rearranges the elements of an n-dimensional vector to make a 2-dimensional vector.
 *
 * @tparam index0 Index of an element in vector v which will be the first element in the swizzled vector.
 * @tparam index1 Index of an element in vector v which will be the second element in the swizzled vector.
 */
template <std::size_t index0, std::size_t index1, class T, std::size_t N>
vector<T, 2> swizzle(const vector<T, N>& v);

/**
 * Rearranges the elements of an n-dimensional vector to make a 3-dimensional vector.
 *
 * @tparam index0 Index of an element in vector v which will be the first element in the swizzled vector.
 * @tparam index1 Index of an element in vector v which will be the second element in the swizzled vector.
 * @tparam index2 Index of an element in vector v which will be the third element in the swizzled vector.
 */
template <std::size_t index0, std::size_t index1, std::size_t index2, class T, std::size_t N>
vector<T, 3> swizzle(const vector<T, N>& v);

/**
 * Rearranges the elements of an n-dimensional vector to make a 4-dimensional vector.
 *
 * @tparam index0 Index of an element in vector v which will be the first element in the swizzled vector.
 * @tparam index1 Index of an element in vector v which will be the second element in the swizzled vector.
 * @tparam index2 Index of an element in vector v which will be the third element in the swizzled vector.
 * @tparam index3 Index of an element in vector v which will be the fourth element in the swizzled vector.
 */
template <std::size_t index0, std::size_t index1, std::size_t index2, std::size_t index3, class T, std::size_t N>
vector<T, 4> swizzle(const vector<T, N>& v);

template <std::size_t index0, std::size_t index1, class T, std::size_t N>
inline vector<T, 2> swizzle(const vector<T, N>& v)
{
	static_assert(index0 < v.size() && index1 < v.size());
	return { v[index0], v[index1] };
}

template <std::size_t index0, std::size_t index1, std::size_t index2, class T, std::size_t N>
inline vector<T, 3> swizzle(const vector<T, N>& v)
{
	static_assert(index0 < v.size() && index1 < v.size() && index2 < v.size());
	return { v[index0], v[index1], v[index2] };
}

template <std::size_t index0, std::size_t index1, std::size_t index2, std::size_t index3, class T, std::size_t N>
inline vector<T, 4> swizzle(const vector<T, N>& v)
{
	static_assert(index0 < v.size() && index1 < v.size() && index2 < v.size() && index3 < v.size());
	return { v[index0], v[index1], v[index2], v[index3] };
}

} // namespace Emergent

#endif // EMERGENT_MATH_SWIZZLE_HPP

