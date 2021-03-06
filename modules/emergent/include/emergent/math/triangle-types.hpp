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

#ifndef EMERGENT_MATH_TRIANGLE_TYPES_HPP
#define EMERGENT_MATH_TRIANGLE_TYPES_HPP

#include <emergent/math/vector-type.hpp>

namespace Emergent
{

/**
 * An n-dimensional triangle.
 *
 * @tparam T Vertex vector component type.
 * @tparam N Number of dimensions.
 */
template <class T, std::size_t N>
using triangle = std::array<vector<T, N>, 3>;

/**
 * A 2-dimensional triangle.
 *
 * @tparam T Vertex vector component type.
 */
template <class T>
using triangle2 = triangle<T, 2>;

/**
 * A 3-dimensional triangle.
 *
 * @tparam T Vertex vector component type.
 */
template <class T>
using triangle3 = triangle<T, 3>;

} // namespace Emergent

#endif // EMERGENT_MATH_TRIANGLE_TYPES_HPP

