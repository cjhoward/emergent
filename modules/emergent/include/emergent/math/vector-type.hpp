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

#ifndef EMERGENT_MATH_VECTOR_TYPE_HPP
#define EMERGENT_MATH_VECTOR_TYPE_HPP

#include <array>
#include <cstddef>

namespace Emergent
{

/**
 * An n-dimensional Euclidean vector.
 *
 * @tparam T Vector component type.
 * @tparam N Number of dimensions.
 */
template <class T, std::size_t N>
using vector = std::array<T, N>;

} // namespace Emergent

#endif // EMERGENT_MATH_VECTOR_TYPE_HPP

