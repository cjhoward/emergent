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

#include <emergent/graphics/scene.hpp>
#include <emergent/animation/step-interpolator.hpp>
#include <emergent/graphics/scene-object.hpp>

namespace Emergent
{

Scene::Scene(StepInterpolator* interpolator):
	interpolator(interpolator)
{}

Scene::~Scene()
{}

void Scene::addObject(SceneObject* object)
{
	objectList.push_back(object);
	objectMap[object->getSceneObjectType()].push_back(object);
	registerTweens(object);
}

void Scene::removeObject(SceneObject* object)
{
	objectList.remove(object);
	objectMap[object->getSceneObjectType()].remove(object);
	unregisterTweens(object);
}

void Scene::removeObjects()
{
	for (SceneObject* object: objectList)
	{
		unregisterTweens(object);
	}

	objectList.clear();
	objectMap.clear();
}

void Scene::removeObjects(SceneObjectType type)
{
	auto it = objectMap.find(type);
	if (it != objectMap.end())
	{
		for (SceneObject* object: it->second)
		{
			objectList.remove(object);
			unregisterTweens(object);
		}
		
		objectMap.erase(it);
	}
}

const std::list<SceneObject*>* Scene::getObjects(SceneObjectType type) const
{
	auto it = objectMap.find(type);
	if (it != objectMap.end())
	{
		return &(it->second);
	}
	
	return nullptr;
}

void Scene::registerTweens(SceneObject* object)
{
	const std::list<TweenBase*>* tweens = object->getTweens();
	for (TweenBase* tween: *tweens)
	{
		interpolator->addTween(tween);
	}
}

void Scene::unregisterTweens(SceneObject* object)
{
	const std::list<TweenBase*>* tweens = object->getTweens();
	for (TweenBase* tween: *tweens)
	{
		interpolator->removeTween(tween);
	}
}

} // namespace Emergent

