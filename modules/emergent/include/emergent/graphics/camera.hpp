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

#include <emergent/graphics/scene-object.hpp>
#include <emergent/math/types.hpp>
#include <emergent/geometry/view-frustum.hpp>

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
	
	
	void setCullingMask(const BoundingVolume* mask);
	
	void setActive(bool active);
	
	void setCompositor(Compositor* compositor);
	
	// Sets the composite index, which determines the order in which cameras in the scene are composited.
	void setCompositeIndex(std::size_t index);
	
	virtual SceneObjectType getSceneObjectType() const;
	
	float getFOV() const;
	float getAspectRatio() const;
	float getClipLeft() const;
	float getClipRight() const;
	float getClipBottom() const;
	float getClipTop() const;
	float getClipNear() const;
	float getClipFar() const;
	const Matrix4& getView() const;
	const Matrix4& getProjection() const;
	const Matrix4& getInverseProjection() const;
	const Matrix4& getViewProjection() const;
	const Matrix4& getInverseViewProjection() const;
	const ViewFrustum& getViewFrustum() const;
	
	float getSubstepFOV() const;
	float getSubstepAspectRatio() const;
	float getSubstepClipLeft() const;
	float getSubstepClipRight() const;
	float getSubstepClipBottom() const;
	float getSubstepClipTop() const;
	float getSubstepClipNear() const;
	float getSubstepClipFar() const;
	Matrix4 getSubstepView() const;
	Matrix4 getSubstepProjection() const;
	Matrix4 getSubstepInverseProjection() const;
	Matrix4 getSubstepViewProjection() const;
	Matrix4 getSubstepInverseViewProjection() const;
	ViewFrustum getSubstepViewFrustum() const;

	const BoundingVolume* getCullingMask() const;
	bool isActive() const;
	const Compositor* getCompositor() const;
	Compositor* getCompositor();
	std::size_t getCompositeIndex() const;
	
private:
	virtual void transformed();
	
	void updateView();
	void updateProjection();
	void updateViewProjection();

	bool orthographic;
	Tween<float, lerp<float>> fov;
	Tween<float, lerp<float>> aspectRatio;
	Tween<float, lerp<float>> clipLeft;
	Tween<float, lerp<float>> clipRight;
	Tween<float, lerp<float>> clipBottom;
	Tween<float, lerp<float>> clipTop;
	Tween<float, lerp<float>> clipNear;
	Tween<float, lerp<float>> clipFar;
	Matrix4 view;
	Matrix4 projection;
	Matrix4 inverseProjection;
	Matrix4 viewProjection;
	Matrix4 inverseViewProjection;
	ViewFrustum viewFrustum;
	
	const BoundingVolume* cullingMask;
	bool active;
	Compositor* compositor;
	std::size_t compositeIndex;
};

inline void Camera::setActive(bool active)
{
	this->active = active;
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

inline float Camera::getFOV() const
{
	return fov.getState1();
}

inline float Camera::getAspectRatio() const
{
	return aspectRatio.getState1();
}

inline float Camera::getClipLeft() const
{
	return clipLeft.getState1();
}

inline float Camera::getClipRight() const
{
	return clipRight.getState1();
}

inline float Camera::getClipBottom() const
{
	return clipBottom.getState1();
}

inline float Camera::getClipTop() const
{
	return clipTop.getState1();
}

inline float Camera::getClipNear() const
{
	return clipNear.getState1();
}

inline float Camera::getClipFar() const
{
	return clipFar.getState1();
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

inline float Camera::getSubstepFOV() const
{
	return fov.getSubstate();
}

inline float Camera::getSubstepAspectRatio() const
{
	return aspectRatio.getSubstate();
}

inline float Camera::getSubstepClipLeft() const
{
	return clipLeft.getSubstate();
}

inline float Camera::getSubstepClipRight() const
{
	return clipRight.getSubstate();
}

inline float Camera::getSubstepClipBottom() const
{
	return clipBottom.getSubstate();
}

inline float Camera::getSubstepClipTop() const
{
	return clipTop.getSubstate();
}

inline float Camera::getSubstepClipNear() const
{
	return clipNear.getSubstate();
}

inline float Camera::getSubstepClipFar() const
{
	return clipFar.getSubstate();
}

inline Matrix4 Camera::getSubstepView() const
{
	return glm::lookAt(getSubstepTranslation(), getSubstepTranslation() - getSubstepForward(), getSubstepUp());
}

inline Matrix4 Camera::getSubstepProjection() const
{
	if (orthographic)
	{
		return glm::ortho(clipLeft.getSubstate(), clipRight.getSubstate(), clipBottom.getSubstate(), clipTop.getSubstate(), clipNear.getSubstate(), clipFar.getSubstate());
	}
	else
	{
		return glm::perspective(getSubstepFOV(), getSubstepAspectRatio(), getSubstepClipNear(), getSubstepClipFar());
	}
}

inline Matrix4 Camera::getSubstepInverseProjection() const
{
	return glm::inverse(getSubstepProjection());
}

inline Matrix4 Camera::getSubstepViewProjection() const
{
	return getSubstepProjection() * getSubstepView();
}

inline Matrix4 Camera::getSubstepInverseViewProjection() const
{
	return glm::inverse(getSubstepViewProjection());
}

inline ViewFrustum Camera::getSubstepViewFrustum() const
{
	ViewFrustum frustum;
	frustum.setMatrices(getSubstepView(), getSubstepProjection());
	return frustum;
}

inline const BoundingVolume* Camera::getCullingMask() const
{
	return cullingMask;
}

inline bool Camera::isActive() const
{
	return active;
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

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_CAMERA_HPP
