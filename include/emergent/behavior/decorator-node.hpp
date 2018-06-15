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

#ifndef EMERGENT_BEHAVIOR_DECORATOR_NODE_HPP
#define EMERGENT_BEHAVIOR_DECORATOR_NODE_HPP

#include <emergent/behavior/node.hpp>

namespace Emergent
{
namespace BehaviorTree
{

/**
 * Abstract base class for decorator nodes, which can contain one child node.
 *
 * @ingroup behavior
 */
template <typename T>
class DecoratorNode: public Node<T>
{
public:
	/**
	 * Creates an instance of DecoratorNode.
	 *
	 * @param child Specifies a child node.
	 */
	DecoratorNode(Node<T>* child);

	/**
	 * Creates an instance of DecoratorNode.
	 */
	DecoratorNode();

	/**
	 * Sets the child of this decorator node.
	 *
	 * @param child Specifies a child.
	 */
	void setChild(Node<T>* child);

	/**
	 * Returns the child of this decorator node.
	 */
	const Node<T>* getChild() const;

	/// @copydoc DecoratorNode::getChild() const
	Node<T>* getChild();

protected:
	Node<T>* child;
};

template <typename T>
DecoratorNode<T>::DecoratorNode(Node<T>* child):
	child(child)
{}

template <typename T>
DecoratorNode<T>::DecoratorNode():
	child(nullptr)
{}

template <typename T>
void DecoratorNode<T>::setChild(Node<T>* child)
{
	this->child = child;
}

template <typename T>
const Node<T>* DecoratorNode<T>::getChild() const
{
	return child;
}

template <typename T>
Node<T>* DecoratorNode<T>::getChild()
{
	return child;
}

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_DECORATOR_NODE_HPP
