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

#ifndef EMERGENT_GRAPHICS_SCENE_OBJECT_HPP
#define EMERGENT_GRAPHICS_SCENE_OBJECT_HPP

#include <emergent/animation/tween.hpp>
#include <emergent/geometry/aabb.hpp>
#include <emergent/math/types.hpp>
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
	void setCullingEnabled(bool enabled);
	void setCullingMask(const BoundingVolume* mask);
	void setTransform(const Transform& transform);
	void setTranslation(const Vector3& translation);
	void setRotation(const Quaternion& rotation);
	void setScale(const Vector3& scale);

	/// Reset each tween in this object
	void resetTweens();
	
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
	const Matrix4& getTransformMatrix() const;

	/// Returns true if this object should be view frustum-culled
	bool isCullingEnabled() const;

	/// Returns the culling mask of this object
	const BoundingVolume* getCullingMask() const;

	/// Returns a list of tweens used by this object
	const std::list<TweenBase*>* getTweens() const;

	/// Returns the bounds tween
	const Tween<AABB>* getBoundsTween() const;

	/// @copydoc SceneObject::getBoundsTween() const
	Tween<AABB>* getBoundsTween();

	/// Returns the transformtion tween
	const Tween<Transform>* getTransformTween() const;
	
	/// @copydoc SceneObject::getTransformTween() const
	Tween<Transform>* getTransformTween();

	/// Returns the forward vector tween
	const Tween<Vector3>* getForwardTween() const;

	/// @copydoc SceneObject::getForwardTween() const
	Tween<Vector3>* getForwardTween();

	/// Returns the up vector tween
	const Tween<Vector3>* getUpTween() const;

	/// @copydoc SceneObject::getUpTween() const
	Tween<Vector3>* getUpTween();

	/// Returns the right vector tween
	const Tween<Vector3>* getRightTween() const;

	/// @copydoc SceneObject::getRightTween() const
	Tween<Vector3>* getRightTween();

	/// Returns the transformation matrix tween
	const Tween<Matrix4>* getTransformMatrixTween() const;

	/// @copydoc SceneObject::getTransformMatrixTween() const
	Tween<Matrix4>* getTransformMatrixTween();
	
protected:
	/**
	 * Recalculates the scene object's bounds.
	 */
	void updateBounds();

	/**
	 * Registers a tween variable to be interpolated between steps. This should only be done once for each tween in the constructor.
	 *
	 * @param tween Tween to be registered.
	 */
	void registerTween(TweenBase* tween);

private:
	// Calculates the transformed AABB of this object
	virtual AABB calculateBounds() const;
	
	// Called each time the object is transformed
	virtual void transformed();
	
	// Updates the transform
	void updateTransform();

	Vector3 interpolateForward(const Vector3& x, const Vector3& y, float a) const;
	Vector3 interpolateUp(const Vector3& x, const Vector3& y, float a) const;
	Vector3 interpolateRight(const Vector3& x, const Vector3& y, float a) const;
	Matrix4 interpolateMatrix(const Matrix4& x, const Matrix4& y, float a) const;
	
	bool active;
	bool cullingEnabled;
	const BoundingVolume* cullingMask;
	AABB bounds;
	Transform transform;
	Vector3 forward;
	Vector3 up;
	Vector3 right;
	Matrix4 matrix;
	Tween<AABB> boundsTween;
	Tween<Transform> transformTween;
	Tween<Vector3> forwardTween;
	Tween<Vector3> upTween;
	Tween<Vector3> rightTween;
	Tween<Matrix4> matrixTween;
	std::list<TweenBase*> tweens;
};

inline void SceneObject::setActive(bool active)
{
	this->active = active;
}

inline void SceneObject::setCullingEnabled(bool enabled)
{
	this->cullingEnabled = enabled;
}

inline void SceneObject::setCullingMask(const BoundingVolume* mask)
{
	this->cullingMask = mask;
}

inline bool SceneObject::isActive() const
{
	return active;
}

inline bool SceneObject::isCullingEnabled() const
{
	return cullingEnabled;
}

inline const BoundingVolume* SceneObject::getCullingMask() const
{
	return cullingMask;
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

inline const Matrix4& SceneObject::getTransformMatrix() const
{
	return matrix;
}

inline const std::list<TweenBase*>* SceneObject::getTweens() const
{
	return &tweens;
}

inline const Tween<AABB>* SceneObject::getBoundsTween() const
{
	return &boundsTween;
}

inline Tween<AABB>* SceneObject::getBoundsTween()
{
	return &boundsTween;
}

inline const Tween<Transform>* SceneObject::getTransformTween() const
{
	return &transformTween;
}

inline Tween<Transform>* SceneObject::getTransformTween()
{
	return &transformTween;
}

inline const Tween<Vector3>* SceneObject::getForwardTween() const
{
	return &forwardTween;
}

inline Tween<Vector3>* SceneObject::getForwardTween()
{
	return &forwardTween;
}

inline const Tween<Vector3>* SceneObject::getUpTween() const
{
	return &upTween;
}

inline Tween<Vector3>* SceneObject::getUpTween()
{
	return &upTween;
}

inline const Tween<Vector3>* SceneObject::getRightTween() const
{
	return &rightTween;
}

inline Tween<Vector3>* SceneObject::getRightTween()
{
	return &rightTween;
}

inline const Tween<Matrix4>* SceneObject::getTransformMatrixTween() const
{
	return &matrixTween;
}

inline Tween<Matrix4>* SceneObject::getTransformMatrixTween()
{
	return &matrixTween;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SCENE_OBJECT_HPP

