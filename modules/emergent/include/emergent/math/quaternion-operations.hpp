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

#ifndef EMERGENT_MATH_QUATERNION_OPERATIONS_HPP
#define EMERGENT_MATH_QUATERNION_OPERATIONS_HPP

#include <emergent/math/matrix-type.hpp>
#include <emergent/math/quaternion-type.hpp>
#include <emergent/math/vector-operations.hpp>
#include <emergent/math/vector-type.hpp>
#include <cmath>

namespace Emergent
{

/**
 * Adds two quaternions.
 *
 * @param x First quaternion.
 * @param y Second quaternion.
 * @return Sum of the two quaternions.
 */
///@{
template <class T>
quaternion<T> add(const quaternion<T>& x, const quaternion<T>& y);
template <class T>
quaternion<T> operator+(const quaternion<T>& x, const quaternion<T>& y);
///@}

/**
 *
 */
template <class T>
quaternion<T> conjugate(const quaternion<T>& x);

/**
 * Divides a quaternion by a scalar.
 *
 * @param q Quaternion.
 * @param s Scalar.
 * @return Result of the division.
 */
///@{
template <class T>
quaternion<T> div(const quaternion<T>& q, T s);
template <class T>
quaternion<T> operator/(const quaternion<T>& q, T s);
///@}


/**
 *
 */
template <class T>
T length(const quaternion<T>& x);

/**
 *
 */
template <class T>
T length_squared(const quaternion<T>& x);

/**
 * Creates a unit quaternion rotation using forward and up vectors.
 *
 * @param forward Unit forward vector.
 * @param up Unit up vector.
 * @return Unit rotation quaternion.
 */
template <class T>
quaternion<T> look_rotation(const vector<T, 3>& forward, const vector<T, 3>& up);

/**
 * Converts a quaternion to a rotation matrix.
 *
 * @param q Unit quaternion.
 * @return Matrix representing the rotation described by `q`.
 */
template <class T>
matrix<T, 3, 3> matrix_cast(const quaternion<T>& q);

/**
 * Multiplies two quaternions.
 *
 * @param x First quaternion.
 * @param y Second quaternion.
 * @return Product of the two quaternions.
 */
///@{
template <class T>
quaternion<T> mul(const quaternion<T>& x, const quaternion<T>& y);
template <class T>
quaternion<T> operator*(const quaternion<T>& x, const quaternion<T>& y);
///@}

/**
 * Multiplies a quaternion by a scalar.
 *
 * @param q Quaternion.
 * @param s Scalar.
 * @return Product of the quaternion and scalar.
 */
///@{
template <class T>
quaternion<T> mul(const quaternion<T>& q, T s);
template <class T>
quaternion<T> operator*(const quaternion<T>& q, T s);
///@}

/**
 * Normalizes a quaternion.
 */
template <class T>
quaternion<T> normalize(const quaternion<T>& x);

/**
 * Subtracts a quaternion from another quaternion.
 *
 * @param x First quaternion.
 * @param y Second quaternion.
 * @return Difference between the quaternions.
 */
///@{
template <class T>
quaternion<T> sub(const quaternion<T>& x, const quaternion<T>& y);
template <class T>
quaternion<T> operator-(const quaternion<T>& x, const quaternion<T>& y);
///@}


/**
 * Converts a 3x3 rotation matrix to a quaternion.
 *
 * @param m Rotation matrix.
 * @return Unit quaternion representing the rotation described by `m`.
 */
template <class T>
quaternion<T> quaternion_cast(const matrix<T, 3, 3>& m);

template <class T>
inline quaternion<T> add(const quaternion<T>& x, const quaternion<T>& y)
{
	return {std::get<0>(x) + std::get<0>(y), std::get<1>(x) + std::get<1>(y)};
}

template <class T>
inline quaternion<T> operator+(const quaternion<T>& x, const quaternion<T>& y)
{
	return add(x, y);
}

template <class T>
inline quaternion<T> conjugate(const quaternion<T>& x)
{
	return {std::get<0>(x), -std::get<1>(x)};
}

template <class T>
inline quaternion<T> div(const quaternion<T>& q, T s)
{
	return {std::get<0>(q) / s, std::get<1>(q) / s};
}

template <class T>
inline quaternion<T> operator/(const quaternion<T>& q, T s)
{
	return div(q, s);
}

template <class T>
inline T length(const quaternion<T>& x)
{
	return std::sqrt(std::get<0>(x) * std::get<0>(x) + length_squared(std::get<1>(x)));
}

template <class T>
inline T length_squared(const quaternion<T>& x)
{
	return std::get<0>(x) * std::get<0>(x) + length_squared(std::get<1>(x));
}

template <class T>
quaternion<T> look_rotation(const vector<T, 3>& forward, const vector<T, 3>& up)
{
	// Form orthogonal matrix
	matrix<T, 3, 3> m;
	m[0] = normalize(cross(up, forward)); // Right
	m[1] = cross(forward, m[0]);          // Up
	m[2] = forward;                       // Forward

	// Convert to quaternion
	return normalize(quaternion_cast(m));
}

template <class T>
matrix<T, 3, 3> matrix_cast(const quaternion<T>& q)
{
	T wx = std::get<0>(q) * std::get<1>(q)[0];
	T wy = std::get<0>(q) * std::get<1>(q)[1];
	T wz = std::get<0>(q) * std::get<1>(q)[2];
	T xx = std::get<1>(q)[0] * std::get<1>(q)[0];
	T xy = std::get<1>(q)[0] * std::get<1>(q)[1];
	T xz = std::get<1>(q)[0] * std::get<1>(q)[2];
	T yy = std::get<1>(q)[1] * std::get<1>(q)[1];
	T yz = std::get<1>(q)[1] * std::get<1>(q)[2];
	T zz = std::get<1>(q)[2] * std::get<1>(q)[2];

	return
		{{
			{T(1) - (yy + zz) * T(2), (xy + wz) * T(2), (xz - wy) * T(2)},
			{(xy - wz) * T(2), T(1) - (xx + zz) * T(2), (yz + wx) * T(2)},
			{(xz + wy) * T(2), (yz - wx) * T(2), T(1) - (xx + yy) * T(2)}
		}};
}

template <class T>
quaternion<T> mul(const quaternion<T>& x, const quaternion<T>& y)
{
	return
		{
			-std::get<1>(x)[0] * std::get<1>(y)[0] - std::get<1>(x)[1] * std::get<1>(y)[1] - std::get<1>(x)[2] * std::get<1>(y)[2] + std::get<0>(x) * std::get<0>(y),
			{
				std::get<1>(x)[0] * std::get<0>(y) + std::get<1>(x)[1] * std::get<1>(y)[2] - std::get<1>(x)[2] * std::get<1>(y)[1] + std::get<0>(x) * std::get<1>(y)[0],
				-std::get<1>(x)[0] * std::get<1>(y)[2] + std::get<1>(x)[1] * std::get<0>(y) + std::get<1>(x)[2] * std::get<1>(y)[0] + std::get<0>(x) * std::get<1>(y)[1],
				std::get<1>(x)[0] * std::get<1>(y)[1] - std::get<1>(x)[1] * std::get<1>(y)[0] + std::get<1>(x)[2] * std::get<0>(y) + std::get<0>(x) * std::get<1>(y)[2]
			}
		};
}

template <class T>
inline quaternion<T> operator*(const quaternion<T>& x, const quaternion<T>& y)
{
	return mul(x, y);
}

template <class T>
inline quaternion<T> mul(const quaternion<T>& q, T s)
{
	return {std::get<0>(q) * s, std::get<1>(q) * s};
}

template <class T>
inline quaternion<T> operator*(const quaternion<T>& q, T s)
{
	return mul(q, s);
}

template <class T>
inline quaternion<T> normalize(const quaternion<T>& x)
{
	return mul(x, T(1) / length(x));
}

template <class T>
inline quaternion<T> sub(const quaternion<T>& x, const quaternion<T>& y)
{
	return {std::get<0>(x) - std::get<0>(y), std::get<1>(x) - std::get<1>(y)};
}

template <class T>
inline quaternion<T> operator-(const quaternion<T>& x, const quaternion<T>& y)
{
	return sub(x, y);
}

template <class T>
quaternion<T> quaternion_cast(const matrix<T, 3, 3>& m)
{
	T r;
	vector<T, 3> i;

	T trace = m[0][0] + m[1][1] + m[2][2];
	if (trace > T(0))
	{
		T s = T(0.5) / std::sqrt(trace + T(1));
		r = T(0.25) / s;
		i =
		{
			(m[2][1] - m[1][2]) * s,
			(m[0][2] - m[2][0]) * s,
			(m[1][0] - m[0][1]) * s
		};
	}
	else
	{
		if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
		{
			T s = T(2) / std::sqrt(T(1) + m[0][0] - m[1][1] - m[2][2]);
			r = (m[2][1] - m[1][2]) * s;
			i =
			{
				T(0.25) / s,
				(m[0][1] + m[1][0]) * s,
				(m[0][2] + m[2][0]) * s
			};
		}
		else if (m[1][1] > m[2][2])
		{
			T s = T(2) / std::sqrt(T(1) + m[1][1] - m[0][0] - m[2][2]);
			r = (m[0][2] - m[2][0]) * s;
			i =
			{
				(m[0][1] + m[1][0]) * s,
				T(0.25) / s,
				(m[1][2] + m[2][1]) * s
			};
		}
		else
		{
			T s = T(2) / std::sqrt(T(1) + m[2][2] - m[0][0] - m[1][1]);
			r = (m[1][0] - m[0][1]) * s;
			i = 
			{
				(m[0][2] + m[2][0]) * s,
				(m[1][2] + m[2][1]) * s,
				T(0.25) / s
			};
		}
	}

	return {r, i};
}

} // namespace Emergent

#endif // EMERGENT_MATH_QUATERNION_OPERATIONS_HPP

