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

#ifndef EMERGENT_MATH_FUNDAMENTAL_MATRIX_TYPES_HPP
#define EMERGENT_MATH_FUNDAMENTAL_MATRIX_TYPES_HPP

#include <emergent/math/matrix-type.hpp>

namespace Emergent
{

/**
 * 2x2, 3x3, and 4x4 matrices of fundamental C++ types.
 */
///@{
using bool2x2 = matrix<bool, 2, 2>;
using bool3x3 = matrix<bool, 3, 3>;
using bool4x4 = matrix<bool, 4, 4>;

using char2x2 = matrix<char, 2, 2>;
using char3x3 = matrix<char, 3, 3>;
using char4x4 = matrix<char, 4, 4>;

using uchar2x2 = matrix<unsigned char, 2, 2>;
using uchar3x3 = matrix<unsigned char, 3, 3>;
using uchar4x4 = matrix<unsigned char, 4, 4>;

using short2x2 = matrix<short, 2, 2>;
using short3x3 = matrix<short, 3, 3>;
using short4x4 = matrix<short, 4, 4>;

using ushort2x2 = matrix<unsigned short, 2, 2>;
using ushort3x3 = matrix<unsigned short, 3, 3>;
using ushort4x4 = matrix<unsigned short, 4, 4>;

using int2x2 = matrix<int, 2, 2>;
using int3x3 = matrix<int, 3, 3>;
using int4x4 = matrix<int, 4, 4>;

using uint2x2 = matrix<unsigned int, 2, 2>;
using uint3x3 = matrix<unsigned int, 3, 3>;
using uint4x4 = matrix<unsigned int, 4, 4>;

using long2x2 = matrix<long, 2, 2>;
using long3x3 = matrix<long, 3, 3>;
using long4x4 = matrix<long, 4, 4>;

using ulong2x2 = matrix<unsigned long, 2, 2>;
using ulong3x3 = matrix<unsigned long, 3, 3>;
using ulong4x4 = matrix<unsigned long, 4, 4>;

using float2x2 = matrix<float, 2, 2>;
using float3x3 = matrix<float, 3, 3>;
using float4x4 = matrix<float, 4, 4>;

using double2x2 = matrix<double, 2, 2>;
using double3x3 = matrix<double, 3, 3>;
using double4x4 = matrix<double, 4, 4>;
///@}

} // namespace Emergent

#endif // EMERGENT_MATH_FUNDAMENTAL_MATRIX_TYPES_HPP

