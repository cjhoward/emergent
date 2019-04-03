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

#ifndef EMERGENT_MATH_TRANSFORM_TYPES_HPP
#define EMERGENT_MATH_TRANSFORM_TYPES_HPP

#include <emergent/math/quaternion-type.hpp>
#include <emergent/math/vector-type.hpp>

namespace Emergent
{

template<class T>
struct transform2
{
	vector<T, 2> translation;
	T rotation;
	vector<T, 2> scale;
};

template<class T>
struct transform3
{
	vector<T, 3> translation;
	quaternion<T> rotation;
	vector<T, 3> scale;
};

} // namespace Emergent

#endif // EMERGENT_MATH_TRANSFORM_TYPES_HPP

