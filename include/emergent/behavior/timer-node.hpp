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

#ifndef EMERGENT_BEHAVIOR_TIMER_NODE_HPP
#define EMERGENT_BEHAVIOR_TIMER_NODE_HPP

#include <emergent/behavior/decorator-node.hpp>
#include <chrono>

namespace Emergent
{
namespace BehaviorTree
{

/**
 * Executes the child behavior at a specified interval.
 *
 * @ingroup behavior
 */
template <typename T>
class TimerNode: public DecoratorNode<T>
{
public:
	TimerNode(std::chrono::high_resolution_clock::duration interval);
	TimerNode();

	/// @copydoc Node<T>::clone
	Node<T>* clone() const;

	void setInterval(std::chrono::high_resolution_clock::duration interval);
	std::chrono::high_resolution_clock::duration getInterval() const;

	ExitStatus execute(const T& context);

private:
	bool stopped;
	std::chrono::high_resolution_clock::duration interval;
	std::chrono::high_resolution_clock::time_point t0;
};

template <typename T>
TimerNode<T>::TimerNode(std::chrono::high_resolution_clock::duration interval):
	stopped(true),
	interval(interval)
{}

template <typename T>
TimerNode<T>::TimerNode():
	stopped(true)
{}

template <typename T>
Node<T>* TimerNode<T>::clone() const
{
	TimerNode<T>* node = new TimerNode<T>(interval);
	node->setChild(DecoratorNode<T>::child);

	return node;
}

template <typename T>
void TimerNode<T>::setInterval(std::chrono::high_resolution_clock::duration interval)
{
	this->interval = interval;
}

template <typename T>
std::chrono::high_resolution_clock::duration TimerNode<T>::getInterval() const
{
	return interval;
}

template <typename T>
ExitStatus TimerNode<T>::execute(const T& context)
{
	ExitStatus status = ExitStatus::RUNNING;
	std::chrono::high_resolution_clock::time_point t1;

	if (stopped)
	{
		t0 = t1 = std::chrono::high_resolution_clock::now();
		stopped = false;
	}
	else
	{
		t1 = std::chrono::high_resolution_clock::now();
	}

	if ((t1 - t0) >= interval)
	{
		status = DecoratorNode<T>::child->execute(context);
		t0 = t1;
	}

	return status;
}

} // namespace BehaviorTree
} // namespace Emergent

#endif // EMERGENT_BEHAVIOR_TIMER_NODE_HPP
