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

#ifndef EMERGENT_ENTITY_ENTITY_MANAGER_HPP
#define EMERGENT_ENTITY_ENTITY_MANAGER_HPP

#include <emergent/entity/entity-id.hpp>
#include <emergent/entity/entity-id-pool.hpp>
#include <emergent/entity/component-manager.hpp>

namespace Emergent
{

/**
 * Manages the creation and destruction of entities.
 *
 * @ingroup entity
 */
class EntityManager
{
public:
	/**
	 * Creates an instance of EntityManager.
	 */
	EntityManager();
	
	/**
	 * Destroys an instance of EntityManager.
	 */
	~EntityManager();

	/**
	 * Creates an entity template with the next available template ID.
	 *
	 * @return Template ID of the created template.
	 */
	EntityID createTemplate();

	/**
	 * Creates an entity template with the specified template ID.
	 *
	 * @param templateID Specifies the template ID of the entity template to be created.
	 *
	 * @return `true` if the entity template was created, and `false` if the entity template already exists.
	 */
	bool createTemplate(EntityID templateID);

	/**
	  * Destroys an entity template with the specified template ID.
	  *
	  * @param templateID Specifies the template ID of the entity template to be destroyed.
	  *
	  * @return `true` if the entity template was destroyed, and `false` if an invalid template ID was supplied.
	  */
	bool destroyTemplate(EntityID templateID);

	/**
	 * Creates an entity instance with the next available instance ID.
	 *
	 * @return Instance ID of the created entity instance.
	 */
	EntityID createInstance();
	
	/**
	 * Creates an entity instance with the next available instance ID.
	 *
	 * @param templateID Specifies the template ID of the entity instance to be created.
	 * @return Instance ID of the created entity instance.
	 */
	EntityID createInstance(EntityID templateID);

	/**
	 * Creates an entity instance with the specified instance ID.
	 *
	 * @param templateID Specifies the template ID of the entity instance to be created.
	 * @param instanceID Specifies the instance ID of the entity instance to be created.
	 *
	 * @return `true` if the entity instance was created, and `false` if the entity instance already exists.
	 */
	bool createInstance(EntityID templateID, EntityID instanceID);
	
	/**
	 * Destroys an entity instance with the specified instance ID.
	 *
	 * @param instanceID Specifies the instance ID of the entity instance to be destroyed.
	 *
	 * @return `true` if the entity instance was destroyed, and `false` if an invalid instance ID was supplied.
	 */
	bool destroyInstance(EntityID instanceID);

	/**
	 * Returns the component manager associated with entity templates.
	 */
	const ComponentManager* getTemplateComponentManager() const;

	/// @copydoc EntityManager::getTemplateComponentManager() const
	ComponentManager* getTemplateComponentManager();

	/**
	 * Returns the component manager associated with entity instances.
	 */
	const ComponentManager* getInstanceComponentManager() const;

	/// @copydoc EntityManager::getInstanceComponentManager() const
	ComponentManager* getInstanceComponentManager();
	
private:
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;

	/**
	 * Applies the specified entity template to an entity instance.
	 *
	 * @param templateID Specifies the ID of an entity template.
	 * @param instanceID Specifies the ID of an entity instance.
	 */
	void applyTemplate(EntityID templateID, EntityID instanceID);

	EntityIDPool templateIDPool;
	EntityIDPool instanceIDPool;
	ComponentManager templateComponentManager;
	ComponentManager instanceComponentManager;
};

inline const ComponentManager* EntityManager::getTemplateComponentManager() const
{
	return &templateComponentManager;
}

inline ComponentManager* EntityManager::getTemplateComponentManager()
{
	return &templateComponentManager;
}

inline const ComponentManager* EntityManager::getInstanceComponentManager() const
{
	return &instanceComponentManager;
}

inline ComponentManager* EntityManager::getInstanceComponentManager()
{
	return &instanceComponentManager;
}

} // namespace Emergent

#endif // EMERGENT_ENTITY_ENTITY_MANAGER_HPP
