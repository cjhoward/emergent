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

#include <emergent/graphics/scene-layer.hpp>
#include <emergent/graphics/scene.hpp>
#include <emergent/graphics/scene-object.hpp>
#include <emergent/utility/step-interpolator.hpp>

namespace Emergent
{

SceneLayer::SceneLayer(Scene* scene, std::size_t index):
	scene(scene),
	index(index)
{}

void SceneLayer::addObject(SceneObject* object)
{
	objectList.push_back(object);
	objectMap[object->getSceneObjectType()].push_back(object);
	registerSubstepTweens(object);
}

void SceneLayer::removeObject(SceneObject* object)
{
	objectList.remove(object);
	objectMap[object->getSceneObjectType()].remove(object);
	unregisterSubstepTweens(object);
}

void SceneLayer::removeObjects()
{
	for (SceneObject* object: objectList)
	{
		unregisterSubstepTweens(object);
	}

	objectList.clear();
	objectMap.clear();
}

void SceneLayer::removeObjects(SceneObjectType type)
{
	auto it = objectMap.find(type);
	if (it != objectMap.end())
	{
		for (SceneObject* object: it->second)
		{
			objectList.remove(object);
			unregisterSubstepTweens(object);
		}
		
		objectMap.erase(it);
	}
}

const std::list<SceneObject*>* SceneLayer::getObjects(SceneObjectType type) const
{
	auto it = objectMap.find(type);
	if (it != objectMap.end())
	{
		return &(it->second);
	}
	
	return nullptr;
}

void SceneLayer::registerSubstepTweens(SceneObject* object)
{
	const std::list<TweenBase*>* substepTweens = object->getSubstepTweens();
	for (TweenBase* variable: *substepTweens)
	{
		scene->getInterpolator()->addVariable(variable);
	}
}

void SceneLayer::unregisterSubstepTweens(SceneObject* object)
{
	const std::list<TweenBase*>* substepTweens = object->getSubstepTweens();
	for (TweenBase* variable: *substepTweens)
	{
		scene->getInterpolator()->removeVariable(variable);
	}
}

} // namespace Emergent

