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

#ifndef EMERGENT_MATH_QUATERNION_VECTOR_OPERATIONS_HPP
#define EMERGENT_MATH_QUATERNION_VECTOR_OPERATIONS_HPP

#include <emergent/math/quaternion-type.hpp>
#include <emergent/math/vector-operations.hpp>
#include <emergent/math/vector-type.hpp>
#include <type_traits>

namespace Emergent
{

/**
 * Rotates a 3-dimensional vector by a quaternion.
 *
 * @param q Unit quaternion.
 * @param v Vector.
 * @return Rotated vector.
 */
///@{
template <class T>
vector<T, 3> mul(const quaternion<T>& q, const vector<T, 3>& v);
template <class T>
vector<T, 3> operator*(const quaternion<T>& q, const vector<T, 3>& v);
///@}

template <class T>
vector<T, 3> mul(const quaternion<T>& q, const vector<T, 3>& v)
{
	const T r = std::get<0>(q);             // Real part
	const vector<T, 3>& i = std::get<1>(q); // Imaginary part
	return i * dot(i, v) * T(2) + v * (r * r - dot(i, i)) + cross(i, v) * r * T(2);
}

template <class T>
inline vector<T, 3> operator*(const quaternion<T>& q, const vector<T, 3>& v)
{
	return mul(q, v);
}

} // namespace Emergent

#endif // EMERGENT_MATH_QUATERNION_VECTOR_OPERATIONS_HPP

