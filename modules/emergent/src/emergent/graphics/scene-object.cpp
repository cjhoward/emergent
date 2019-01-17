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

#include <emergent/animation/step-interpolator.hpp>
#include <emergent/graphics/scene-object.hpp>
#include <emergent/math/interpolation.hpp>

namespace Emergent
{

SceneObject::SceneObject():
	active(true),
	cullingEnabled(true),
	cullingMask(nullptr),
	bounds(transform.translation, transform.translation),
	transform(Transform::getIdentity()),
	forward(0, 0, -1),
	up(0, 1, 0),
	right(1, 0, 0),
	matrix(1.0f),
	boundsTween(&bounds, lerp<AABB>),
	transformTween(&transform, lerp<Transform>),
	forwardTween(&forward, std::bind(&SceneObject::interpolateForward, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
	upTween(&up, std::bind(&SceneObject::interpolateUp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
	rightTween(&right, std::bind(&SceneObject::interpolateRight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
	matrixTween(&matrix, std::bind(&SceneObject::interpolateMatrix, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
{
	// WARNING: The order of registration is important (see interpolation functions)
	registerTween(&boundsTween);
	registerTween(&transformTween);
	registerTween(&forwardTween);
	registerTween(&upTween);
	registerTween(&rightTween);
	registerTween(&matrixTween);
}

SceneObject::~SceneObject()
{}

void SceneObject::setTransform(const Transform& transform)
{
	this->transform = transform;
	updateTransform();
}

void SceneObject::setTranslation(const Vector3& translation)
{
	transform.translation = translation;
	updateTransform();
}

void SceneObject::setRotation(const Quaternion& rotation)
{
	transform.rotation = rotation;
	updateTransform();
}

void SceneObject::setScale(const Vector3& scale)
{
	transform.scale = scale;
	updateTransform();
}

void SceneObject::resetTweens()
{
	for (TweenBase* tween: tweens)
	{
		tween->reset();
	}
}

void SceneObject::updateBounds()
{
	bounds = calculateBounds();
}

void SceneObject::registerTween(TweenBase* variable)
{
	tweens.push_back(variable);
}

AABB SceneObject::calculateBounds() const
{
	return AABB(transform.translation, transform.translation);
}

void SceneObject::transformed()
{}

void SceneObject::updateTransform()
{
	forward = glm::normalize(transform.rotation * Vector3(0.0f, 0.0f, -1.0f));
	up = glm::normalize(transform.rotation * Vector3(0.0f, 1.0f, 0.0f));
	right = glm::normalize(glm::cross(forward, up));
	up = glm::cross(right, forward);
	
	matrix = transform.toMatrix();
	transformed();

	updateBounds();
}

Vector3 SceneObject::interpolateForward(const Vector3& x, const Vector3& y, float a) const
{
	// WARNING: Assumes this tween has been interpolated beforehand
	return glm::normalize(transformTween.getSubstate().rotation * Vector3(0.0f, 0.0f, -1.0f));
}

Vector3 SceneObject::interpolateUp(const Vector3& x, const Vector3& y, float a) const
{
	// WARNING: Assumes these tweens have been interpolated beforehand
	Vector3 upSubstate = glm::normalize(transformTween.getSubstate().rotation * Vector3(0.0f, 1.0f, 0.0f));
	Vector3 rightSubstate = glm::normalize(glm::cross(forwardTween.getSubstate(), upSubstate));
	return glm::cross(rightSubstate, forwardTween.getSubstate());
}

Vector3 SceneObject::interpolateRight(const Vector3& x, const Vector3& y, float a) const
{
	// WARNING: Assumes these tweens have been interpolated beforehand
	Vector3 upSubstate = glm::normalize(transformTween.getSubstate().rotation * Vector3(0.0f, 1.0f, 0.0f));
	return glm::normalize(glm::cross(forwardTween.getSubstate(), upSubstate));
}

Matrix4 SceneObject::interpolateMatrix(const Matrix4& x, const Matrix4& y, float a) const
{
	// WARNING: Assumes this tween has been interpolated beforehand
	return transformTween.getSubstate().toMatrix();
}

} // namespace Emergent

