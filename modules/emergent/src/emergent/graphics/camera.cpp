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

#include <emergent/graphics/camera.hpp>
#include <emergent/math/math.hpp>

namespace Emergent
{

Camera::Camera():
	orthographic(true),
	view(1.0f),
	projection(1.0f),
	inverseProjection(1.0f),
	viewProjection(1.0f),
	inverseViewProjection(1.0f),
	viewFrustum(),
	cullingMask(&viewFrustum),
	active(true),
	compositor(nullptr),
	compositeIndex(0)
{
	registerSubstepTween(&fov);
	registerSubstepTween(&aspectRatio);
	registerSubstepTween(&clipLeft);
	registerSubstepTween(&clipRight);
	registerSubstepTween(&clipBottom);
	registerSubstepTween(&clipTop);
	registerSubstepTween(&clipNear);
	registerSubstepTween(&clipFar);

	fov.setState1(glm::radians(90.0f));
	aspectRatio.setState1(1.0f);
	clipLeft.setState1(-1.0f);
	clipRight.setState1(1.0f);
	clipBottom.setState1(-1.0f);
	clipTop.setState1(1.0f);
	clipNear.setState1(-1.0f);
	clipFar.setState1(1.0f);
	resetSubstepTweens();
}

void Camera::setPerspective(float fov, float aspectRatio, float near, float far)
{
	orthographic = false;

	this->fov.setState1(fov);
	this->aspectRatio.setState1(aspectRatio);
	this->clipNear.setState1(near);
	this->clipFar.setState1(far);
	
	projection = glm::perspective(fov, aspectRatio, near, far);
	updateProjection();
}

void Camera::setOrthographic(float left, float right, float bottom, float top, float near, float far)
{
	orthographic = true;
	
	this->clipLeft.setState1(left);
	this->clipRight.setState1(right);
	this->clipBottom.setState1(bottom);
	this->clipTop.setState1(top);
	this->clipNear.setState1(near);
	this->clipFar.setState1(far);
	
	projection = glm::ortho(left, right, bottom, top, near, far);
	updateProjection();
}

void Camera::lookAt(const Vector3& translation, const Vector3& target, const Vector3& up)
{
	Vector3 forward = glm::normalize(target - translation);
	
	Transform transform = getTransform();
	transform.translation = translation;
	transform.rotation = lookRotation(forward, up);
	
	setTransform(transform);
}

Vector3 Camera::project(const Vector3& object, const Vector4& viewport) const
{
	Vector4 result = viewProjection * Vector4(object, 1.0f);
	result.x = (result.x / result.w) * 0.5f + 0.5f;
	result.y = (result.y / result.w) * 0.5f + 0.5f;
	result.z = (result.z / result.w) * 0.5f + 0.5f;
	
	result.x = result.x * viewport[2] + viewport[0];
	result.y = result.y * viewport[3] + viewport[1];
	
	return Vector3(result);
}

Vector3 Camera::unproject(const Vector3& window, const Vector4& viewport) const
{
	Vector4 result;
	
	result.x = ((window.x - viewport[0]) / viewport[2]) * 2.0f - 1.0f;
	result.y = ((window.y - viewport[1]) / viewport[3]) * 2.0f - 1.0f;
	result.z = window.z * 2.0f - 1.0f;
	result.w = 1.0f;
	
	result = inverseViewProjection * result;
	return Vector3(result) / result.w;
}

void Camera::transformed()
{
	updateView();
}

void Camera::updateView()
{
	view = glm::lookAt(getTranslation(), getTranslation() - getForward(), getUp());
	viewFrustum.setViewMatrix(view);
	updateViewProjection();
}

void Camera::updateProjection()
{
	inverseProjection = glm::inverse(projection);
	viewFrustum.setProjectionMatrix(projection);
	updateViewProjection();
}

void Camera::updateViewProjection()
{
	viewProjection = projection * view;
	inverseViewProjection = glm::inverse(viewProjection);
}

} // namespace Emergent
