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
#include <algorithm>
#include <cmath>
#include <ostream>
#include <type_traits>
#include <utility>

namespace Emergent
{

/**
 * Adds two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Sum of the two vectors.
 */
template <class T, std::size_t N>
vector<T, N> add(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Checks if all elements of a boolean vector are `true`.
 *
 * @param x Vector to be tested for truth.
 * @return `true` if all elements are `true`, `false` otherwise.
 */
template <std::size_t N>
bool all(const vector<bool, N>& x);

/**
 * Checks if any elements of a boolean vector are `true`.
 *
 * @param x Vector to be tested for truth.
 * @return `true` if any elements are `true`, `false` otherwise.
 */
template <std::size_t N>
bool any(const vector<bool, N>& x);

/**
 * Clamps the values of a vector's elements.
 *
 * @param x Vector to clamp.
 * @param min_value Minimum element value.
 * @param max_value Maximum element value.
 * @return Clamped vector.
 */
template <class T, std::size_t N>
vector<T, N> clamp(const vector<T, N>& x, T min_value, T max_value);

/**
 * Clamps the length of a vector.
 *
 * @param x Vector to clamp.
 * @param max_length Maximum length.
 * @return Length-clamped vector.
 */
template <class T, std::size_t N>
vector<T, N> clamp_length(const vector<T, N>& x, T max_length);

/**
 * Calculate the cross product of two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Cross product of the two vectors.
 */
template <class T>
vector<T, 3> cross(const vector<T, 3>& x, const vector<T, 3>& y);

/**
 * Calculates the distance between two points.
 *
 * @param p0 First of two points.
 * @param p1 Second of two points.
 * @return Distance between the two points.
 */
template <class T, std::size_t N>
vector<T, N> distance(const vector<T, N>& p0, const vector<T, N>& p1);

/**
 * Calculates the squared distance between two points.
 *
 * @param p0 First of two points.
 * @param p1 Second of two points.
 * @return Squared distance between the two points.
 */
template <class T, std::size_t N>
vector<T, N> distance_squared(const vector<T, N>& p0, const vector<T, N>& p1);

/**
 * Divides a vector by another vector.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Result of the division.
 */
template <class T, std::size_t N>
vector<T, N> div(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Divides a vector by a scalar.
 *
 * @param v Vector.
 * @param s Scalar.
 * @return Result of the division.
 */
template <class T, std::size_t N>
vector<T, N> div(const vector<T, N>& v, T s);

/**
 * Calculates the dot product of two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Dot product of the two vectors.
 */
template <class T, std::size_t N>
T dot(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Compares two vectors for equality
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Boolean vector containing the result of the element comparisons.
 */
template <class T, std::size_t N>
vector<bool, N> equal(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Performs a component-wise greater-than comparison of two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Boolean vector containing the result of the element comparisons.
 */
template <class T, std::size_t N>
vector<bool, N> greater_than(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Performs a component-wise greater-than or equal-to comparison of two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Boolean vector containing the result of the element comparisons.
 */
template <class T, std::size_t N>
vector<bool, N> greater_than_equal(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Calculates the length of a vector.
 *
 * @param x Vector of which to calculate the length.
 * @return Length of the vector.
 */
template <class T, std::size_t N>
T length(const vector<T, N>& x);

/**
 * Calculates the squared length of a vector.
 *
 * @param x Vector of which to calculate the squared length.
 * @return Squared length of the vector.
 */
template <class T, std::size_t N>
T length_squared(const vector<T, N>& x);

/**
 * Performs a component-wise less-than comparison of two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Boolean vector containing the result of the element comparisons.
 */
template <class T, std::size_t N>
vector<bool, N> less_than(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Performs a component-wise less-than or equal-to comparison of two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Boolean vector containing the result of the element comparisons.
 */
template <class T, std::size_t N>
vector<bool, N> less_than_equal(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Multiplies two vectors.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Product of the two vectors.
 */
template <class T, std::size_t N>
vector<T, N> mul(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Multiplies a vector by a scalar.
 *
 * @param v Vector.
 * @param s Scalar.
 * @return Product of the vector and scalar.
 */
template <class T, std::size_t N>
vector<T, N> mul(const vector<T, N>& v, T s);

/**
 * Negates a vector.
 *
 * @param x Vector to negate.
 * @return Negated vector.
 */
template <class T, std::size_t N>
vector<T, N> negate(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Calculates the unit vector in the same direction as the original vector.
 *
 * @param x Vector to normalize.
 * @return Normalized vector.
 */
template <class T, std::size_t N>
vector<T, N> normalize(const vector<T, N>& x);

/**
 * Logically inverts a boolean vector.
 *
 * @param x Vector to be inverted.
 * @return Logically inverted vector.
 */
template <class T, std::size_t N>
vector<bool, N> not(const vector<T, N>& x);

/**
 * Compares two vectors for inequality
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Boolean vector containing the result of the element comparisons.
 */
template <class T, std::size_t N>
vector<bool, N> not_equal(const vector<T, N>& x, const vector<T, N>& y);

/**
 * Subtracts a vector from another vector.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Result of the subtraction.
 */
template <class T, std::size_t N>
vector<T, N> sub(const vector<T, N>& x, const vector<T, N>& y);

/// @copydoc add(const vector<T, N>&, const vector<T, N>&)
template <class T, std::size_t N>
vector<T, N> operator+(const vector<T, N>& x, const vector<T, N>& y);

/// @copydoc negate(const vector<T, N>&)
template <class T, std::size_t N>
vector<T, N> operator-(const vector<T, N>& x);

/// @copydoc sub(const vector<T, N>&, const vector<T, N>&)
template <class T, std::size_t N>
vector<T, N> operator-(const vector<T, N>& x, const vector<T, N>& y);

/// @copydoc mul(const vector<T, N>&, const vector<T, N>&)
template <class T, std::size_t N>
vector<T, N> operator*(const vector<T, N>& x, const vector<T, N>& y);

/// @copydoc mul(const vector<T, N>&, T)
template <class T, std::size_t N>
vector<T, N> operator*(const vector<T, N>& v, T s);

/// @copydoc mul(const vector<T, N>&, T)
template <class T, std::size_t N>
vector<T, N> operator*(T s, const vector<T, N>& v);

/// @copydoc div(const vector<T, N>&, const vector<T, N>&)
template <class T, std::size_t N>
vector<T, N> operator/(const vector<T, N>& x, const vector<T, N>& y);

/// @copydoc div(const vector<T, N>&, T)
template <class T, std::size_t N>
vector<T, N> operator/(const vector<T, N>& v, T s);

/**
 * Adds two vectors and stores the result in the first vector.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Reference to the first vector.
 */
template <class T, std::size_t N>
vector<T, N>& operator+=(vector<T, N>& x, const vector<T, N>& y);

/**
 * Subtracts two vectors and stores the result in the first vector.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Reference to the first vector.
 */
template <class T, std::size_t N>
vector<T, N>& operator-=(vector<T, N>& x, const vector<T, N>& y);

/**
 * Multiplies two vectors and stores the result in the first vector.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Reference to the first vector.
 */
template <class T, std::size_t N>
vector<T, N>& operator*=(vector<T, N>& x, const vector<T, N>& y);

/**
 * Multiplies a vector and a scalar and stores the result in the vector.
 *
 * @param v Vector.
 * @param s Scalar.
 * @return Reference to the vector.
 */
template <class T, std::size_t N>
vector<T, N>& operator*=(vector<T, N>& v, T s);

/**
 * Divides the first vector by the second vector the result in the first vector.
 *
 * @param x First vector.
 * @param y Second vector.
 * @return Reference to the first vector.
 */
template <class T, std::size_t N>
vector<T, N>& operator/=(vector<T, N>& x, const vector<T, N>& y);

/**
 * Divides a vector by a scalar and stores the result in the vector.
 *
 * @param v Vector.
 * @param s Scalar.
 * @return Reference to the vector.
 */
template <class T, std::size_t N>
vector<T, N>& operator/=(vector<T, N>& v, T s);

/**
 * Writes the elements of a vector to an output stream, with each element delimeted by a space.
 *
 * @param os Output stream.
 * @param v Vector.
 * @return Output stream.
 */
template <class T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const vector<T, N>& v);

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<T, N> add(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] + y[I])...};
}

template <class T, std::size_t N>
inline vector<T, N> add(const vector<T, N>& x, const vector<T, N>& y)
{
	return add(x, y, std::make_index_sequence<N>{});
}

/// @internal
template <std::size_t N, std::size_t... I>
inline bool all(const vector<bool, N>& x, std::index_sequence<I...>)
{
	return (x[I] && ...);
}

template <std::size_t N>
inline bool all(const vector<bool, N>& x)
{
	return all(x, std::make_index_sequence<N>{});
}

/// @internal
template <std::size_t N, std::size_t... I>
inline bool any(const vector<bool, N>& x, std::index_sequence<I...>)
{
	return (x[I] || ...);
}

template <std::size_t N>
inline bool any(const vector<bool, N>& x)
{
	return any(x, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<T, N> clamp(const vector<T, N>& x, T min_value, T max_value, std::index_sequence<I...>)
{
	return {std::min<T>(max_value, std::max<T>(min_value, x[I]))...};
}

template <class T, std::size_t N>
inline vector<T, N> clamp(const vector<T, N>& x, T min_value, T max_value)
{
	return clamp(x, min_value, max_value, std::make_index_sequence<N>{});
}

template <class T, std::size_t N>
vector<T, N> clamp_length(const vector<T, N>& x, T max_length)
{
	T length2 = length_squared(x);
	return (length2 > max_length * max_length) ? (x * max_length / std::sqrt(length2)) : x;
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

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<T, N> div(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] / y[I])...};
}

template <class T, std::size_t N>
inline vector<T, N> div(const vector<T, N>& x, const vector<T, N>& y)
{
	return div(x, y, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<T, N> div(const vector<T, N>& v, T s, std::index_sequence<I...>)
{
	return {(v[I] / s)...};
}

template <class T, std::size_t N>
inline vector<T, N> div(const vector<T, N>& v, T s)
{
	return div(v, s, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline T dot(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return ((x[I] * y[I]) + ...);
}

template <class T, std::size_t N>
inline T dot(const vector<T, N>& x, const vector<T, N>& y)
{
	return dot(x, y, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<bool, N> equal(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] == y[I])...};
}

template <class T, std::size_t N>
inline vector<bool, N> equal(const vector<T, N>& x, const vector<T, N>& y)
{
	return equal(x, y, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<bool, N> greater_than(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] > y[I])...};
}

template <class T, std::size_t N>
inline vector<bool, N> greater_than(const vector<T, N>& x, const vector<T, N>& y)
{
	return greater_than(x, y, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<bool, N> greater_than_equal(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] >= y[I])...};
}

template <class T, std::size_t N>
inline vector<bool, N> greater_than_equal(const vector<T, N>& x, const vector<T, N>& y)
{
	return greater_than_equal(x, y, std::make_index_sequence<N>{});
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

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<bool, N> less_than(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] < y[I])...};
}

template <class T, std::size_t N>
inline vector<bool, N> less_than(const vector<T, N>& x, const vector<T, N>& y)
{
	return less_than(x, y, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<bool, N> less_than_equal(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] <= y[I])...};
}

template <class T, std::size_t N>
inline vector<bool, N> less_than_equal(const vector<T, N>& x, const vector<T, N>& y)
{
	return less_than_equal(x, y, std::make_index_sequence<N>{});
}

template <class T, std::size_t N>
vector<T, N> limit(const vector<T, N>& v, T l)
{
	T l2 = length_squared(v);
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<T, N> mul(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] * y[I])...};
}

template <class T, std::size_t N>
inline vector<T, N> mul(const vector<T, N>& x, const vector<T, N>& y)
{
	return mul(x, y, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<T, N> mul(const vector<T, N>& v, T s, std::index_sequence<I...>)
{
	return {(v[I] * s)...};
}

template <class T, std::size_t N>
inline vector<T, N> mul(const vector<T, N>& v, T s)
{
	return mul(v, s, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<T, N> negate(const vector<T, N>& x, std::index_sequence<I...>)
{
	return {(-x[I])...};
}

template <class T, std::size_t N>
inline vector<T, N> negate(const vector<T, N>& x, const vector<T, N>& y)
{
	return negate(x, std::make_index_sequence<N>{});
}

template <class T, std::size_t N>
inline vector<T, N> normalize(const vector<T, N>& x)
{
	static_assert(std::is_floating_point<T>::value);
	return mul(x, T(1) / length(x));
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<bool, N> not(const vector<T, N>& x, std::index_sequence<I...>)
{
	return {!x[I]...};
}

template <class T, std::size_t N>
inline vector<bool, N> not(const vector<T, N>& x)
{
	return not(x, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<bool, N> not_equal(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] != y[I])...};
}

template <class T, std::size_t N>
inline vector<bool, N> not_equal(const vector<T, N>& x, const vector<T, N>& y)
{
	return not_equal(x, y, std::make_index_sequence<N>{});
}

/// @internal
template <class T, std::size_t N, std::size_t... I>
inline vector<T, N> sub(const vector<T, N>& x, const vector<T, N>& y, std::index_sequence<I...>)
{
	return {(x[I] - y[I])...};
}

template <class T, std::size_t N>
inline vector<T, N> sub(const vector<T, N>& x, const vector<T, N>& y)
{
	return sub(x, y, std::make_index_sequence<N>{});
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
inline vector<T, N> operator*(T s, const vector<T, N>& v)
{
	return mul(v, s);
}

template <class T, std::size_t N>
inline vector<T, N> operator/(const vector<T, N>& x, const vector<T, N>& y)
{
	return div(x, y);
}

template <class T, std::size_t N>
inline vector<T, N> operator/(const vector<T, N>& v, T s)
{
	return div(v, s);
}

template <class T, std::size_t N>
inline vector<T, N>& operator+=(vector<T, N>& x, const vector<T, N>& y)
{
	return (x = x + y);
}

template <class T, std::size_t N>
inline vector<T, N>& operator-=(vector<T, N>& x, const vector<T, N>& y)
{
	return (x = x - y);
}

template <class T, std::size_t N>
inline vector<T, N>& operator*=(vector<T, N>& x, const vector<T, N>& y)
{
	return (x = x * y);
}

template <class T, std::size_t N>
inline vector<T, N>& operator*=(vector<T, N>& v, T s)
{
	return (v = v * s);
}

template <class T, std::size_t N>
inline vector<T, N>& operator/=(vector<T, N>& x, const vector<T, N>& y)
{
	return (x = x * y);
}

template <class T, std::size_t N>
inline vector<T, N>& operator/=(vector<T, N>& v, T s)
{
	return (v = v / s);
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

