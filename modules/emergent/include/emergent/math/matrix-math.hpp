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

#ifndef EMERGENT_MATH_MATRIX_MATH_HPP
#define EMERGENT_MATH_MATRIX_MATH_HPP

#include <emergent/math/matrix-types.hpp>
#include <emergent/math/vector-types.hpp>
#include <type_traits>

namespace Emergent
{

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
matrix<T, 2, 2> matrixCompMult(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y);
template <class T>
matrix<T, 3, 3> matrixCompMult(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y);
template <class T>
matrix<T, 4, 4> matrixCompMult(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y);
///@}

/**
 * Calculates the outer product of a pair of vectors.
 *
 * @param c Parameter to be treated as a column vector.
 * @param r Parameter to be treated as a row vector.
 */
///@{
template <class T>
matrix<T, 2, 2> outerProduct(const vector<T, 2>& c, const vector<T, 2>& r);
template <class T>
matrix<T, 3, 3> outerProduct(const vector<T, 3>& c, const vector<T, 3>& r);
template <class T>
matrix<T, 4, 4> outerProduct(const vector<T, 4>& c, const vector<T, 4> r);
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
matrix<T, 2, 2> matrixCompMult(const matrix<T, 2, 2>& x, const matrix<T, 2, 2>& y)
{
	return
		{{
			 {x[0][0] * y[0][0], x[0][1] * y[0][1]},
			 {x[1][0] * y[1][0], x[1][1] * y[1][1]}
		}};
}

template <class T>
matrix<T, 3, 3> matrixCompMult(const matrix<T, 3, 3>& x, const matrix<T, 3, 3>& y)
{
	return
		{{
			 {x[0][0] * y[0][0], x[0][1] * y[0][1], x[0][2] * y[0][2]},
			 {x[1][0] * y[1][0], x[1][1] * y[1][1], x[1][2] * y[1][2]},
			 {x[2][0] * y[2][0], x[2][1] * y[2][1], x[2][2] * y[2][2]}
		}};
}

template <class T>
matrix<T, 4, 4> matrixCompMult(const matrix<T, 4, 4>& x, const matrix<T, 4, 4>& y)
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
matrix<T, 2, 2> outerProduct(const vector<T, 2>& c, const vector<T, 2>& r)
{
	return
		{{
			 {c[0] * r[0], c[1] * r[0]},
			 {c[0] * r[1], c[1] * r[1]}
		}};
}

template <class T>
matrix<T, 3, 3> outerProduct(const vector<T, 3>& c, const vector<T, 3>& r)
{
	return
		{{
			 {c[0] * r[0], c[1] * r[0], c[2] * r[0]},
			 {c[0] * r[1], c[1] * r[1], c[2] * r[1]},
			 {c[0] * r[2], c[1] * r[2], c[2] * r[2]}
		}};
}

template <class T>
matrix<T, 4, 4> outerProduct(const vector<T, 4>& c, const vector<T, 4> r)
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

#endif // EMERGENT_MATH_MATRIX_MATH_HPP

