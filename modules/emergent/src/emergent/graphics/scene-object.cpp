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
#include <emergent/utility/step-interpolator.hpp>

namespace Emergent
{

SceneObject::SceneObject():
	active(true)
{
	registerSubstepTween(&bounds);
	registerSubstepTween(&transform);
	registerSubstepTween(&forward);
	registerSubstepTween(&up);
	registerSubstepTween(&right);

	transform.setState1(Transform::getIdentity());
	forward.setState1(Vector3(0, 0, -1));
	up.setState1(Vector3(0, 1, 0));
	right.setState1(Vector3(1, 0, 0));
	matrix = Matrix4(1.0f);
	resetSubstepTweens();
}

SceneObject::~SceneObject()
{}

void SceneObject::setActive(bool active)
{
	this->active = active;
}

void SceneObject::setTransform(const Transform& transform)
{
	this->transform.setState1(transform);
	updateTransform();
}

void SceneObject::setTranslation(const Vector3& translation)
{
	transform.setState1(Transform(translation, transform.getState1().rotation, transform.getState1().scale));
	updateTransform();
}

void SceneObject::setRotation(const Quaternion& rotation)
{
	transform.setState1(Transform(transform.getState1().translation, rotation, transform.getState1().scale));
	updateTransform();
}

void SceneObject::setScale(const Vector3& scale)
{
	transform.setState1(Transform(transform.getState1().translation, transform.getState1().rotation, scale));
	updateTransform();
}

void SceneObject::resetSubstepTweens()
{
	for (TweenBase* variable: substepTweens)
	{
		variable->update();
	}
}

void SceneObject::updateBounds()
{
	bounds.setState1(calculateBounds());
}

void SceneObject::registerSubstepTween(TweenBase* variable)
{
	substepTweens.push_back(variable);
}

AABB SceneObject::calculateBounds() const
{
	return AABB(getTranslation(), getTranslation());
}

void SceneObject::transformed()
{}

void SceneObject::updateTransform()
{
	forward.setState1(glm::normalize(getRotation() * Vector3(0.0f, 0.0f, -1.0f)));
	up.setState1(glm::normalize(getRotation() * Vector3(0.0f, 1.0f, 0.0f)));
	right.setState1(glm::normalize(glm::cross(forward.getState1(), up.getState1())));
	up.setState1(glm::cross(right.getState1(), forward.getState1()));
	
	matrix = transform.getState1().toMatrix();
	transformed();

	updateBounds();
}

} // namespace Emergent

