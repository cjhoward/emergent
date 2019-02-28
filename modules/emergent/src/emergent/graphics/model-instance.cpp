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

#include <emergent/graphics/model-instance.hpp>
#include <emergent/graphics/model.hpp>

namespace Emergent
{

ModelInstance::ModelInstance(const Model* model):
	model(model),
	pose(nullptr)
{}

ModelInstance::ModelInstance():
	model(nullptr),
	pose(nullptr)
{}

void ModelInstance::setModel(const Model* model)
{
	this->model = model;

	// Resize material slots
	materialSlots.resize(model->getGroupCount());
	for (std::size_t i = 0; i < model->getGroupCount(); ++i)
	{
		materialSlots[i] = nullptr;
	}
	resetMaterialSlots();

	updateBounds();
}

void ModelInstance::setMaterialSlot(std::size_t index, Material* material)
{
	materialSlots[index] = material;
}

void ModelInstance::resetMaterialSlots()
{
	for (std::size_t i = 0; i < model->getGroupCount(); ++i)
	{
		materialSlots[i] = nullptr;
	}
}

AABB ModelInstance::calculateBounds() const
{
	if (model)
	{
		return model->getBounds().transformed(getTransform());
	}
	
	return AABB(getTranslation(), getTranslation());
}

} // namespace Emergent

