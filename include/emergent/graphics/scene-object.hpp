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

#ifndef EMERGENT_GRAPHICS_SCENE_OBJECT_HPP
#define EMERGENT_GRAPHICS_SCENE_OBJECT_HPP

#include <emergent/math/types.hpp>
#include <emergent/geometry/aabb.hpp>

namespace Emergent
{

class Model;

/**
 * Enumerates the scene object types.
 *
 * @ingroup graphics
 */
enum class SceneObjectType
{
	MODEL_INSTANCE,
	LIGHT,
	CAMERA,
	BILLBOARD_BATCH
};

/**
 * Abstract base class for objects which can be added to a scene.
 *
 * @ingroup graphics
 */
class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject() = 0;
	
	void setActive(bool active);
	void setTransform(const Transform& transform);
	void setTranslation(const Vector3& translation);
	void setRotation(const Quaternion& rotation);
	void setScale(const Vector3& scale);
	
	virtual SceneObjectType getSceneObjectType() const = 0;
	
	/// Returns whether this object is active
	bool isActive() const;
	
	/// Returns the bounds of this object
	const AABB& getBounds() const;
	
	/// Returns the transformation
	const Transform& getTransform() const;
	
	/// Returns the transformation translation vector
	const Vector3& getTranslation() const;
	
	/// Returns the transformation rotation quaternion
	const Quaternion& getRotation() const;
	
	/// Returns the transformation scale vector
	const Vector3& getScale() const;
	
	/// Returns the forward vector
	const Vector3& getForward() const;
	
	/// Returns the up vector
	const Vector3& getUp() const;
	
	/// Returns the right vector
	const Vector3& getRight() const;
	
	/// Returns the transformation matrix
	const Matrix4& getMatrix() const;
	
protected:
	void updateBounds();
	
private:
	// Calculates the transformed AABB of this object
	virtual AABB calculateBounds() const;
	
	// Called each time the object is transformed
	virtual void transformed();
	
	// Updates the transform
	void updateTransform();
	
	bool active;
	AABB bounds;
	Transform transform;
	Vector3 forward;
	Vector3 up;
	Vector3 right;
	Matrix4 matrix;
};

inline bool SceneObject::isActive() const
{
	return active;
}

inline const AABB& SceneObject::getBounds() const
{
	return bounds;
}

inline const Transform& SceneObject::getTransform() const
{
	return transform;
}

inline const Vector3& SceneObject::getTranslation() const
{
	return transform.translation;
}

inline const Quaternion& SceneObject::getRotation() const
{
	return transform.rotation;
}

inline const Vector3& SceneObject::getScale() const
{
	return transform.scale;
}

inline const Vector3& SceneObject::getForward() const
{
	return forward;
}

inline const Vector3& SceneObject::getUp() const
{
	return up;
}

inline const Vector3& SceneObject::getRight() const
{
	return right;
}

inline const Matrix4& SceneObject::getMatrix() const
{
	return matrix;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SCENE_OBJECT_HPP

