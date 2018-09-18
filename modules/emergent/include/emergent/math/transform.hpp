/*
 * Copyright (C) 2017-2018  Christopher J. Howard
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

#ifndef EMERGENT_MATH_TRANSFORM_HPP
#define EMERGENT_MATH_TRANSFORM_HPP

#include <emergent/math/types.hpp>

namespace Emergent
{

/**
 * A three-dimensional TRS transform
 *
 * @ingroup math
 */
class Transform
{
public:
	Transform() = default;
	Transform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);
	
	Vector3 translation;
	Quaternion rotation;
	Vector3 scale;
	
	Transform inverse() const;
	
	Vector3 transform(const Vector3& v) const;
	Transform transform(const Transform& other) const;
	Matrix4 toMatrix() const;
	static const Transform& getIdentity();
	
	Vector3 operator*(const Vector3& v) const;
	Transform operator*(const Transform& other) const;

	bool operator==(const Transform& rhs) const;
	bool operator!=(const Transform& rhs) const;
};

inline Transform::Transform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale):
	translation(translation),
	rotation(rotation),
	scale(scale)
{}

inline const Transform& Transform::getIdentity()
{
	static const Transform identity(Vector3(0.0f), Quaternion(1.0f, Vector3(0.0f)), Vector3(1.0f));
	return identity;
}

inline Vector3 Transform::operator*(const Vector3& v) const
{
	return transform(v);
}

inline Transform Transform::operator*(const Transform& other) const
{
	return transform(other);
}

inline bool Transform::operator==(const Transform& rhs) const
{
	return (translation == rhs.translation && rotation == rhs.rotation && scale == rhs.scale);
}

inline bool Transform::operator!=(const Transform& rhs) const
{
	return (translation != rhs.translation || rotation != rhs.rotation || scale != rhs.scale);
}


} // namespace Emergent

#endif // EMERGENT_MATH_TRANSFORM_HPP

