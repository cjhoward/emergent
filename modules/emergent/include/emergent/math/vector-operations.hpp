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

#ifndef EMERGENT_MATH_VECTOR_OPERATIONS_HPP
#define EMERGENT_MATH_VECTOR_OPERATIONS_HPP

#include <emergent/math/vector-type.hpp>
#include <cmath>
#include <ostream>
#include <type_traits>

namespace Emergent
{

/**
 * Adds two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Sum of the two vectors.
 */
///@{
template <class T>
vector<T, 2> add(const vector<T, 2>& x, const vector<T, 2>& y);
template <class T>
vector<T, 3> add(const vector<T, 3>& x, const vector<T, 3>& y);
template <class T>
vector<T, 4> add(const vector<T, 4>& x, const vector<T, 4>& y);
///@}

/**
 * Calculate the cross product of two vectors.
 *
 * @param x First of two vectors.
 * @param y Second of two vectors.
 */
template <class T>
vector<T, 3> cross(const vector<T, 3>& x, const vector<T, 3>& y);

/**
 * Calculates the distance between two points.
 *
 * @param p0 First of two points.
 * @param p1 Second of two points.
 */
template <class T, std::size_t N>
vector<T, N> distance(const vector<T, N>& p0, const vector<T, N>& p1);

/**
 * Calculates the squared distance between two points.
 *
 * @param p0 First of two points.
 * @param p1 Second of two points.
 */
template <class T, std::size_t N>
vector<T, N> distance_squared(const vector<T, N>& p0, const vector<T, N>& p1);

/**
 * Divides a vector by another vector.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return 
 */
///@{
template <class T>
vector<T, 2> div(const vector<T, 2>& x, const vector<T, 2>& y);
template <class T>
vector<T, 3> div(const vector<T, 3>& x, const vector<T, 3>& y);
template <class T>
vector<T, 4> div(const vector<T, 4>& x, const vector<T, 4>& y);
///@}

/**
 *
 */
///@{
template <class T>
vector<T, 2> div(const vector<T, 2>& v, T s);
template <class T>
vector<T, 3> div(const vector<T, 3>& v, T s);
template <class T>
vector<T, 4> div(const vector<T, 4>& v, T s);
///@}

/**
 * Calculates the dot product of two vectors.
 *
 * @param x First of two vectors.
 * @param y Second of two vectors.
 */
///@{
template <class T>
T dot(const vector<T, 2>& x, const vector<T, 2>& y);
template <class T>
T dot(const vector<T, 3>& x, const vector<T, 3>& y);
template <class T>
T dot(const vector<T, 4>& x, const vector<T, 4>& y);
///@}

/**
 * Calculates the length of a vector.
 *
 * @param x Vector of which to calculate the length.
 */
template <class T, std::size_t N>
T length(const vector<T, N>& x);

/**
 * Calculates the squared length of a vector.
 *
 * @param x Vector of which to calculate the squared length.
 */
template <class T, std::size_t N>
T length_squared(const vector<T, N>& x);

/**
 * Multiplies two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Product of the two vectors.
 */
///@{
template <class T>
vector<T, 2> mul(const vector<T, 2>& x, const vector<T, 2>& y);
template <class T>
vector<T, 3> mul(const vector<T, 3>& x, const vector<T, 3>& y);
template <class T>
vector<T, 4> mul(const vector<T, 4>& x, const vector<T, 4>& y);
///@}

/**
 * Multiplies a vector by a scalar.
 *
 * @param v Vector.
 * @param s Scalar.
 * @return Product of the vector and scalar.
 */
///@{
template <class T>
vector<T, 2> mul(const vector<T, 2>& v, T s);
template <class T>
vector<T, 3> mul(const vector<T, 3>& v, T s);
template <class T>
vector<T, 4> mul(const vector<T, 4>& v, T s);
///@}

/**
 * Negates a vector.
 *
 * @param x Vector to negate.
 * @return Negated vector.
 */
///@{
template <class T>
vector<T, 2> negate(const vector<T, 2>& x);
template <class T>
vector<T, 3> negate(const vector<T, 3>& x);
template <class T>
vector<T, 4> negate(const vector<T, 4>& x);
///@}

/**
 * Calculates the unit vector in the same direction as the original vector.
 *
 * @param x Vector to normalize.
 */
template <class T, std::size_t N>
vector<T, N> normalize(const vector<T, N>& x);

/**
 * Subtracts a vector from another vector.
 */
///@{
template <class T>
vector<T, 2> sub(const vector<T, 2>& x, const vector<T, 2>& y);
template <class T>
vector<T, 3> sub(const vector<T, 3>& x, const vector<T, 3>& y);
template <class T>
vector<T, 4> sub(const vector<T, 4>& x, const vector<T, 4>& y);
///@}

/**
 *
 */
template <class T, std::size_t N>
vector<T, N> operator+(const vector<T, N>& x, const vector<T, N>& y);

/**
 *
 */
template <class T, std::size_t N>
vector<T, N> operator-(const vector<T, N>& x);

/**
 *
 */
template <class T, std::size_t N>
vector<T, N> operator-(const vector<T, N>& x, const vector<T, N>& y);

/**
 *
 */
template <class T, std::size_t N>
vector<T, N> operator*(const vector<T, N>& x, const vector<T, N>& y);

/**
 *
 */
template <class T, std::size_t N>
vector<T, N> operator*(const vector<T, N>& v, T s);

/**
 *
 */
template <class T, std::size_t N>
vector<T, N> operator*(T s, const vector<T, N>& v);

/**
 *
 */
template <class T, std::size_t N>
vector<T, N> operator/(const vector<T, N>& x, const vector<T, N>& y);

/**
 *
 */
template <class T, std::size_t N>
vector<T, N> operator/(const vector<T, N>& v, T s);

/**
 * Writes the elements of a vector to an output stream, with each element delimeted by a space.
 *
 * @param os Output stream.
 * @param v Vector.
 */
template <class T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const vector<T, N>& v);

template <class T>
inline vector<T, 2> add(const vector<T, 2>& x, const vector<T, 2>& y)
{
	return {x[0] + y[0], x[1] + y[1]};
}

template <class T>
inline vector<T, 3> add(const vector<T, 3>& x, const vector<T, 3>& y)
{
	return {x[0] + y[0], x[1] + y[1], x[2] + y[2]};
}

template <class T>
inline vector<T, 4> add(const vector<T, 4>& x, const vector<T, 4>& y)
{
	return {x[0] + y[0], x[1] + y[1], x[2] + y[2], x[3] + y[3]};
}

template <class T>
inline vector<T, 3> cross(const vector<T, 3>& x, const vector<T, 3>& y)
{
	return
		{
			x[1] * y[2] - y[1] * x[2],
			x[2] * y[0] - y[2] * x[0],
			x[0] * y[1] - y[0] * x[1]
		};
}

template <class T, std::size_t N>
inline vector<T, N> distance(const vector<T, N>& p0, const vector<T, N>& p1)
{
	static_assert(std::is_floating_point<T>::value);
	return length(sub(p0, p1));
}

template <class T, std::size_t N>
inline vector<T, N> distance_squared(const vector<T, N>& p0, const vector<T, N>& p1)
{
	static_assert(std::is_floating_point<T>::value);
	return length_squared(sub(p0, p1));
}

template <class T>
inline vector<T, 2> div(const vector<T, 2>& x, const vector<T, 2>& y)
{
	return {x[0] / y[0], x[1] / y[1]};
}

template <class T>
inline vector<T, 3> div(const vector<T, 3>& x, const vector<T, 3>& y)
{
	return {x[0] / y[0], x[1] / y[1], x[2] / y[2]};
}

template <class T>
inline vector<T, 4> div(const vector<T, 4>& x, const vector<T, 4>& y)
{
	return {x[0] / y[0], x[1] / y[1], x[2] / y[2], x[3] / y[3]};
}

template <class T>
inline vector<T, 2> div(const vector<T, 2>& v, T s)
{
	return {v[0] / s, v[1] / s};
}

template <class T>
inline vector<T, 3> div(const vector<T, 3>& v, T s)
{
	return {v[0] / s, v[1] / s, v[2] / s};
}

template <class T>
inline vector<T, 4> div(const vector<T, 4>& v, T s)
{
	return {v[0] / s, v[1] / s, v[2] / s, v[3] / s};
}

template <class T>
inline T dot(const vector<T, 2>& x, const vector<T, 2>& y)
{
	return x[0] * y[0] + x[1] * y[1];
}

template <class T>
inline T dot(const vector<T, 3>& x, const vector<T, 3>& y)
{
	return x[0] * y[0] + x[1] * y[1] + x[2] * y[2];
}

template <class T>
inline T dot(const vector<T, 4>& x, const vector<T, 4>& y)
{
	return x[0] * y[0] + x[1] * y[1] + x[2] * y[2] + x[3] * y[3];
}

template <class T, std::size_t N>
inline T length(const vector<T, N>& x)
{
	static_assert(std::is_floating_point<T>::value);
	return std::sqrt(dot(x, x));
}

template <class T, std::size_t N>
inline T length_squared(const vector<T, N>& x)
{
	static_assert(std::is_floating_point<T>::value);
	return dot(x, x);
}

template <class T>
inline vector<T, 2> mul(const vector<T, 2>& x, const vector<T, 2>& y)
{
	return {x[0] * y[0], x[1] * y[1]};
}

template <class T>
inline vector<T, 3> mul(const vector<T, 3>& x, const vector<T, 3>& y)
{
	return {x[0] * y[0], x[1] * y[1], x[2] * y[2]};
}

template <class T>
inline vector<T, 4> mul(const vector<T, 4>& x, const vector<T, 4>& y)
{
	return {x[0] * y[0], x[1] * y[1], x[2] * y[2], x[3] * y[3]};
}

template <class T>
inline vector<T, 2> mul(const vector<T, 2>& v, T s)
{
	return {v[0] * s, v[1] * s};
}

template <class T>
inline vector<T, 3> mul(const vector<T, 3>& v, T s)
{
	return {v[0] * s, v[1] * s, v[2] * s};
}

template <class T>
inline vector<T, 4> mul(const vector<T, 4>& v, T s)
{
	return {v[0] * s, v[1] * s, v[2] * s, v[3] * s};
}

template <class T>
inline vector<T, 2> negate(const vector<T, 2>& x)
{
	return {-x[0], -x[1]};
}

template <class T>
inline vector<T, 3> negate(const vector<T, 3>& x)
{
	return {-x[0], -x[1], -x[2]};
}

template <class T>
inline vector<T, 4> negate(const vector<T, 4>& x)
{
	return {-x[0], -x[1], -x[2], -x[3]};
}

template <class T, std::size_t N>
inline vector<T, N> normalize(const vector<T, N>& x)
{
	static_assert(std::is_floating_point<T>::value);
	return mul(x, T(1) / length(x));
}

template <class T>
inline vector<T, 2> sub(const vector<T, 2>& x, const vector<T, 2>& y)
{
	return {x[0] - y[0], x[1] - y[1]};
}

template <class T>
inline vector<T, 3> sub(const vector<T, 3>& x, const vector<T, 3>& y)
{
	return {x[0] - y[0], x[1] - y[1], x[2] - y[2]};
}

template <class T>
inline vector<T, 4> sub(const vector<T, 4>& x, const vector<T, 4>& y)
{
	return {x[0] - y[0], x[1] - y[1], x[2] - y[2], x[3] - y[3]};
}

template <class T, std::size_t N>
inline vector<T, N> operator+(const vector<T, N>& x, const vector<T, N>& y)
{
	return add(x, y);
}

template <class T, std::size_t N>
inline vector<T, N> operator-(const vector<T, N>& x)
{
	return negate(x);
}

template <class T, std::size_t N>
inline vector<T, N> operator-(const vector<T, N>& x, const vector<T, N>& y)
{
	return sub(x, y);
}

template <class T, std::size_t N>
inline vector<T, N> operator*(const vector<T, N>& x, const vector<T, N>& y)
{
	return mul(x, y);
}

template <class T, std::size_t N>
inline vector<T, N> operator*(const vector<T, N>& v, T s)
{
	return mul(v, s);
}

template <class T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const vector<T, N>& v)
{
	for (std::size_t i = 0; i < N; ++i)
	{
		os << v[i];

		if (i < N - 1)
		{
			os << ' ';
		}
	}

	return os;
}

} // namespace Emergent

#endif // EMERGENT_MATH_VECTOR_OPERATIONS_HPP

