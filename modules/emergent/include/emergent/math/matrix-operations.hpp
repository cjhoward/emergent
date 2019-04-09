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

#ifndef EMERGENT_MATH_MATRIX_OPERATIONS_HPP
#define EMERGENT_MATH_MATRIX_OPERATIONS_HPP

#include <emergent/math/matrix-type.hpp>
#include <emergent/math/vector-operations.hpp>
#include <emergent/math/vector-type.hpp>
#include <type_traits>

namespace Emergent
{

/**
 * Adds two matrices.
 *
 * @param x First matrix.
 * @param y Second matrix.
 * @return Sum of the two matrices.
 */
///@{
template <class T>
matrix<T, 2, 2> add(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y);
template <class T>
matrix<T, 3, 3> add(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y);
template <class T>
matrix<T, 4, 4> add(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y);
template <class T, std::size_t N, std::size_t M>
matrix<T, N, M> operator+(const matrix<T, N, M>& x, const matrix<T, N, M>& y);
///@}

/**
 * Calculates the determinant of a matrix.
 *
 * @param m Matrix of which to take the determinant. 
 */
///@{
template <class T>
T determinant(const matrix<T, 2, 2>& m);
template <class T>
T determinant(const matrix<T, 3, 3>& m);
template <class T>
T determinant(const matrix<T, 4, 4>& m);
///@}

/**
 * Calculates the inverse of a matrix.
 *
 * @param m Matrix of which to take the inverse.
 */
///@{
template <class T>
matrix<T, 2, 2> inverse(const matrix<T, 2, 2>& m);
template <class T>
matrix<T, 3, 3> inverse(const matrix<T, 3, 3>& m);
template <class T>
matrix<T, 4, 4> inverse(const matrix<T, 4, 4>& m);
///@}

/**
 * Performs a component-wise multiplication of two matrices.
 *
 * @param x First matrix multiplicand.
 * @param y Second matrix multiplicand.
 */
///@{
template <class T>
matrix<T, 2, 2> componentwise_mul(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y);
template <class T>
matrix<T, 3, 3> componentwise_mul(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y);
template <class T>
matrix<T, 4, 4> componentwise_mul(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y);
///@}

/**
 * Multiplies two matrices.
 *
 * @param x First matrix.
 * @param y Second matrix.
 * @return Product of the two matrices.
 */
///@{
template <class T>
matrix<T, 2, 2> mul(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y);
template <class T>
matrix<T, 3, 3> mul(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y);
template <class T>
matrix<T, 4, 4> mul(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y);
template <class T, std::size_t N, std::size_t M>
matrix<T, N, M> operator*(const matrix<T, N, M>& x, const matrix<T, N, M>& y);
///@}

/**
 * Multiplies a matrix by a scalar.
 *
 * @param m Matrix.
 * @param s Scalar.
 * @return Product of the matrix and the scalar..
 */
///@{
template <class T, std::size_t N, std::size_t M>
matrix<T, N, M> mul(const matrix<T, N, M>& m, T s);
template <class T, std::size_t N, std::size_t M>
matrix<T, N, M> operator*(const matrix<T, N, M>& m, T s);
template <class T, std::size_t N, std::size_t M>
matrix<T, N, M> operator*(T s, const matrix<T, N, M>& m);
///@}

/**
 * Creates an orthographic projection matrix.
 *
 * @param left Distance to the left clipping plane.
 * @param right Distance to the right clipping plane.
 * @param bottom Distance to the bottom clipping plane.
 * @param top Distance to the top clipping plane.
 * @param z_near Distance to the near clipping plane.
 * @param z_far Distance to the far clipping plane.
 * @return Orthographic projection matrix.
 */
template <class T>
matrix<T, 4, 4> ortho(T left, T right, T bottom, T top, T z_near, T z_far);

/**
 * Calculates the outer product of a pair of vectors.
 *
 * @param c Parameter to be treated as a column vector.
 * @param r Parameter to be treated as a row vector.
 */
///@{
template <class T>
matrix<T, 2, 2> outer_product(const vector<T, 2>& c, const vector<T, 2>& r);
template <class T>
matrix<T, 3, 3> outer_product(const vector<T, 3>& c, const vector<T, 3>& r);
template <class T>
matrix<T, 4, 4> outer_product(const vector<T, 4>& c, const vector<T, 4> r);
///@}

/**
 * Creates a perspective projection matrix.
 *
 * @param vertical_fov Vertical field of view angle, in radians.
 * @param aspect_ratio Aspect ratio which determines the horizontal field of view.
 * @param z_near Distance to the near clipping plane.
 * @param z_far Distance to the far clipping plane.
 * @return Perspective projection matrix.
 */
template <class T>
matrix<T, 4, 4> perspective(T vertical_fov, T aspect_ratio, T z_near, T z_far);

/**
 * Subtracts a matrix from another matrix.
 *
 * @param x First matrix.
 * @param y Second matrix.
 * @return Difference between the two matrices.
 */
///@{
template <class T>
matrix<T, 2, 2> sub(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y);
template <class T>
matrix<T, 3, 3> sub(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y);
template <class T>
matrix<T, 4, 4> sub(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y);
template <class T, std::size_t N, std::size_t M>
matrix<T, N, M> operator-(const matrix<T, N, M>& x, const matrix<T, N, M>& y);
///@}

/**
 * Calculates the transpose of a matrix.
 *
 * @param m Matrix of which to take the transpose.
 */
///@{
template <class T>
matrix<T, 2, 2> transpose(const matrix<T, 2, 2>& m);
template <class T>
matrix<T, 3, 3> transpose(const matrix<T, 3, 3>& m);
template <class T>
matrix<T, 4, 4> transpose(const matrix<T, 4, 4>& m);
///@}

template <class T>
matrix<T, 2, 2> add(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y)
{
	return
		{{
			x[0] + y[0],
			x[1] + y[1]
		}};
}

template <class T>
matrix<T, 3, 3> add(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y)
{
	return
		{{
			x[0] + y[0],
			x[1] + y[1],
			x[2] + y[2]
		}};
}

template <class T>
matrix<T, 4, 4> add(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y)
{
	return
		{{
			x[0] + y[0],
			x[1] + y[1],
			x[2] + y[2],
			x[3] + y[3]
		}};
}

template <class T, std::size_t N, std::size_t M>
inline matrix<T, N, M> operator+(const matrix<T, N, M>& x, const matrix<T, N, M>& y)
{
	return add(x, y);
}

template <class T>
T determinant(const matrix<T, 2, 2>& m)
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

template <class T>
T determinant(const matrix<T, 3, 3>& m)
{
	return m[0][0] * m [1][1] * m[2][2] +
		m[0][1] * m[1][2] * m[2][0] +
		m[0][2] * m[1][0] * m[2][1] -
		m[0][0] * m[1][2] * m[2][1] -
		m[0][1] * m[1][0] * m[2][2] -
		m[0][2] * m[1][1] * m[2][0];
}

template <class T>
T determinant(const matrix<T, 4, 4>& m)
{
	return m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] -
		m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
		m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][1] * m[1][2] * m[2][3] * m[3][0] -
		m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][2] * m[1][3] * m[2][0] * m[3][1] +
		m[0][3] * m[1][0] * m[2][2] * m[3][1] - m[0][0] * m[1][3] * m[2][2] * m[3][1] -
		m[0][2] * m[1][0] * m[2][3] * m[3][1] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
		m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][1] * m[1][3] * m[2][0] * m[3][2] -
		m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][0] * m[1][3] * m[2][1] * m[3][2] +
		m[0][1] * m[1][0] * m[2][3] * m[3][2] - m[0][0] * m[1][1] * m[2][3] * m[3][2] -
		m[0][2] * m[1][1] * m[2][0] * m[3][3] + m[0][1] * m[1][2] * m[2][0] * m[3][3] +
		m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][0] * m[1][2] * m[2][1] * m[3][3] -
		m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
}

template <class T>
matrix<T, 2, 2> inverse(const matrix<T, 2, 2>& m)
{
	static_assert(std::is_floating_point<T>::value);

	const T rd(T(1) / determinant(m));
	return
		{{
			{ m[1][1] * rd, -m[0][1] * rd},
			{-m[1][0] * rd,  m[0][0] * rd}
		}};
}

template <class T>
matrix<T, 3, 3> inverse(const matrix<T, 3, 3>& m)
{
	static_assert(std::is_floating_point<T>::value);

	const T rd(T(1) / determinant(m));

	return
		{{
			{
				(m[1][1] * m[2][2] - m[1][2] * m[2][1]) * rd,
				(m[0][2] * m[2][1] - m[0][1] * m[2][2]) * rd,
				(m[0][1] * m[1][2] - m[0][2] * m[1][1]) * rd
			},

			{
				(m[1][2] * m[2][0] - m[1][0] * m[2][2]) * rd,
				(m[0][0] * m[2][2] - m[0][2] * m[2][0]) * rd,
				(m[0][2] * m[1][0] - m[0][0] * m[1][2]) * rd
			},

			{
				(m[1][0] * m[2][1] - m[1][1] * m[2][0]) * rd,
				(m[0][1] * m[2][0] - m[0][0] * m[2][1]) * rd,
				(m[0][0] * m[1][1] - m[0][1] * m[1][0]) * rd
			}
		}};
}

template <class T>
matrix<T, 4, 4> inverse(const matrix<T, 4, 4>& m)
{
	static_assert(std::is_floating_point<T>::value);

	const T rd(T(1) / determinant(m));

	return
		{{
			{
				(m[1][2] * m[2][3] * m[3][1] - m[1][3] * m[2][2] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] - m[1][2] * m[2][1] * m[3][3] + m[1][1] * m[2][2] * m[3][3]) * rd,
				(m[0][3] * m[2][2] * m[3][1] - m[0][2] * m[2][3] * m[3][1] - m[0][3] * m[2][1] * m[3][2] + m[0][1] * m[2][3] * m[3][2] + m[0][2] * m[2][1] * m[3][3] - m[0][1] * m[2][2] * m[3][3]) * rd,
				(m[0][2] * m[1][3] * m[3][1] - m[0][3] * m[1][2] * m[3][1] + m[0][3] * m[1][1] * m[3][2] - m[0][1] * m[1][3] * m[3][2] - m[0][2] * m[1][1] * m[3][3] + m[0][1] * m[1][2] * m[3][3]) * rd,
				(m[0][3] * m[1][2] * m[2][1] - m[0][2] * m[1][3] * m[2][1] - m[0][3] * m[1][1] * m[2][2] + m[0][1] * m[1][3] * m[2][2] + m[0][2] * m[1][1] * m[2][3] - m[0][1] * m[1][2] * m[2][3]) * rd
			},

			{
				(m[1][3] * m[2][2] * m[3][0] - m[1][2] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][2] + m[1][0] * m[2][3] * m[3][2] + m[1][2] * m[2][0] * m[3][3] - m[1][0] * m[2][2] * m[3][3]) * rd,
				(m[0][2] * m[2][3] * m[3][0] - m[0][3] * m[2][2] * m[3][0] + m[0][3] * m[2][0] * m[3][2] - m[0][0] * m[2][3] * m[3][2] - m[0][2] * m[2][0] * m[3][3] + m[0][0] * m[2][2] * m[3][3]) * rd,
				(m[0][3] * m[1][2] * m[3][0] - m[0][2] * m[1][3] * m[3][0] - m[0][3] * m[1][0] * m[3][2] + m[0][0] * m[1][3] * m[3][2] + m[0][2] * m[1][0] * m[3][3] - m[0][0] * m[1][2] * m[3][3]) * rd,
				(m[0][2] * m[1][3] * m[2][0] - m[0][3] * m[1][2] * m[2][0] + m[0][3] * m[1][0] * m[2][2] - m[0][0] * m[1][3] * m[2][2] - m[0][2] * m[1][0] * m[2][3] + m[0][0] * m[1][2] * m[2][3]) * rd
			},

			{
				(m[1][1] * m[2][3] * m[3][0] - m[1][3] * m[2][1] * m[3][0] + m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] - m[1][1] * m[2][0] * m[3][3] + m[1][0] * m[2][1] * m[3][3]) * rd,
				(m[0][3] * m[2][1] * m[3][0] - m[0][1] * m[2][3] * m[3][0] - m[0][3] * m[2][0] * m[3][1] + m[0][0] * m[2][3] * m[3][1] + m[0][1] * m[2][0] * m[3][3] - m[0][0] * m[2][1] * m[3][3]) * rd,
				(m[0][1] * m[1][3] * m[3][0] - m[0][3] * m[1][1] * m[3][0] + m[0][3] * m[1][0] * m[3][1] - m[0][0] * m[1][3] * m[3][1] - m[0][1] * m[1][0] * m[3][3] + m[0][0] * m[1][1] * m[3][3]) * rd,
				(m[0][3] * m[1][1] * m[2][0] - m[0][1] * m[1][3] * m[2][0] - m[0][3] * m[1][0] * m[2][1] + m[0][0] * m[1][3] * m[2][1] + m[0][1] * m[1][0] * m[2][3] - m[0][0] * m[1][1] * m[2][3]) * rd
			},

			{
				(m[1][2] * m[2][1] * m[3][0] - m[1][1] * m[2][2] * m[3][0] - m[1][2] * m[2][0] * m[3][1] + m[1][0] * m[2][2] * m[3][1] + m[1][1] * m[2][0] * m[3][2] - m[1][0] * m[2][1] * m[3][2]) * rd,
				(m[0][1] * m[2][2] * m[3][0] - m[0][2] * m[2][1] * m[3][0] + m[0][2] * m[2][0] * m[3][1] - m[0][0] * m[2][2] * m[3][1] - m[0][1] * m[2][0] * m[3][2] + m[0][0] * m[2][1] * m[3][2]) * rd,
				(m[0][2] * m[1][1] * m[3][0] - m[0][1] * m[1][2] * m[3][0] - m[0][2] * m[1][0] * m[3][1] + m[0][0] * m[1][2] * m[3][1] + m[0][1] * m[1][0] * m[3][2] - m[0][0] * m[1][1] * m[3][2]) * rd,
				(m[0][1] * m[1][2] * m[2][0] - m[0][2] * m[1][1] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] + m[0][0] * m[1][1] * m[2][2]) * rd
			}
		}};
}

template <class T>
matrix<T, 2, 2> componentwise_mul(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y)
{
	return
		{{
			 {x[0][0] * y[0][0], x[0][1] * y[0][1]},
			 {x[1][0] * y[1][0], x[1][1] * y[1][1]}
		}};
}

template <class T>
matrix<T, 3, 3> componentwise_mul(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y)
{
	return
		{{
			 {x[0][0] * y[0][0], x[0][1] * y[0][1], x[0][2] * y[0][2]},
			 {x[1][0] * y[1][0], x[1][1] * y[1][1], x[1][2] * y[1][2]},
			 {x[2][0] * y[2][0], x[2][1] * y[2][1], x[2][2] * y[2][2]}
		}};
}

template <class T>
matrix<T, 4, 4> componentwise_mul(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y)
{
	return
		{{
			 {x[0][0] * y[0][0], x[0][1] * y[0][1], x[0][2] * y[0][2], x[0][3] * y[0][3]},
			 {x[1][0] * y[1][0], x[1][1] * y[1][1], x[1][2] * y[1][2], x[1][3] * y[1][3]},
			 {x[2][0] * y[2][0], x[2][1] * y[2][1], x[2][2] * y[2][2], x[2][3] * y[2][3]},
			 {x[3][0] * y[3][0], x[3][1] * y[3][1], x[3][2] * y[3][2], x[3][3] * y[3][3]}
		}};
}

template <class T>
matrix<T, 2, 2> mul(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y)
{
	return
		{{
			x[0] * y[0][0] + x[1] * y[0][1],
			x[0] * y[1][0] + x[1] * y[1][1]
		}};
}

template <class T>
matrix<T, 3, 3> mul(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y)
{
	return
		{{
			x[0] * y[0][0] + x[1] * y[0][1] + x[2] * y[0][2],
			x[0] * y[1][0] + x[1] * y[1][1] + x[2] * y[1][2],
			x[0] * y[2][0] + x[1] * y[2][1] + x[2] * y[2][2]
		}};
}

template <class T>
matrix<T, 4, 4> mul(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y)
{
	return
		{{
			x[0] * y[0][0] + x[1] * y[0][1] + x[2] * y[0][2] + x[3] * y[0][3],
			x[0] * y[1][0] + x[1] * y[1][1] + x[2] * y[1][2] + x[3] * y[1][3],
			x[0] * y[2][0] + x[1] * y[2][1] + x[2] * y[2][2] + x[3] * y[2][3],
			x[0] * y[3][0] + x[1] * y[3][1] + x[2] * y[3][2] + x[3] * y[3][3]
		}};
}

template <class T, std::size_t N, std::size_t M>
inline matrix<T, N, M> operator*(const matrix<T, N, M>& x, const matrix<T, N, M>& y)
{
	return mul(x, y);
}

/// @internal
template <class T, std::size_t N, std::size_t M, std::size_t... I>
inline matrix<T, N, M> mul(const matrix<T, N, M>& m, T s, std::index_sequence<I...>)
{
	return {{(m[I] * s)...}};
}

template <class T, std::size_t N, std::size_t M>
inline matrix<T, N, M> mul(const matrix<T, N, M>& m, T s)
{
	return mul(m, s, std::make_index_sequence<N>{});
}

template <class T, std::size_t N, std::size_t M>
inline matrix<T, N, M> operator*(const matrix<T, N, M>& m, T s)
{
	return mul(m, s);
}

template <class T, std::size_t N, std::size_t M>
inline matrix<T, N, M> operator*(T s, const matrix<T, N, M>& m)
{
	return mul(m, s);
}

template <class T>
matrix<T, 4, 4> ortho(T left, T right, T bottom, T top, T z_near, T z_far)
{
	return
		{{
			 {T(2) / (right - left), T(0), T(0), T(0)},
			 {T(0), T(2) / (top - bottom), T(0), T(0)},
			 {T(0), T(0), T(-2) / (z_far - z_near), T(0)},
			 {-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((z_far + z_near) / (z_far - z_near)), T(1)}
		}};
}

template <class T>
matrix<T, 2, 2> outer_product(const vector<T, 2>& c, const vector<T, 2>& r)
{
	return
		{{
			 {c[0] * r[0], c[1] * r[0]},
			 {c[0] * r[1], c[1] * r[1]}
		}};
}

template <class T>
matrix<T, 3, 3> outer_product(const vector<T, 3>& c, const vector<T, 3>& r)
{
	return
		{{
			 {c[0] * r[0], c[1] * r[0], c[2] * r[0]},
			 {c[0] * r[1], c[1] * r[1], c[2] * r[1]},
			 {c[0] * r[2], c[1] * r[2], c[2] * r[2]}
		}};
}

template <class T>
matrix<T, 4, 4> outer_product(const vector<T, 4>& c, const vector<T, 4> r)
{
	return
		{{
			 {c[0] * r[0], c[1] * r[0], c[2] * r[0], c[3] * r[0]},
			 {c[0] * r[1], c[1] * r[1], c[2] * r[1], c[3] * r[1]},
			 {c[0] * r[2], c[1] * r[2], c[2] * r[2], c[3] * r[2]},
			 {c[0] * r[3], c[1] * r[3], c[2] * r[3], c[3] * r[3]}
		}};
}

template <class T>
matrix<T, 4, 4> perspective(T vertical_fov, T aspect_ratio, T z_near, T z_far)
{
	T half_fov = vertical_fov * T(0.5);
	T f = std::cos(half_fov) / std::sin(half_fov);

	return
		{{
			 {f / aspect_ratio, T(0), T(0), T(0)},
			 {T(0), f, T(0), T(0)},
			 {T(0), T(0), (z_far + z_near) / (z_near - z_far), T(-1)},
			 {T(0), T(0), (T(2) * z_near * z_far) / (z_near - z_far), T(0)}
		}};
}

template <class T>
matrix<T, 2, 2> sub(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y)
{
	return
		{{
			x[0] - y[0],
			x[1] - y[1]
		}};
}

template <class T>
matrix<T, 3, 3> sub(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y)
{
	return
		{{
			x[0] - y[0],
			x[1] - y[1],
			x[2] - y[2]
		}};
}

template <class T>
matrix<T, 4, 4> sub(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y)
{
	return
		{{
			x[0] - y[0],
			x[1] - y[1],
			x[2] - y[2],
			x[3] - y[3]
		}};
}

template <class T, std::size_t N, std::size_t M>
inline matrix<T, N, M> operator-(const matrix<T, N, M>& x, const matrix<T, N, M>& y)
{
	return sub(x, y);
}

template <class T>
matrix<T, 2, 2> transpose(const matrix<T, 2, 2>& m)
{

	return
		{{
			{
				m[0][0], m[1][0]
			},

			{
				m[0][1], m[1][1]
			}
		}};
}

template <class T>
matrix<T, 3, 3> transpose(const matrix<T, 3, 3>& m)
{

	return
		{{
			{
				m[0][0], m[1][0], m[2][0]
			},

			{
				m[0][1], m[1][1], m[2][1]
			},

			{
				m[0][2], m[1][2], m[2][2]
			}
		}};
}

template <class T>
matrix<T, 4, 4> transpose(const matrix<T, 4, 4>& m)
{

	return
		{{
			{
				m[0][0], m[1][0], m[2][0], m[3][0]
			},

			{
				m[0][1], m[1][1], m[2][1], m[3][1]
			},

			{
				m[0][2], m[1][2], m[2][2], m[3][2]
			},

			{
				m[0][3], m[1][3], m[2][3], m[3][3]
			}
		}};
}

} // namespace Emergent

#endif // EMERGENT_MATH_MATRIX_OPERATIONS_HPP

