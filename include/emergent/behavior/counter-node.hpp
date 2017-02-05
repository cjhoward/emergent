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

#ifndef EMERGENT_BEHAVIOR_COUNTER_NODE_HPP
#define EMERGENT_BEHAVIOR_COUNTER_NODE_HPP

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
class CounterNode: public DecoratorNode<T>
{
public:
	CounterNode(unsigned int limit);
	CounterNode();

	/// @copydoc Node<T>::clone
	Node<T>* clone() const;

	void setLimit(unsigned int limit);
	unsigned int getLimit() const;

	ExitStatus execute(const T& context);

private:
	unsigned int count;
	unsigned int limit;
};

template <typename T>
CounterNode<T>::CounterNode(unsigned int limit):
	count(0),
	limit(limit)
{}

template <typename T>
CounterNode<T>::CounterNode():
	count(0),
	limit(0)
{}

template <typename T>
Node<T>* CounterNode<T>::clone() const
{
	CounterNode<T>* node = new CounterNode<T>(limit);
	node->setChild(DecoratorNode<T>::child);

	return node;
}

template <typename T>
void CounterNode<T>::setLimit(unsigned int limit)
{
	this->limit = limit;
}

template <typename T>
unsigned int CounterNode<T>::getLimit() const
{
	return limit;
}

template <typename T>
ExitStatus CounterNode<T>::execute(const T& context)
{
	ExitStatus status = ExitStatus::RUNNING;

	if (++count >= limit)
	{
		status = DecoratorNode<T>::child->execute(context);
		count = 0;
	}

	return status;
}

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_COUNTER_NODE_HPP
