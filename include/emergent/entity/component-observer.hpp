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

#ifndef EMERGENT_ENTITY_COMPONENT_OBSERVER_HPP
#define EMERGENT_ENTITY_COMPONENT_OBSERVER_HPP

#include <emergent/entity/entity-id.hpp>

namespace Emergent
{

class Component;
class ComponentManager;

/**
 * Abstract base class for component observers.
 *
 * @ingroup entity
 */
class ComponentObserver
{
public:
	/**
	 * Destroys an instance of ComponentObserver.
	 */
	virtual ~ComponentObserver();
	
protected:
	/**
	 * Creates an instance of ComponentObserver.
	 *
	 * @param componentManager Specifies the component manager with which to associate this component observer.
	 */
	ComponentObserver(ComponentManager* componentManager);
	
	ComponentManager* componentManager;
	
private:
	friend class ComponentManager;
	
	/**
	 * Called after a component is added to an entity.
	 *
	 * @param entity Specifies the entity with which the component is associated.
	 * @param component Specifies the component added.
	 */
	virtual void componentAdded(EntityID entity, Component* component) = 0;
	
	/**
	 * Called after a component is removed from an entity.
	 *
	 * @param entity Specifies the entity with which the component is associated.
	 * @param component Specifies the component removed.
	 */
	virtual void componentRemoved(EntityID entity, Component* component) = 0;
};

} // namespace Emergent

#endif // EMERGENT_ENTITY_COMPONENT_OBSERVER_HPP
