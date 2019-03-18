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
#include <emergent/math/vector-types.hpp>
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
template <class T, std::size_t N>
vector<T, N> barycentric(const vector<T, N>& p, const triangle<T, N>& t);

/**
 * Calculates the cartesian coordinates for barycentric point p with respect to triangle t.
 *
 * @param p Barycentric point for which to calculate the cartesian coordinates.
 * @param t Triangle to which the barycentric coordinates are in respect.
 */
template <class T, std::size_t N>
vector<T, N> cartesian(const vector<T, N>& p, const triangle<T, N>& t);

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
template <class T, std::size_t N>
T signedArea(const triangle<T, N>& t);

/**
 * Returns true if point p is contained within triangle t.
 *
 * @param p Point to check for containment.
 * @param t Triangle in which to check for containment.
 */
template <class T, std::size_t N>
bool contained(const vector<T, N>& p, const triangle<T, N>& t);

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

} // namespace Emergent

#endif // EMERGENT_MATH_TRIGONOMETRY_HPP
