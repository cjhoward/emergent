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

#ifndef EMERGENT_ENTITY_ENTITY_ID_POOL_HPP
#define EMERGENT_ENTITY_ENTITY_ID_POOL_HPP

#include <emergent/entity//entity-id.hpp>
#include <set>

namespace Emergent
{

/**
 * Manages the creation and destruction of entities.
 *
 * @ingroup entity
 */
class EntityIDPool
{
public:
	/**
	 * Creates an instance of EntityIDPool.
	 */
	EntityIDPool();
	
	/**
	 * Destroys an instance of EntityIDPool.
	 */
	~EntityIDPool();

	/**
	 * Reserves the next available ID.
	 *
	 * @return Reserved ID.
	 */
	EntityID reserveNextID();

	/**
	 * Reserves the specified ID.
	 *
	 * @param id Specifies an ID to reserve.
	 */
	void reserveID(EntityID id);

	/**
	 * Frees the specified ID.
	 *
	 * @param id Specifies an ID to free.
	 */
	void freeID(EntityID id);

	/**
	 * Returns `true` if the specified ID is reserved.
	 */
	bool isReserved(EntityID id) const;

private:
	void findNextID();

	EntityID nextID;
	std::set<EntityID> reservedIDs;
	std::set<EntityID> availableIDs;
};

inline void EntityIDPool::freeID(EntityID id)
{
	reservedIDs.erase(id);
	availableIDs.insert(id);
}

inline bool EntityIDPool::isReserved(EntityID id) const
{
	return (reservedIDs.find(id) != reservedIDs.end());
}

} // namespace Emergent

#endif // EMERGENT_ENTITY_ENTITY_ID_POOL_HPP
