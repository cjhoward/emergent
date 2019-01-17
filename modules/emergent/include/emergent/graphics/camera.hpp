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

#ifndef EMERGENT_GRAPHICS_CAMERA_HPP
#define EMERGENT_GRAPHICS_CAMERA_HPP

#include <emergent/geometry/view-frustum.hpp>
#include <emergent/graphics/scene-object.hpp>
#include <emergent/math/types.hpp>

namespace Emergent
{

class Compositor;

/**
 * Renders a scene.
 *
 * @ingroup graphics
 */
class Camera: public SceneObject
{
public:
	Camera();
	
	void setPerspective(float fov, float aspectRatio, float near, float far);
	void setOrthographic(float left, float right, float bottom, float top, float near, float far);
	void lookAt(const Vector3& translation, const Vector3& target, const Vector3& up);
	
	// Maps objects coordinates to window coordinates. viewport vector = (x, y, w, h)
	Vector3 project(const Vector3& object, const Vector4& viewport) const;
	
	// Maps window coordinates to object coordinates. viewport vector = (x, y, w, h)
	Vector3 unproject(const Vector3& window, const Vector4& viewport) const;
	
	void setCullingEnabled(bool enabled);
	void setCullingMask(const BoundingVolume* mask);
	
	void setActive(bool active);


	
	void setCompositor(Compositor* compositor);
	
	// Sets the composite index, which determines the order in which cameras in the scene are composited.
	void setCompositeIndex(std::size_t index);
	
	virtual SceneObjectType getSceneObjectType() const;

	bool isCullingEnabled() const;
	const BoundingVolume* getCullingMask() const;
	bool isActive() const;
	const Compositor* getCompositor() const;
	Compositor* getCompositor();
	std::size_t getCompositeIndex() const;
	
	/// Returns the vertical field of view (in radians)
	float getFOV() const;

	/// Returns the aspect ratio
	float getAspectRatio() const;

	/// Returns the distance to the left clipping plane
	float getClipLeft() const;

	/// Returns the distance to the right clipping plane
	float getClipRight() const;

	/// Returns the distance to the bottom clipping plane
	float getClipBottom() const;

	/// Returns the distance to the top clipping plane
	float getClipTop() const;

	/// Returns the distance to the near clipping plane
	float getClipNear() const;

	/// Returns the distance to the far clipping plane
	float getClipFar() const;

	/// Returns the view matrix
	const Matrix4& getView() const;

	/// Returns the projection matrix
	const Matrix4& getProjection() const;

	/// Returns the inverse projection matrix
	const Matrix4& getInverseProjection() const;

	/// Returns the view-projection matrix
	const Matrix4& getViewProjection() const;

	/// Returns the inverse view-projection matrix
	const Matrix4& getInverseViewProjection() const;

	/// Returns the view frustum
	const ViewFrustum& getViewFrustum() const;

	/// Returns the field of view tween
	const Tween<float>* getFOVTween() const;

	/// @copydoc Camera::getFOVTween() const
	Tween<float>* getFOVTween();

	/// Returns the aspect ratio tween
	const Tween<float>* getAspectRatioTween() const;

	/// @copydoc Camera::getAspectRatioTween() const
	Tween<float>* getAspectRatioTween();

	/// Returns the clip left tween
	const Tween<float>* getClipLeftTween() const;
	Tween<float>* getClipLeftTween();

	/// Returns the clip right tween
	const Tween<float>* getClipRightTween() const;

	/// @copydoc Camera::getClipRightTween() const
	Tween<float>* getClipRightTween();

	/// Returns the clip bottom tween
	const Tween<float>* getClipBottomTween() const;

	/// @copydoc Camera::getClipBottomTween() const
	Tween<float>* getClipBottomTween();

	/// Returns the clip top tween
	const Tween<float>* getClipTopTween() const;

	/// @copydoc Camera::getClipTopTween() const
	Tween<float>* getClipTopTween();

	/// Returns the clip near tween
	const Tween<float>* getClipNearTween() const;

	/// @copydoc Camera::getClipNearTween() const
	Tween<float>* getClipNearTween();

	/// Returns the clip far tween
	const Tween<float>* getClipFarTween() const;

	/// @copydoc Camera::getClipFarTween() const
	Tween<float>* getClipFarTween();

	/// Returns the view matrix tween
	const Tween<Matrix4>* getViewTween() const;

	/// @copydoc Camera::getViewTween() const
	Tween<Matrix4>* getViewTween();

	/// Returns the projection matrix tween
	const Tween<Matrix4>* getProjectionTween() const;

	/// @copydoc Camera::getProjectionTween() const
	Tween<Matrix4>* getProjectionTween();

	/// Returns the inverse projection tween
	const Tween<Matrix4>* getInverseProjectionTween() const;

	/// @copydoc Camera::getInverseProjectionTween() const
	Tween<Matrix4>* getInverseProjectionTween();

	/// Returns the view-projection tween
	const Tween<Matrix4>* getViewProjectionTween() const;

	/// @copydoc Camera::getViewProjectionTween() const
	Tween<Matrix4>* getViewProjectionTween();

	/// Returns the inverse view-projection tween
	const Tween<Matrix4>* getInverseViewProjectionTween() const;

	/// @copydoc Camera::getInverseViewProjectionTween() const
	Tween<Matrix4>* getInverseViewProjectionTween();

	/// Returns the view frustum tween
	const Tween<ViewFrustum>* getViewFrustumTween() const;

	/// @copydoc Camera::getViewFrustumTween() const
	Tween<ViewFrustum>* getViewFrustumTween();
	
private:
	virtual void transformed();
	void updateView();
	void updateProjection();
	void updateViewProjection();

	// These functions are somewhat hacky. They don't actually use the x and y parameters but rather use the state0 and state1 of other known tweens (such as the scene object's transform tween) to calculate the interpolated matrices.
	Matrix4 interpolateView(const Matrix4& x, const Matrix4& y, float a) const;
	Matrix4 interpolateProjection(const Matrix4& x, const Matrix4& y, float a) const;
	Matrix4 interpolateInverseProjection(const Matrix4& x, const Matrix4& y, float a) const;
	Matrix4 interpolateViewProjection(const Matrix4& x, const Matrix4& y, float a) const;
	Matrix4 interpolateInverseViewProjection(const Matrix4& x, const Matrix4& y, float a)const ;
	ViewFrustum interpolateViewFrustum(const ViewFrustum& x, const ViewFrustum& y, float a) const;

	bool cullingEnabled;
	const BoundingVolume* cullingMask;
	bool active;
	Compositor* compositor;
	std::size_t compositeIndex;

	bool orthographic;
	float fov;
	float aspectRatio;
	float clipLeft;
	float clipRight;
	float clipBottom;
	float clipTop;
	float clipNear;
	float clipFar;
	Matrix4 view;
	Matrix4 projection;
	Matrix4 inverseProjection;
	Matrix4 viewProjection;
	Matrix4 inverseViewProjection;
	ViewFrustum viewFrustum;
	
	Tween<float> fovTween;
	Tween<float> aspectRatioTween;
	Tween<float> clipLeftTween;
	Tween<float> clipRightTween;
	Tween<float> clipBottomTween;
	Tween<float> clipTopTween;
	Tween<float> clipNearTween;
	Tween<float> clipFarTween;
	Tween<Matrix4> viewTween;
	Tween<Matrix4> projectionTween;
	Tween<Matrix4> inverseProjectionTween;
	Tween<Matrix4> viewProjectionTween;
	Tween<Matrix4> inverseViewProjectionTween;
	Tween<ViewFrustum> viewFrustumTween;
};

inline void Camera::setActive(bool active)
{
	this->active = active;
}

inline void Camera::setCullingEnabled(bool enabled)
{
	this->cullingEnabled = enabled;
}

inline void Camera::setCullingMask(const BoundingVolume* mask)
{
	this->cullingMask = mask;
}

inline void Camera::setCompositor(Compositor* compositor)
{
	this->compositor = compositor;
}

inline void Camera::setCompositeIndex(std::size_t index)
{
	this->compositeIndex = index;
}

inline SceneObjectType Camera::getSceneObjectType() const
{
	return SceneObjectType::CAMERA;
}

inline bool Camera::isActive() const
{
	return active;
}

inline bool Camera::isCullingEnabled() const
{
	return cullingEnabled;
}

inline const BoundingVolume* Camera::getCullingMask() const
{
	return cullingMask;
}

inline const Compositor* Camera::getCompositor() const
{
	return compositor;
}

inline Compositor* Camera::getCompositor()
{
	return compositor;
}

inline std::size_t Camera::getCompositeIndex() const
{
	return compositeIndex;
}

inline float Camera::getFOV() const
{
	return fov;
}

inline float Camera::getAspectRatio() const
{
	return aspectRatio;
}

inline float Camera::getClipLeft() const
{
	return clipLeft;
}

inline float Camera::getClipRight() const
{
	return clipRight;
}

inline float Camera::getClipBottom() const
{
	return clipBottom;
}

inline float Camera::getClipTop() const
{
	return clipTop;
}

inline float Camera::getClipNear() const
{
	return clipNear;
}

inline float Camera::getClipFar() const
{
	return clipFar;
}

inline const Matrix4& Camera::getView() const
{
	return view;
}

inline const Matrix4& Camera::getProjection() const
{
	return projection;
}

inline const Matrix4& Camera::getInverseProjection() const
{
	return inverseProjection;
}

inline const Matrix4& Camera::getViewProjection() const
{
	return viewProjection;
}

inline const Matrix4& Camera::getInverseViewProjection() const
{
	return inverseViewProjection;
}

inline const ViewFrustum& Camera::getViewFrustum() const
{
	return viewFrustum;
}

inline const Tween<float>* Camera::getFOVTween() const
{
	return &fovTween;
}

inline Tween<float>* Camera::getFOVTween()
{
	return &fovTween;
}

inline const Tween<float>* Camera::getAspectRatioTween() const
{
	return &aspectRatioTween;
}

inline Tween<float>* Camera::getAspectRatioTween()
{
	return &aspectRatioTween;
}

inline const Tween<float>* Camera::getClipLeftTween() const
{
	return &clipLeftTween;
}

inline Tween<float>* Camera::getClipLeftTween()
{
	return &clipLeftTween;
}

inline const Tween<float>* Camera::getClipRightTween() const
{
	return &clipRightTween;
}

inline Tween<float>* Camera::getClipRightTween()
{
	return &clipRightTween;
}

inline const Tween<float>* Camera::getClipBottomTween() const
{
	return &clipBottomTween;
}

inline Tween<float>* Camera::getClipBottomTween()
{
	return &clipBottomTween;
}

inline const Tween<float>* Camera::getClipTopTween() const
{
	return &clipTopTween;
}

inline Tween<float>* Camera::getClipTopTween()
{
	return &clipTopTween;
}

inline const Tween<float>* Camera::getClipNearTween() const
{
	return &clipNearTween;
}

inline Tween<float>* Camera::getClipNearTween()
{
	return &clipNearTween;
}

inline const Tween<float>* Camera::getClipFarTween() const
{
	return &clipFarTween;
}

inline Tween<float>* Camera::getClipFarTween()
{
	return &clipFarTween;
}

inline const Tween<Matrix4>* Camera::getViewTween() const
{
	return &viewTween;
}

inline Tween<Matrix4>* Camera::getViewTween()
{
	return &viewTween;
}

inline const Tween<Matrix4>* Camera::getProjectionTween() const
{
	return &projectionTween;
}

inline Tween<Matrix4>* Camera::getProjectionTween()
{
	return &projectionTween;
}

inline const Tween<Matrix4>* Camera::getInverseProjectionTween() const
{
	return &inverseProjectionTween;
}

inline Tween<Matrix4>* Camera::getInverseProjectionTween()
{
	return &inverseProjectionTween;
}

inline const Tween<Matrix4>* Camera::getViewProjectionTween() const
{
	return &viewProjectionTween;
}

inline Tween<Matrix4>* Camera::getViewProjectionTween()
{
	return &viewProjectionTween;
}

inline const Tween<Matrix4>* Camera::getInverseViewProjectionTween() const
{
	return &inverseViewProjectionTween;
}

inline Tween<Matrix4>* Camera::getInverseViewProjectionTween()
{
	return &inverseViewProjectionTween;
}

inline const Tween<ViewFrustum>* Camera::getViewFrustumTween() const
{
	return &viewFrustumTween;
}

inline Tween<ViewFrustum>* Camera::getViewFrustumTween()
{
	return &viewFrustumTween;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_CAMERA_HPP

