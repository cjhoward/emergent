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
#include <emergent/math/interpolation.hpp>
#include <emergent/math/math.hpp>

namespace Emergent
{

Camera::Camera():
	cullingEnabled(true),
	cullingMask(nullptr),
	active(true),
	compositor(nullptr),
	compositeIndex(0),
	orthographic(true),
	fov(glm::radians(90.0f)),
	aspectRatio(1.0f),
	clipLeft(-1.0f),
	clipRight(1.0f),
	clipBottom(-1.0f),
	clipTop(1.0f),
	clipNear(-1.0f),
	clipFar(1.0f),
	view(1.0f),
	projection(1.0f),
	inverseProjection(1.0f),
	viewProjection(1.0f),
	inverseViewProjection(1.0f),
	viewFrustum(),
	fovTween(&fov, lerp<float>),
	aspectRatioTween(&aspectRatio, lerp<float>),
	clipLeftTween(&clipLeft, lerp<float>),
	clipRightTween(&clipRight, lerp<float>),
	clipBottomTween(&clipBottom, lerp<float>),
	clipTopTween(&clipTop, lerp<float>),
	clipNearTween(&clipNear, lerp<float>),
	clipFarTween(&clipFar, lerp<float>),
	viewTween(&view, std::bind(&Camera::interpolateView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
	projectionTween(&projection, std::bind(&Camera::interpolateProjection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
	inverseProjectionTween(&inverseProjection, std::bind(&Camera::interpolateInverseProjection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
	viewProjectionTween(&viewProjection, std::bind(&Camera::interpolateViewProjection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
	inverseViewProjectionTween(&inverseViewProjection, std::bind(&Camera::interpolateInverseViewProjection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
	viewFrustumTween(&viewFrustum, std::bind(&Camera::interpolateViewFrustum, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
{
	// WARNING: This order is important (see interpolation functions)
	registerTween(&fovTween);
	registerTween(&aspectRatioTween);
	registerTween(&clipLeftTween);
	registerTween(&clipRightTween);
	registerTween(&clipBottomTween);
	registerTween(&clipTopTween);
	registerTween(&clipNearTween);
	registerTween(&clipFarTween);
	registerTween(&viewTween);
	registerTween(&projectionTween);
	registerTween(&inverseProjectionTween);
	registerTween(&viewProjectionTween);
	registerTween(&inverseViewProjectionTween);
	registerTween(&viewFrustumTween);
}

void Camera::setPerspective(float fov, float aspectRatio, float near, float far)
{
	orthographic = false;

	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->clipNear = near;
	this->clipFar = far;
	
	projection = glm::perspective(fov, aspectRatio, near, far);
	updateProjection();
}

void Camera::setOrthographic(float left, float right, float bottom, float top, float near, float far)
{
	orthographic = true;
	
	this->clipLeft = left;
	this->clipRight = right;
	this->clipBottom = bottom;
	this->clipTop = top;
	this->clipNear = near;
	this->clipFar = far;
	
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

Matrix4 Camera::interpolateView(const Matrix4& x, const Matrix4& y, float a) const
{
	// WARNING: Assumes theses tweens have been interpolated beforehand
	const Vector3& translationSubstate = getTransformTween()->getSubstate().translation;
	const Vector3& forwardSubstate = getForwardTween()->getSubstate();
	const Vector3& upSubstate = getUpTween()->getSubstate();

	return glm::lookAt(translationSubstate, translationSubstate - forwardSubstate, upSubstate);
}

Matrix4 Camera::interpolateProjection(const Matrix4& x, const Matrix4& y, float a) const
{
	if (orthographic)
	{
		// WARNING: Assumes theses tweens have been interpolated beforehand
		return glm::ortho(clipLeftTween.getSubstate(), clipRightTween.getSubstate(), clipBottomTween.getSubstate(), clipTopTween.getSubstate(), clipNearTween.getSubstate(), clipFarTween.getSubstate());
	}
	else
	{
		// WARNING: Assumes theses tweens have been interpolated beforehand
		return glm::perspective(fovTween.getSubstate(), aspectRatioTween.getSubstate(), clipNearTween.getSubstate(), clipFarTween.getSubstate());
	}
}

Matrix4 Camera::interpolateInverseProjection(const Matrix4& x, const Matrix4& y, float a) const
{
	// WARNING: Assumes this tween has been interpolated beforehand
	return glm::inverse(inverseProjectionTween.getSubstate());
}

Matrix4 Camera::interpolateViewProjection(const Matrix4& x, const Matrix4& y, float a) const
{
	// WARNING: Assumes theses tweens have been interpolated beforehand
	return projectionTween.getSubstate() * viewTween.getSubstate();
}

Matrix4 Camera::interpolateInverseViewProjection(const Matrix4& x, const Matrix4& y, float a) const
{
	// WARNING: Assumes this tween has been interpolated beforehand
	return glm::inverse(viewProjectionTween.getSubstate());
}

ViewFrustum Camera::interpolateViewFrustum(const ViewFrustum& x, const ViewFrustum& y, float a) const
{
	// WARNING: Assumes theses tweens have been interpolated beforehand
	ViewFrustum  frustum;
	frustum.setMatrices(viewTween.getSubstate(), projectionTween.getSubstate());
	return frustum;
}

} // namespace Emergent
