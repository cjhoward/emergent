/*
 * Copyright (C) 2017-2019  Christopher J. Howard
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

#include <atomic>
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

	/// Returns the unique event type identifier for this event type.
	virtual const std::size_t getEventTypeID() const = 0;

	/**
	 * Allocates a copy of this event.
	 *
	 * @return Newly allocated copy of this event.
	 */
	virtual EventBase* clone() const = 0;

protected:
	/// Returns the next available event type ID.
	static std::size_t getNextEventTypeID();
};

inline std::size_t EventBase::getNextEventTypeID()
{
	static std::atomic<std::size_t> nextEventTypeID{0};
	return nextEventTypeID++;
}

/**
 * Templated abstract base class for events.
 *
 * @tparam T The derived class.
 *
 * @ingroup utility
 */
template <typename T>
class Event: public EventBase
{
public:
	/// The unique event type identifier for this event type.
	static const std::atomic<std::size_t> EVENT_TYPE_ID;

	/// Destroys an event
	virtual ~Event() = default;

	virtual const std::size_t getEventTypeID() const final;
	virtual EventBase* clone() const = 0;
};

template <typename T>
const std::atomic<std::size_t> Event<T>::EVENT_TYPE_ID{EventBase::getNextEventTypeID()};

template <typename T>
inline const std::size_t Event<T>::getEventTypeID() const
{
	return EVENT_TYPE_ID;
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_EVENT_HPP

