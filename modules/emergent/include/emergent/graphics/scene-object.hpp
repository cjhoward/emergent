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
#include <emergent/utility/tween.hpp>
#include <list>

namespace Emergent
{

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

	/// Sets state0 = state1 for each substep-interpolated tween variable
	void resetSubstepTweens();
	
	virtual SceneObjectType getSceneObjectType() const = 0;
	
	/// Returns whether this object is active
	bool isActive() const;
	
	/// Returns the bounds of this object
	const AABB& getBounds() const;
	
	/// Returns the transformation of this object
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

	/// Returns the bounds of this object, interpolated between the previous state and current state.
	const AABB& getSubstepBounds() const;

	/// Returns the transformation of this object, interpolated between the previous state and current state.
	const Transform& getSubstepTransform() const;
	
	/// Returns the transformation translation vector, interpolated between the previous state and current state.
	const Vector3& getSubstepTranslation() const;
	
	/// Returns the transformation rotation quaternion, interpolated between the previous state and current state.
	const Quaternion& getSubstepRotation() const;
	
	/// Returns the transformation scale vector, interpolated between the previous state and current state.
	const Vector3& getSubstepScale() const;
	
	/// Returns the forward vector, interpolated between the previous state and current state.
	const Vector3& getSubstepForward() const;
	
	/// Returns the up vector, interpolated between the previous state and current state.
	const Vector3& getSubstepUp() const;
	
	/// Returns the right vector, interpolated between the previous state and current state.
	const Vector3& getSubstepRight() const;
	
	/// Returns the transformation matrix, interpolated between the previous state and current state.
	Matrix4 getSubstepMatrix() const;

	/// Returns a list of substep-interpolated tween variables
	const std::list<TweenBase*>* getSubstepTweens() const;
	
protected:
	/**
	 * Recalculates the scene object's bounds.
	 */
	void updateBounds();

	/**
	 * Registers a tween variable to be interpolated between steps. This should only be done once for each tween in the constructor.
	 *
	 * @param variable Variable to be registered.
	 */
	void registerSubstepTween(TweenBase* tween);

private:
	// Calculates the transformed AABB of this object
	virtual AABB calculateBounds() const;
	
	// Called each time the object is transformed
	virtual void transformed();
	
	// Updates the transform
	void updateTransform();
	
	bool active;
	std::list<TweenBase*> substepTweens;
	Tween<AABB, lerp<AABB>> bounds;
	Tween<Transform, lerp<Transform>> transform;
	Tween<Vector3, lerp<Vector3>> forward;
	Tween<Vector3, lerp<Vector3>> up;
	Tween<Vector3, lerp<Vector3>> right;
	Matrix4 matrix;
};

inline bool SceneObject::isActive() const
{
	return active;
}

inline const AABB& SceneObject::getBounds() const
{
	return bounds.getState1();
}

inline const Transform& SceneObject::getTransform() const
{
	return transform.getState1();
}

inline const Vector3& SceneObject::getTranslation() const
{
	return transform.getState1().translation;
}

inline const Quaternion& SceneObject::getRotation() const
{
	return transform.getState1().rotation;
}

inline const Vector3& SceneObject::getScale() const
{
	return transform.getState1().scale;
}

inline const Vector3& SceneObject::getForward() const
{
	return forward.getState1();
}

inline const Vector3& SceneObject::getUp() const
{
	return up.getState1();
}

inline const Vector3& SceneObject::getRight() const
{
	return right.getState1();
}

inline const Matrix4& SceneObject::getMatrix() const
{
	return matrix;
}

inline const AABB& SceneObject::getSubstepBounds() const
{
	return bounds.getSubstate();
}

inline const Transform& SceneObject::getSubstepTransform() const
{
	return transform.getSubstate();
}

inline const Vector3& SceneObject::getSubstepTranslation() const
{
	return transform.getSubstate().translation;
}

inline const Quaternion& SceneObject::getSubstepRotation() const
{
	return transform.getSubstate().rotation;
}

inline const Vector3& SceneObject::getSubstepScale() const
{
	return transform.getSubstate().scale;
}

inline const Vector3& SceneObject::getSubstepForward() const
{
	return forward.getSubstate();
}

inline const Vector3& SceneObject::getSubstepUp() const
{
	return up.getSubstate();
}

inline const Vector3& SceneObject::getSubstepRight() const
{
	return right.getSubstate();
}

inline Matrix4 SceneObject::getSubstepMatrix() const
{
	return getSubstepTransform().toMatrix();
}

inline const std::list<TweenBase*>* SceneObject::getSubstepTweens() const
{
	return &substepTweens;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SCENE_OBJECT_HPP

