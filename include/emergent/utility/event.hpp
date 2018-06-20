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

#ifndef EMERGENT_UTILITY_EVENT_HPP
#define EMERGENT_UTILITY_EVENT_HPP

#include <cstdlib>

namespace Emergent
{

/**
 * Abstract base class for events.
 *
 * @ingroup utility
 */
class EventBase
{
public:
	/// Destroys an event base.
	virtual ~EventBase() = default;

	/// Returns the unique event type identifier for this event.
	virtual std::size_t getEventTypeID() const = 0;

	/**
	 * Allocates a copy of this event.
	 *
	 * @return Newly allocated copy of this event.
	 */
	virtual EventBase* clone() const = 0;
};

/**
 * Templated abstract base class for events.
 *
 * @tparam eventType Unique event type identifier.
 *
 * @ingroup utility
 */
template <std::size_t eventTypeID>
class Event: public EventBase
{
public:
	/// Unique event type identifier.
	static const std::size_t EVENT_TYPE_ID = eventTypeID;

	/// Destroys an event
	virtual ~Event() = default;

	/// @copydoc EventBase::getEventTypeID()
	virtual std::size_t getEventTypeID() const final;

	/// @copydoc EvenetBase::clone()
	virtual EventBase* clone() const = 0;
};

template <std::size_t eventTypeID>
inline std::size_t Event<eventTypeID>::getEventTypeID() const
{
	return eventTypeID;
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_EVENT_HPP

