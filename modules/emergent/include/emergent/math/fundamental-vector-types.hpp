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

#ifndef EMERGENT_MATH_FUNDAMENTAL_VECTOR_TYPES_HPP
#define EMERGENT_MATH_FUNDAMENTAL_VECTOR_TYPES_HPP

#include <emergent/math/vector-type.hpp>

namespace Emergent
{

/**
 * 2-, 3-, and 4-dimensional Euclidean vectors of fundamental C++ types.
 */
///@{
using bool2 = vector<bool, 2>;
using bool3 = vector<bool, 3>;
using bool4 = vector<bool, 4>;

using char2 = vector<char, 2>;
using char3 = vector<char, 3>;
using char4 = vector<char, 4>;

using uchar2 = vector<unsigned char, 2>;
using uchar3 = vector<unsigned char, 3>;
using uchar4 = vector<unsigned char, 4>;

using short2 = vector<short, 2>;
using short3 = vector<short, 3>;
using short4 = vector<short, 4>;

using ushort2 = vector<unsigned short, 2>;
using ushort3 = vector<unsigned short, 3>;
using ushort4 = vector<unsigned short, 4>;

using int2 = vector<int, 2>;
using int3 = vector<int, 3>;
using int4 = vector<int, 4>;

using uint2 = vector<unsigned int, 2>;
using uint3 = vector<unsigned int, 3>;
using uint4 = vector<unsigned int, 4>;

using long2 = vector<long, 2>;
using long3 = vector<long, 3>;
using long4 = vector<long, 4>;

using ulong2 = vector<unsigned long, 2>;
using ulong3 = vector<unsigned long, 3>;
using ulong4 = vector<unsigned long, 4>;

using float2 = vector<float, 2>;
using float3 = vector<float, 3>;
using float4 = vector<float, 4>;

using double2 = vector<double, 2>;
using double3 = vector<double, 3>;
using double4 = vector<double, 4>;
///@}

} // namespace Emergent

#endif // EMERGENT_MATH_FUNDAMENTAL_VECTOR_TYPES_HPP

