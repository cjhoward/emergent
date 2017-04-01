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

#include <emergent/math/math.hpp>
#include <cstdlib>

namespace Emergent
{

Quaternion lookRotation(Vector3 forward, Vector3 up)
{
	Vector3 right = glm::normalize(glm::cross(up, forward));
	up = glm::cross(forward, right);	
	return glm::normalize(glm::quat_cast(Matrix3(right, up, forward)));
}

Vector3 barycentric(const Vector3& p, const Vector3& a, const Vector3& b, const Vector3& c)
{
	Vector3 v0 = b - a;
	Vector3 v1 = c - a;
	Vector3 v2 = p - a;

    float d00 = glm::dot(v0, v0);
    float d01 = glm::dot(v0, v1);
    float d11 = glm::dot(v1, v1);
    float d20 = glm::dot(v2, v0);
    float d21 = glm::dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;

	Vector3 result;
    result.y = (d11 * d20 - d01 * d21) / denom;
    result.z = (d00 * d21 - d01 * d20) / denom;
    result.x = 1.0f - result.y - result.z;
	
	return result;
}

Vector3 cartesian(const Vector3& p, const Vector3& a, const Vector3& b, const Vector3& c)
{
	return a * p.x + b * p.y + c * p.z;
}

Vector3 normalize_barycentric(const Vector3& v)
{
	float inverseLength = 1.0f / (v.x + v.y + v.z);
	return v * inverseLength;
}

float signed_area(const Vector3& a, const Vector3& b, const Vector3& c)
{
	return 0.5f * (-b.y * c.x + a.y *(-b.x + c.x) + a.x * (b.y - c.y) + b.x * c.y);
}

bool contained(const Vector3& p, const Vector3& a, const Vector3& b, const Vector3& c)
{
	bool ab = ((b.y - a.y) * (p.x - a.x) + (-b.x + a.x) * (p.y - a.y) >= 0.0f);
	bool bc = ((c.y - b.y) * (p.x - b.x) + (-c.x + b.x) * (p.y - b.y) >= 0.0f);
	bool ca = ((a.y - c.y) * (p.x - c.x) + (-a.x + c.x) * (p.y - c.y) >= 0.0f);
	return (ab && bc & ca);
}

Vector3 closest_point_on_segment(const Vector3& p, const Vector3& a, const Vector3& b)
{
	Vector3 d = b - a;
	float t = ((p.x - a.x) * d.x + (p.y - a.y) * d.y + (p.z - a.y) * d.z) / glm::dot(d, d);
	t = glm::clamp(t, 0.0f, 1.0f);
	
	return a + d * t;
}

Vector3 project_on_plane(const Vector3& v, const Vector3& p, const Vector3& n)
{
	return v - n * glm::dot(v - p, n);
}

// code taken from Detour's dtClosestPtPointTriangle
// @see https://github.com/recastnavigation/recastnavigation/blob/master/Detour/Source/DetourCommon.cpp
// (zlib license)
void project_on_triangle(const Vector3& p, const Vector3& a, const Vector3& b, const Vector3& c, Vector3* closest, int* edge)
{
	// Check if P in vertex region outside A
	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 ap = p - a;
	float d1 = glm::dot(ab, ap);
	float d2 = glm::dot(ac, ap);
	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// barycentric coordinates (1,0,0)
		*closest = a;
		*edge = 0;
		return;
	}
	
	// Check if P in vertex region outside B
	Vector3 bp = p - b;
	float d3 = glm::dot(ab, bp);
	float d4 = glm::dot(ac, bp);
	if (d3 >= 0.0f && d4 <= d3)
	{
		// barycentric coordinates (0,1,0)
		*closest = b;
		*edge = 1;
		return;
	}
	
	// Check if P in edge region of AB, if so return projection of P onto AB
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		// barycentric coordinates (1-v,v,0)
		float v = d1 / (d1 - d3);
		*closest = ab * v + a;
		*edge = 0;
		return;
	}
	
	// Check if P in vertex region outside C
	Vector3 cp = p - c;
	float d5 = glm::dot(ab, cp);
	float d6 = glm::dot(ac, cp);
	if (d6 >= 0.0f && d5 <= d6)
	{
		// barycentric coordinates (0,0,1)
		*closest = c;
		*edge = 2;
		return;
	}
	
	// Check if P in edge region of AC, if so return projection of P onto AC
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		// barycentric coordinates (1-w,0,w)
		float w = d2 / (d2 - d6);
		*closest = ac * w + a;
		*edge = 2;
		return;
	}
	
	// Check if P in edge region of BC, if so return projection of P onto BC
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		// barycentric coordinates (0,1-w,w)
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = (c - b) * w + b;
		*edge = 1;
		return;
	}
	
	// P inside face region. Compute Q through its barycentric coordinates (u,v,w)
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = ab * v + ac * w + a;
	*edge = -1;
}

// t = time, b = beginning value, c = change in value, d = duration
float ease_out_quintic(float t, float b, float c, float d) {
	t /= d;
	float ts=t*t;

	float tc=ts*t;
	return b+c*(tc*ts + -5*ts*ts + 10*tc + -10*ts + 5*t);
}

float frand(float min, float max)
{
    double f = (float)std::rand() / RAND_MAX;
    return min + f * (max - min);
}

Vector3 limit(const Vector3& v, float l)
{
	float lengthSquared = glm::dot(v, v);
	if (!lengthSquared)
	{
		return v;
	}
	
	float length = std::sqrt(lengthSquared);
	if (length > l)
	{
		return v * (1.0f / length) * l;
	}
	
	return v;
}

} // namespace Emergent
