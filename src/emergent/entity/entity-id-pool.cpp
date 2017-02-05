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

#include <emergent/entity/entity-id-pool.hpp>

namespace Emergent
{

EntityIDPool::EntityIDPool():
	nextID(0)
{}

EntityIDPool::~EntityIDPool()
{}

EntityID EntityIDPool::reserveNextID()
{
	EntityID id;

	if (!availableIDs.empty())
	{
		id = *availableIDs.begin();
		availableIDs.erase(availableIDs.begin());
		reservedIDs.insert(id);
	}
	else
	{
		id = nextID;
		reservedIDs.insert(id);
		findNextID();
	}

	return id;
}

void EntityIDPool::reserveID(EntityID id)
{
	availableIDs.erase(id);
	reservedIDs.insert(id);
	
	if (nextID == id)
	{
		findNextID();
	}
}

inline void EntityIDPool::findNextID()
{
	do
	{
		++nextID;
	}
	while (reservedIDs.find(nextID) != reservedIDs.end());
}

} // namespace Emergent
