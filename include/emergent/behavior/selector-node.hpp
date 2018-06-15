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

#ifndef EMERGENT_BEHAVIOR_SELECTOR_NODE_HPP
#define EMERGENT_BEHAVIOR_SELECTOR_NODE_HPP

#include <emergent/behavior/composite-node.hpp>

namespace Emergent
{
namespace BehaviorTree
{

/**
 * Executes each child node in order until a child's execution succeeds or the last child node is executed.
 *
 * @ingroup behavior
 */
template <typename T>
class SelectorNode: public CompositeNode<T>
{
public:
	/// @copydoc Node<T>::clone
	Node<T>* clone() const;

	virtual ExitStatus execute(const T& context);
};

template <typename T>
Node<T>* SelectorNode<T>::clone() const
{
	SelectorNode<T>* node = new SelectorNode<T>();

	for (auto child: CompositeNode<T>::children)
		node->addChild(child->clone());

	return node;
}

template <typename T>
ExitStatus SelectorNode<T>::execute(const T& context)
{
	ExitStatus status = ExitStatus::SUCCESS;

	for (auto child: CompositeNode<T>::children)
	{
		status = child->execute(context);

		if (status != ExitStatus::FAILURE)
			break;
	}

	return status;
}

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_SELECTOR_NODE_HPP
