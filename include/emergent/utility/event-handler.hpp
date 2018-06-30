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

#ifndef EMERGENT_UTILITY_EVENT_HANDLER_HPP
#define EMERGENT_UTILITY_EVENT_HANDLER_HPP

#include <type_traits>

namespace Emergent
{

class EventDispatcher;

/**
 * Abstract base class for event handlers.
 *
 * @ingroup utility
 */
class EventHandlerBase
{
private:
	friend class EventDispatcher;

	/**
	 * Receives an event, casts it to its derived event type, then handles it.
	 *
	 * @param event Received event.
	 */
	virtual void routeEvent(const EventBase& event) = 0;
};

/**
 * Templates abstract base class for event handlers.
 *
 * @tparam Event type.
 *
 * @ingroup utility
 */
template <typename T>
class EventHandler: public EventHandlerBase
{
public:
	static_assert(std::is_base_of<EventBase, T>::value, "T must be a descendant of EventBase.");

	/// Returns the unique event type identifier for the event type handled by this event handler.
	const std::size_t getHandledEventTypeID() const;

	/**
	 * Handles an event of type T.
	 *
	 * @param event Event to handle.
	 */
	virtual void handleEvent(const T& event) = 0;

private:
	/// @copydoc EventHandlerBase::routeEvent()
	virtual void routeEvent(const EventBase& event) final;
};

template <typename T>
inline const std::size_t EventHandler<T>::getHandledEventTypeID() const
{
	return T::EVENT_TYPE_ID;
}

template <typename T>
void EventHandler<T>::routeEvent(const EventBase& event)
{
	handleEvent(static_cast<const T&>(event));
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_EVENT_HANDLER_HPP

