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

#ifndef EMERGENT_BEHAVIOR_COMPOSITE_NODE_HPP
#define EMERGENT_BEHAVIOR_COMPOSITE_NODE_HPP

#include <emergent/behavior/node.hpp>
#include <list>

namespace Emergent
{
namespace BehaviorTree
{

/**
 * Abstract base class for nodes which can contain one or more child nodes.
 *
 * @ingroup behavior
 */
template <typename T>
class CompositeNode: public Node<T>
{
public:
	/**
	 * Adds a child node.
	 *
	 * @param child Specifies a child node.
	 */
	void addChild(Node<T>* child);

	/**
	 * Removes a child node.
	 *
	 * @param child Specifies a child node.
	 */
	void removeChild(Node<T>* child);

	/**
	 * Removes all child nodes.
	 */
	void removeChildren();

protected:
	std::list<Node<T>*> children;
};

template <typename T>
void CompositeNode<T>::addChild(Node<T>* child)
{
	children.push_back(child);
}

template <typename T>
void CompositeNode<T>::removeChild(Node<T>* child)
{
	children.remove(child);
}

template <typename T>
void CompositeNode<T>::removeChildren()
{
	children.clear();
}

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_COMPOSITE_NODE_HPP
