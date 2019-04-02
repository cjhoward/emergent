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

#ifndef EMERGENT_MATH_QUATERNION_TYPE_HPP
#define EMERGENT_MATH_QUATERNION_TYPE_HPP

#include <emergent/math/vector-type.hpp>
#include <tuple>

namespace Emergent
{

/**
 * A quaternion type is a tuple made of a scalar (real) part and vector (imaginary) part.
 *
 * @tparam T Scalar type.
 */
template <class T>
using quaternion = std::tuple<T, vector<T, 3>>;

} // namespace Emergent

#endif // EMERGENT_MATH_QUATERNION_TYPE_HPP

