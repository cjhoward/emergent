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

#ifndef EMERGENT_BEHAVIOR_ACTION_NODE_HPP
#define EMERGENT_BEHAVIOR_ACTION_NODE_HPP

#include <emergent/behavior/node.hpp>
#include <functional>

namespace Emergent
{
namespace BehaviorTree
{

/**
 * Leaf node which executes a specified action.
 *
 * @ingroup behavior
 */
template <typename T>
class ActionNode: public Node<T>
{
public:
	/**
	 * Creates an instance of ActionNode.
	 *
	 * @param action Specifies an action.
	 */
	ActionNode(std::function<ExitStatus(const T&)> action);

	/**
	 * Creates an instance of ActionNode.
	 */
	ActionNode();

	/// @copydoc Node<T>::clone
	Node<T>* clone() const;

	/**
	 * Sets the action of this node.
	 */
	void setAction(std::function<ExitStatus(const T&)> action);

	/**
	 * Returns the action of this node.
	 */
	std::function<ExitStatus(const T&)> getAction() const;

	/**
	 * Executes this node's action and returns its exit status.
	 */
	ExitStatus execute(const T& context);

protected:
	std::function<ExitStatus(const T&)> action;
};

template <typename T>
ActionNode<T>::ActionNode(std::function<ExitStatus(const T&)> action):
	action(action)
{}

template <typename T>
ActionNode<T>::ActionNode()
{}

template <typename T>
Node<T>* ActionNode<T>::clone() const
{
	return new ActionNode<T>(action);
}

template <typename T>
void ActionNode<T>::setAction(std::function<ExitStatus(const T&)> action)
{
	this->action = action;
}

template <typename T>
std::function<ExitStatus(const T&)> ActionNode<T>::getAction() const
{
	return action;
}

template <typename T>
ExitStatus ActionNode<T>::execute(const T& context)
{
	return action(context);
}

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_ACTION_NODE_HPP
