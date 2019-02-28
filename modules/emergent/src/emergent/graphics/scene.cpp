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
#include <emergent/graphics/scene-layer.hpp>

namespace Emergent
{

Scene::Scene(StepInterpolator* interpolator):
	interpolator(interpolator)
{}

Scene::~Scene()
{
	removeLayers();
}

SceneLayer* Scene::addLayer()
{
	SceneLayer* layer = new SceneLayer(this, layers.size());
	layers.push_back(layer);
	return layer;
}

void Scene::removeLayers()
{
	for (SceneLayer* layer: layers)
	{
		delete layer;
	}
	
	layers.clear();
}

} // namespace Emergent

