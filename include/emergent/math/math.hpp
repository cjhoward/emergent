/*
 * Copyright (C) 2017  Christopher J. Howard
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

#ifndef EMERGENT_MATH_HPP
#define EMERGENT_MATH_HPP

#include <emergent/math/types.hpp>

namespace Emergent
{

Quaternion lookRotation(Vector3 forward, Vector3 up);

// Compute barycentric coordinates (u, v, w) for
// point p with respect to triangle (a, b, c)
// http://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates/23745#23745
Vector3 barycentric(const Vector3& p, const Vector3& a, const Vector3& b, const Vector3& c);

Vector3 cartesian(const Vector3& p, const Vector3& a, const Vector3& b, const Vector3& c);

// Returns normalized barycentric coordinates so that u + v + w = 1
Vector3 normalize_barycentric(const Vector3& v);

// Returns the signed area of a triangle
float signed_area(const Vector3& a, const Vector3& b, const Vector3& c);

// Returns true if point p is contained within triangle abc
bool contained(const Vector3& p, const Vector3& a, const Vector3& b, const Vector3& c);

Vector3 closest_point_on_segment(const Vector3& p, const Vector3& a, const Vector3& b);

// Projects a point (v) onto a plane defined by a position (p) and normal (n)
Vector3 project_on_plane(const Vector3& v, const Vector3& p, const Vector3& n);

// Projects a point (p) onto a triangle (abc) and returns the projected point (closest) and edge, if any.
void project_on_triangle(const Vector3& p, const Vector3& a, const Vector3& b, const Vector3& c, Vector3* closest, int* edge);

float ease_out_quintic(float t, float b, float c, float d);

float frand(float min, float max);

Vector3 limit(const Vector3& v, float l);

inline bool nonzero(const Vector3& v)
{
	return (v.x != 0.0f || v.y != 0.0f || v.z != 0.0f);
}

} // namespace Emergent

#endif // EMERGENT_MATH_HPP
