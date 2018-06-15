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

#ifndef EMERGENT_BEHAVIOR_NODE_HPP
#define EMERGENT_BEHAVIOR_NODE_HPP

#include <emergent/behavior/exit-status.hpp>

namespace Emergent
{
namespace BehaviorTree
{

/**
 * Abstract base class for behavior tree nodes.
 *
 * @ingroup behavior
 */
template <typename T>
class Node
{
public:
	/**
	 * Returns a clone of the behavior tree node.
	 */
	virtual Node<T>* clone() const = 0;

	/**
	 * Executes this node and returns an exit status.
	 */
	virtual ExitStatus execute(const T& context) = 0;
};

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_NODE
