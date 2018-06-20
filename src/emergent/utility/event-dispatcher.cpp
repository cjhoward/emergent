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

#include <emergent/utility/event-dispatcher.hpp>

namespace Emergent
{

EventDispatcher::EventDispatcher()
{}

EventDispatcher::~EventDispatcher()
{
	clear();
}

void EventDispatcher::dispatch()
{
	// Process pending subscriptions
	for (auto it = toSubscribe.begin(); it != toSubscribe.end(); ++it)
	{
		handlers[std::get<0>(*it)].push_back(std::get<1>(*it));
	}
	toSubscribe.clear();

	// Process pending unsubscriptions
	for (auto it = toUnsubscribe.begin(); it != toUnsubscribe.end(); ++it)
	{
		handlers[std::get<0>(*it)].remove(std::get<1>(*it));
	}
	toUnsubscribe.clear();

	// For each type of event
	for (auto eventQueue = events.begin(); eventQueue != events.end(); ++eventQueue)
	{
		if (eventQueue->second.empty())
		{
			continue;
		}

		// Get list of handlers for this type of event
		const std::list<EventHandlerBase*>& handlerList = handlers[eventQueue->first];

		// For each event in the queue
		for (auto event = eventQueue->second.begin(); event != eventQueue->second.end(); ++event)
		{
			// For each handler
			for (auto handler = handlerList.begin(); handler != handlerList.end(); ++handler)
			{
				// Pass event to the handler
				(*handler)->routeEvent(**event);
			}

			// Delete event
			delete (*event);
		}

		// Clear event queue
		eventQueue->second.clear();
	}
}

void EventDispatcher::dispatch(const EventBase& event)
{
	// Get list of handlers for this type of event
	const std::list<EventHandlerBase*>& handlerList = handlers[event.getEventTypeID()];

	// For each handler
	for (auto handler = handlerList.begin(); handler != handlerList.end(); ++handler)
	{
		// Pass event to the handler
		(*handler)->routeEvent(event);
	}
}

void EventDispatcher::clear()
{
	// For each type of event
	for (auto eventQueue = events.begin(); eventQueue != events.end(); ++eventQueue)
	{
		// For each event in the queue
		for (auto event = eventQueue->second.begin(); event != eventQueue->second.end(); ++event)
		{
			// Delete event
			delete (*event);
		}

		// Clear event queue
		eventQueue->second.clear();
	}
}

} // namespace Emergent

