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

#ifndef EMERGENT_BEHAVIOR_INVERTER_NODE_HPP
#define EMERGENT_BEHAVIOR_INVERTER_NODE_HPP

#include <emergent/behavior/decorator-node.hpp>

namespace Emergent
{
namespace BehaviorTree
{

/**
 * Returns the inverted exit status of the child node.
 *
 * @ingroup behavior
 */
template <typename T>
class InverterNode: public DecoratorNode<T>
{
public:
	/// @copydoc Node<T>::clone
	Node<T>* clone() const;

	ExitStatus execute(const T& context);
};

template <typename T>
Node<T>* InverterNode<T>::clone() const
{
	InverterNode<T>* node = new InverterNode<T>();
	node->setChild(DecoratorNode<T>::child);

	return node;
}

template <typename T>
ExitStatus InverterNode<T>::execute(const T& context)
{
	ExitStatus status = DecoratorNode<T>::child->execute(context);

	switch (status)
	{
		case ExitStatus::SUCCESS:
			status = ExitStatus::FAILURE;
			break;

		case ExitStatus::FAILURE:
			status = ExitStatus::SUCCESS;
			break;

		default:
			break;
	}

	return status;
}

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_INVERTER_NODE_HPP
