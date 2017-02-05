/*
 * Copyright (C) 2017  Christopher J. Howard
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

#ifndef EMERGENT_GRAPHICS_SCENE_LAYER_HPP
#define EMERGENT_GRAPHICS_SCENE_LAYER_HPP

#include <list>
#include <map>

namespace Emergent
{

class Scene;
class SceneObject;
enum class SceneObjectType;

/**
 * A layer of a three-dimensional scene, containing objects which are composited together.
 *
 * @ingroup graphics
 */
class SceneLayer
{
public:
	/**
	 * Adds an object to the layer.
	 *
	 * @param object Pointer to the scene object to be added.
	 */
	void addObject(SceneObject* object);
	
	/**
	 * Removes an object from the layer.
	 *
	 * @param object Specifies a pointer to the scene object to be removed.
	 */
	void removeObject(SceneObject* object);
	
	/**
	 * Removes all objects from the layer.
	 */
	void removeObjects();
	
	/**
	 * Removes all objects of the specified type from the layer.
	 *
	 * @param type Specifies the type of objects to be removed.
	 */
	void removeObjects(SceneObjectType type);
	
	/**
	 * Returns a pointer to the parent scene.
	 */
	const Scene* getScene() const;
	
	/// @copydoc SceneLayer::getScene() const
	Scene* getScene();
	
	/**
	 * Returns the index of this layer in relation to its parent scene's layers.
	 */
	std::size_t getIndex() const;
	
	/**
	 * Returns a pointer to a list of all objects in the layer.
	 */
	const std::list<SceneObject*>* getObjects() const;
	
	/**
	 * Returns a pointer to a list of all objects in the layer with the specified type.
	 *
	 * @param type Specifies the type of objects to return.
	 */
	const std::list<SceneObject*>* getObjects(SceneObjectType type) const;
	
	//std::list<SceneObject*> query(const BoundingVolume& volume);

private:
	friend class Scene;
	
	/**
	 * Creates an instance of SceneLayer.
	 *
	 * @param scene Pointer to the parent scene.
	 * @param index Index of the layer in relation to its parent scene's layers.
	 */
	SceneLayer(Scene* scene, std::size_t index);
	
	Scene* scene;
	std::size_t index;
	std::list<SceneObject*> objectList;
	std::map<SceneObjectType, std::list<SceneObject*>> objectMap;
};

inline const Scene* SceneLayer::getScene() const
{
	return scene;
}

inline Scene* SceneLayer::getScene()
{
	return scene;
}

inline std::size_t SceneLayer::getIndex() const
{
	return index;
}

inline const std::list<SceneObject*>* SceneLayer::getObjects() const
{
	return &objectList;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SCENE_LAYER_HPP

