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

#ifndef EMERGENT_ENTITY_ENTITY_CONTEXT_HPP
#define EMERGENT_ENTITY_ENTITY_CONTEXT_HPP

#include <emergent/entity/entity-id.hpp>
#include <utility>

namespace Emergent
{

class EntityManager;

/**
 * Entity context type.
 *
 * @ingroup entity
 */
typedef std::pair<EntityManager*, EntityID> EntityContext;

} // namespace Emergent

#endif // EMERGENT_ENTITY_ENTITY_CONTEXT_HPP
