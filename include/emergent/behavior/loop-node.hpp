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

#ifndef EMERGENT_BEHAVIOR_LOOP_NODE_HPP
#define EMERGENT_BEHAVIOR_LOOP_NODE_HPP

#include <emergent/behavior/composite-node.hpp>

namespace Emergent
{
namespace BehaviorTree
{

/**
 * Executes each child node until a child's execution fails.
 *
 * @ingroup behavior
 */
template <typename T>
class LoopNode: public CompositeNode<T>
{
public:
	/// @copydoc Node<T>::clone
	Node<T>* clone() const;

	virtual ExitStatus execute(const T& context);
};

template <typename T>
Node<T>* LoopNode<T>::clone() const
{
	LoopNode<T>* node = new LoopNode<T>();

	for (auto child: CompositeNode<T>::children)
		node->addChild(child->clone());

	return node;
}

template <typename T>
ExitStatus LoopNode<T>::execute(const T& context)
{
	do
	{
		for (auto child: CompositeNode<T>::children)
		{
			ExitStatus status = child->execute(context);

			if (status == ExitStatus::FAILURE)
				return status;
		}
	}
	while (!CompositeNode<T>::children.empty());
}

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_LOOP_NODE_HPP
