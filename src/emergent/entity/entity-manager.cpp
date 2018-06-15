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

#include <emergent/entity/entity-manager.hpp>

namespace Emergent
{

EntityManager::EntityManager()
{}

EntityManager::~EntityManager()
{}

EntityID EntityManager::createTemplate()
{
	return templateIDPool.reserveNextID();
}

bool EntityManager::createTemplate(EntityID templateID)
{
	if (templateIDPool.isReserved(templateID))
	{
		return false;
	}

	templateIDPool.reserveID(templateID);
	
	return true;
}

bool EntityManager::destroyTemplate(EntityID templateID)
{
	if (!templateIDPool.isReserved(templateID))
	{
		return false;
	}

	// Free template components
	ComponentMap* components = templateComponentManager.getComponents(templateID);
	for (auto it = components->begin(); it != components->end(); it = components->begin())
	{
		Component* component = it->second;
		templateComponentManager.removeComponent(templateID, component->getComponentType());
		delete component;
	}

	// Free template ID
	templateIDPool.freeID(templateID);

	return true;
}

EntityID EntityManager::createInstance()
{
	return instanceIDPool.reserveNextID();
}

EntityID EntityManager::createInstance(EntityID templateID)
{
	EntityID instanceID = instanceIDPool.reserveNextID();
	
	applyTemplate(templateID, instanceID);
	
	return instanceID;
}

bool EntityManager::createInstance(EntityID templateID, EntityID instanceID)
{
	if (instanceIDPool.isReserved(instanceID))
	{
		return false;
	}

	instanceIDPool.reserveID(instanceID);

	applyTemplate(templateID, instanceID);
	
	return true;
}

bool EntityManager::destroyInstance(EntityID instanceID)
{
	if (!instanceIDPool.isReserved(instanceID))
	{
		return false;
	}

	// Free instance components
	ComponentMap* components = instanceComponentManager.getComponents(instanceID);
	for (auto it = components->begin(); it != components->end(); it = components->begin())
	{
		Component* component = it->second;
		instanceComponentManager.removeComponent(instanceID, component->getComponentType());
		delete component;
	}

	// Free instance ID
	instanceIDPool.freeID(instanceID);

	return true;
}

void EntityManager::applyTemplate(EntityID templateID, EntityID instanceID)
{
	const ComponentMap* components = templateComponentManager.getComponents(templateID);
	if (components)
	{
		for (auto it = (*components).begin(); it != (*components).end(); ++it)
		{
			Component* component = it->second->clone();
			instanceComponentManager.addComponent(instanceID, component);
		}
	}
}

} // namespace Emergent

