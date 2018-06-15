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

#ifndef EMERGENT_ENTITY_COMPONENT_HPP
#define EMERGENT_ENTITY_COMPONENT_HPP

namespace Emergent
{

enum class ComponentType;

/**
 * Abstract base class for entity components.
 *
 * @ingroup entity
 */
class Component
{
public:
	/**
	 * Destroys an instance of Component.
	 */
	virtual ~Component() = default;

	/**
	 * Clones the component.
	 */
	virtual Component* clone() const = 0;
	
	/**
	 * Returns the component type.
	 */
	virtual ComponentType getComponentType() const = 0;
	
protected:
	/**
	 * Creates an instance of Component.
	 */
	Component() = default;
};

} // namespace Emergent

#endif // EMERGENT_ENTITY_COMPONENT_HPP
