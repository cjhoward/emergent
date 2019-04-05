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

#ifndef EMERGENT_MATH_MATRIX_VECTOR_OPERATIONS_HPP
#define EMERGENT_MATH_MATRIX_VECTOR_OPERATIONS_HPP

#include <emergent/math/matrix-type.hpp>
#include <emergent/math/vector-type.hpp>
#include <type_traits>

namespace Emergent
{

/**
 * Transforms a vector by a matrix.
 *
 * @param m Matrix.
 * @param v Vector.
 * @return Transformed vector.
 */
///@{
template <class T>
vector<T, 2> mul(const matrix<T, 2, 2>& m, const vector<T, 2>& v);
template <class T>
vector<T, 3> mul(const matrix<T, 3, 3>& m, const vector<T, 3>& v);
template <class T>
vector<T, 4> mul(const matrix<T, 4, 4>& m, const vector<T, 4>& v);
template <class T, std::size_t N>
vector<T, N> operator*(const matrix<T, N, N>& m, const vector<T, N>& v);
///@}

template <class T>
vector<T, 2> mul(const matrix<T, 2, 2>& m, const vector<T, 2>& v)
{
	return
		{{
			{m[0][0] * v[0] + m[1][0] * v[1]},
			{m[0][1] * v[0] + m[1][1] * v[1]}
		}};
}

template <class T>
vector<T, 3> mul(const matrix<T, 3, 3>& m, const vector<T, 3>& v)
{
	return
		{{
			{m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2]},
			{m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2]},
			{m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2]}
		}};
}

template <class T>
vector<T, 4> mul(const matrix<T, 4, 4>& m, const vector<T, 4>& v)
{
	return
		{{
			{m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3]},
			{m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3]},
			{m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3]},
			{m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]}
		}};
}

template <class T, std::size_t N>
inline vector<T, N> operator*(const matrix<T, N, N>& m, const vector<T, N>& v)
{
	return mul(m, v);
}

} // namespace Emergent

#endif // EMERGENT_MATH_MATRIX_VECTOR_OPERATIONS_HPP

