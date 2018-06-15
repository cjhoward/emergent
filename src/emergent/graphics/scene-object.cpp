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

#include <emergent/graphics/scene-object.hpp>

namespace Emergent
{

SceneObject::SceneObject():
	active(true),
	transform(Transform::getIdentity()),
	forward(0.0f, 0.0f, -1.0f),
	up(0.0f, 1.0f, 0.0f),
	right(1.0f, 0.0f, 0.0f),
	matrix(1.0f)
{}

SceneObject::~SceneObject()
{}

void SceneObject::setActive(bool active)
{
	this->active = active;
}

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

void SceneObject::updateBounds()
{
	bounds = calculateBounds();
}

AABB SceneObject::calculateBounds() const
{
	return AABB(getTranslation(), getTranslation());
}

void SceneObject::transformed()
{}

void SceneObject::updateTransform()
{
	forward = glm::normalize(getRotation() * Vector3(0.0f, 0.0f, -1.0f));
	up = glm::normalize(getRotation() * Vector3(0.0f, 1.0f, 0.0f));
	right = glm::normalize(glm::cross(forward, up));
	up = glm::cross(right, forward);
	
	matrix = transform.toMatrix();
	transformed();
	bounds = calculateBounds();
}

} // namespace Emergent

