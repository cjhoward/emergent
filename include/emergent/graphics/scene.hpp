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

#ifndef EMERGENT_GRAPHICS_SCENE_HPP
#define EMERGENT_GRAPHICS_SCENE_HPP

#include <vector>

namespace Emergent
{

class SceneLayer;

/**
 * A three-dimensional scene consisting of one or more scene layers.
 *
 * @ingroup graphics
 */
class Scene
{
public:
	/**
	 * Creates an instance of Scene.
	 */
	Scene();
	
	/**
	 * Destroys an instance of Scene.
	 */
	~Scene();
	
	/**
	 * Adds a layer to the scene.
	 *
	 * @return Pointer to the added scene.
	 */
	SceneLayer* addLayer();
	
	/**
	 * Removes all layers from the scene.
	 */
	void removeLayers();
	
	/**
	 * Returns the number of layers in the scene.
	 */
	std::size_t getLayerCount() const;
	
	/**
	 * Returns the layer at the specified index.
	 *
	 * @param index Specifies the index of a layer.
	 * @return Pointer to the layer at the specified index.
	 */
	const SceneLayer* getLayer(std::size_t index) const;
	
	/// @copydoc Scene::getLayer(std::size_t) const
	SceneLayer* getLayer(std::size_t index);
	
private:
	std::vector<SceneLayer*> layers;
};

inline std::size_t Scene::getLayerCount() const
{
	return layers.size();
}

inline const SceneLayer* Scene::getLayer(std::size_t index) const
{
	return layers[index];
}

inline SceneLayer* Scene::getLayer(std::size_t index)
{
	return layers[index];
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SCENE_HPP

