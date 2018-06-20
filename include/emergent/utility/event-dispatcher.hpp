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

#ifndef EMERGENT_UTILITY_EVENT_DISPATCHER_HPP
#define EMERGENT_UTILITY_EVENT_DISPATCHER_HPP

#include <emergent/utility/event.hpp>
#include <emergent/utility/event-handler.hpp>
#include <cstdlib>
#include <list>
#include <map>

namespace Emergent
{

/**
 * Queues events and dispatches them to event handlers.
 *
 * @ingroup utility
 */
class EventDispatcher
{
public:
	/// Creates an event dispatcher
	EventDispatcher();

	/// Destroys an event dispatcher
	~EventDispatcher();

	/**
	 * Subscribes an event handler to event dispatches.
	 *
	 * @param handler Handler to subscribe.
	 */
	template <typename T>
	void subscribe(EventHandler<T>* handler);

	/**
	 * Unsubscribes an event handler from event dispatches.
	 *
	 * @param handler Handler to unsubscribe.
	 */
	template <typename T>
	void unsubscribe(EventHandler<T>* handler);

	/**
	 * Adds an event to the queue.
	 *
	 * @param event Event to queue.
	 */
	void queue(const EventBase& event);

	/// Dispatches all queued events and removes them from the queue.
	void dispatch();

	/**
	 * Dispatches a single event immediately without adding it to the queue.
	 *
	 * @param event Event to dispatch.
	 */
	void dispatch(const EventBase& event);

	/// Removes all events from the queue without notifying handlers.
	void clear();

private:
	std::list<std::tuple<std::size_t, EventHandlerBase*>> toSubscribe;
	std::list<std::tuple<std::size_t, EventHandlerBase*>> toUnsubscribe;
	std::map<std::size_t, std::list<EventHandlerBase*>> handlers;
	std::map<std::size_t, std::list<EventBase*>> events;
};

template <typename T>
void EventDispatcher::subscribe(EventHandler<T>* handler)
{
	toSubscribe.push_back(std::make_tuple(handler->getHandledEventTypeID(), handler));
}

template <typename T>
void EventDispatcher::unsubscribe(EventHandler<T>* handler)
{
	toUnsubscribe.push_back(std::make_tuple(handler->getHandledEventTypeID(), handler));
}

inline void EventDispatcher::queue(const EventBase& event)
{
	events[event.getEventTypeID()].push_back(event.clone());
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_EVENT_DISPATCHER_HPP

