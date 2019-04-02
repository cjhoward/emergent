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

#ifndef EMERGENT_MATH_TRIGONOMETRY_HPP
#define EMERGENT_MATH_TRIGONOMETRY_HPP

#include <emergent/math/triangle-types.hpp>
#include <emergent/math/vector-type.hpp>
#include <emergent/math/vector-operations.hpp>
#include <numeric>
#include <optional>
#include <tuple>

namespace Emergent
{

/**
 * Calculates the barycentric coordinates for cartesian point p with respect to triangle t.
 *
 * @param p Cartesian point for which to calculate the barycentric coordinates.
 * @param t Triangle to which the barycentric coordinates are in respect.
 */
template <class T>
vector<T, 3> barycentric(const vector<T, 3>& p, const triangle<T, 3>& t);

/**
 * Calculates the cartesian coordinates for barycentric point p with respect to triangle t.
 *
 * @param p Barycentric point for which to calculate the cartesian coordinates.
 * @param t Triangle to which the barycentric coordinates are in respect.
 */
template <class T>
vector<T, 3> cartesian(const vector<T, 3>& p, const triangle<T, 3>& t);

/**
 * Calculates the normalized barycentric coordinates of a point so that u + v + w = 1.
 *
 * @param p Barycentric point to normalize.
 */
template <class T, std::size_t N>
vector<T, N> normalizeBarycentric(const vector<T, N>& p);

/**
 * Calculates the signed area of a triangle.
 *
 * @param t Triangle for which to calculate the signed area.
 */
template <class T>
T signedArea(const triangle<T, 3>& t);

/**
 * Returns true if point p is contained within triangle t.
 *
 * @param p Point to check for containment.
 * @param t Triangle in which to check for containment.
 */
template <class T>
bool contained(const vector<T, 3>& p, const triangle<T, 3>& t);

/**
 * Projects a point onto a triangle and returns the closest projected point, as well as the edge index and vertex index, if any.
 *
 * @param p Cartesian point to project.
 * @param t Triangle onto which the point will be projected.
 *
 * @return Tuple containing the cartesian coordinates of the closest projected point, followed by the index of the edge onto which the point was projected (if any), then the index of the vertex onto which the point was projected (if any).
 */
template <class T, std::size_t N>
std::tuple<vector<T, N>, std::optional<std::size_t>, std::optional<std::size_t>> project(const vector<T, N>& p, const triangle<T, N>& t);

template <class T>
vector<T, 3> barycentric(const vector<T, 3>& p, const triangle<T, 3>& t)
{
	vector<T, 3> v0 = t[1] - t[0];
	vector<T, 3> v1 = t[2] - t[0];
	vector<T, 3> v2 = p - t[0];

	T d00 = dot(v0, v0);
	T d01 = dot(v0, v1);
	T d11 = dot(v1, v1);
	T d20 = dot(v2, v0);
	T d21 = dot(v2, v1);
	T denom = d00 * d11 - d01 * d01;

	vector<T, 3> result;
	result[1] = (d11 * d20 - d01 * d21) / denom;
	result[2] = (d00 * d21 - d01 * d20) / denom;
	result[0] = 1.0f - result[1] - result[2];

	return result;
}

template <class T>
vector<T, 3> cartesian(const vector<T, 3>& p, const triangle<T, 3>& t)
{
	return t[0] * p[0] + t[1] * p[1] + t[2] * p[2];
}

template <class T, std::size_t N>
vector<T, N> normalizeBarycentric(const vector<T, N>& p)
{
	return p * (T(1) / std::accumulate(p.begin(), p.end(), T(0)));
}

template <class T>
T signedArea(const triangle<T, 3>& t)
{
	return T(0.5) * (-t[1][1] * t[2][0] + t[0][1] *(-t[1][0] + t[2][0]) + t[0][0] * (t[1][1] - t[2][1]) + t[1][0] * t[2][1]);
}


template <class T>
bool contained(const vector<T, 3>& p, const triangle<T, 3>& t)
{
	auto sameSide = [](const vector<T, 3>& p1, const vector<T, 3>& p2, const vector<T, 3>& a, const vector<T, 3>& b) -> bool
	{
		return (dot(cross(b - a, p1 - a), cross(b - a, p2 - a)) >= T(0));
	};
	
	return (sameSide(p, t[0], t[1], t[2]) && sameSide(p, t[1], t[0], t[2]) && sameSide(p, t[2], t[0], t[1]));
}

} // namespace Emergent

#endif // EMERGENT_MATH_TRIGONOMETRY_HPP
