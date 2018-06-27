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
	 * Processes all pending subscriptions and unsubscriptions, dispatches queued events, then dispatches due scheduled events.
	 *
	 * @param time The current time.
	 */
	void update(double time);

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

	/**
	 * Schedules an event to be dispatched at a specific time.
	 *
	 * @param event Event to schedule.
	 * @param time Time that the event should be dispatched.
	 */
	void schedule(const EventBase& event, double time);

	/**
	 * Dispatches a single event.
	 *
	 * @param event Event to dispatch.
	 */
	void dispatch(const EventBase& event);

	/**
	 * Dispatches all events in the queue.
	 */
	void flush();

	/// Removes all queued and scheduled events from the queue without notifying handlers.
	void clear();

private:
	std::list<std::tuple<std::size_t, EventHandlerBase*>> toSubscribe;
	std::list<std::tuple<std::size_t, EventHandlerBase*>> toUnsubscribe;
	std::map<std::size_t, std::list<EventHandlerBase*>> handlerMap;
	std::list<EventBase*> queuedEvents;
	std::multimap<double, EventBase*> scheduledEvents;
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
	queuedEvents.push_back(event.clone());
}

inline void EventDispatcher::schedule(const EventBase& event, double time)
{
	scheduledEvents.insert(std::pair<double, EventBase*>(time, event.clone()));
}

inline void EventDispatcher::dispatch(const EventBase& event)
{
	// Get list of handlers for this type of event
	const std::list<EventHandlerBase*>& handlers = handlerMap[event.getEventTypeID()];

	// For each handler
	for (auto handler = handlers.begin(); handler != handlers.end(); ++handler)
	{
		// Pass event to the handler
		(*handler)->routeEvent(event);
	}
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_EVENT_DISPATCHER_HPP

