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

#ifndef EMERGENT_GRAPHICS_SCENE_HPP
#define EMERGENT_GRAPHICS_SCENE_HPP

#include <list>
#include <map>

namespace Emergent
{

class SceneObject;
class StepInterpolator;
enum class SceneObjectType;

/**
 * A three-dimensional scene containing scene objects.
 *
 * @ingroup graphics
 */
class Scene
{
public:
	/**
	 * Creates an instance of Scene.
	 *
	 * @param interpolator The interpolator which will be used to interpolated scene object variables.
	 */
	Scene(StepInterpolator* interpolator);
	
	/**
	 * Destroys an instance of Scene.
	 */
	~Scene();
	
	/**
	 * Adds an object to the scene.
	 *
	 * @param object Pointer to the scene object to be added.
	 */
	void addObject(SceneObject* object);
	
	/**
	 * Removes an object from the scene.
	 *
	 * @param object Specifies a pointer to the scene object to be removed.
	 */
	void removeObject(SceneObject* object);
	
	/**
	 * Removes all objects from the scene.
	 */
	void removeObjects();
	
	/**
	 * Removes all objects of the specified type from the scene.
	 *
	 * @param type Specifies the type of objects to be removed.
	 */
	void removeObjects(SceneObjectType type);


	/// Returns the scene's interpolator.
	const StepInterpolator* getInterpolator() const;

	/// @copydoc Scene::getInterpolator() const
	StepInterpolator* getInterpolator();

	/**
	 * Returns a pointer to a list of all objects in the scene.
	 */
	const std::list<SceneObject*>* getObjects() const;
	
	/**
	 * Returns a pointer to a list of all objects in the scene with the specified type.
	 *
	 * @param type Specifies the type of objects to return.
	 */
	const std::list<SceneObject*>* getObjects(SceneObjectType type) const;

private:
	StepInterpolator* interpolator;
	void registerTweens(SceneObject* object);
	void unregisterTweens(SceneObject* object);
	
	std::list<SceneObject*> objectList;
	std::map<SceneObjectType, std::list<SceneObject*>> objectMap;
};

inline const StepInterpolator* Scene::getInterpolator() const
{
	return interpolator;
}

inline StepInterpolator* Scene::getInterpolator()
{
	return interpolator;
}

inline const std::list<SceneObject*>* Scene::getObjects() const
{
	return &objectList;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SCENE_HPP

