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

#ifndef EMERGENT_BEHAVIOR_CONDITIONAL_NODE_HPP
#define EMERGENT_BEHAVIOR_CONDITIONAL_NODE_HPP

#include <emergent/behavior/node.hpp>
#include <functional>

namespace Emergent
{
namespace BehaviorTree
{

/**
 * Leaf node which executes a conditional function and returns the result.
 *
 * @ingroup behavior
 */
template <typename T>
class ConditionalNode: public Node<T>
{
public:
	/**
	 * Creates an instance of ConditionalNode.
	 *
	 * @param conditional Specifies a conditional function.
	 */
	ConditionalNode(std::function<bool(const T&)> conditional);

	/**
	 * Creates an instance of ConditionalNode.
	 */
	ConditionalNode();

	/// @copydoc Node<T>::clone
	Node<T>* clone() const;

	/**
	 * Sets the conditional function of this node.
	 */
	void setConditional(std::function<bool(const T&)> conditional);

	/**
	 * Returns the conditional function of this node.
	 */
	std::function<bool(const T&)> getConditional() const;

	/**
	 * Executes this node's conditional function and returns ExitStatus::SUCCESS if the result is true, and ExitStatus::FAILURE if the result is false.
	 */
	ExitStatus execute(const T& context);

protected:
	std::function<bool(const T&)> conditional;
};

template <typename T>
ConditionalNode<T>::ConditionalNode(std::function<bool(const T&)> conditional):
	conditional(conditional)
{}

template <typename T>
ConditionalNode<T>::ConditionalNode()
{}

template <typename T>
Node<T>* ConditionalNode<T>::clone() const
{
	return new ConditionalNode<T>(conditional);
}

template <typename T>
void ConditionalNode<T>::setConditional(std::function<bool(const T&)> conditional)
{
	this->conditional = conditional;
}

template <typename T>
std::function<bool(const T&)> ConditionalNode<T>::getConditional() const
{
	return conditional;
}

template <typename T>
ExitStatus ConditionalNode<T>::execute(const T& context)
{
	return conditional(context) ? ExitStatus::SUCCESS : ExitStatus::FAILURE;
}

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_CONDITIONAL_NODE_HPP
