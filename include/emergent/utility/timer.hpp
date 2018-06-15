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

#ifndef EMERGENT_UTILITY_TIMER_HPP
#define EMERGENT_UTILITY_TIMER_HPP

#include <chrono>

namespace Emergent
{

/**
 * High resolution timer.
 *
 * @ingroup utility
 */
class Timer
{
public:
	/**
	 * Creates an instance of Timer.
	 */
	Timer();
	
	/**
	 * Destroys an instance of Timer.
	 */
	~Timer();
	
	/**
	 * Starts the timer.
	 */
	void start();
	
	/**
	 * Stops the timer.
	 */
	void stop();
	
	/**
	 * Pauses the timer.
	 */
	void pause();
	
	/**
	 * Resets the elapsed duration. This has no effect on the state.
	 */
	void reset();
	
	/**
	 * Returns `true` if the timer is stopped, `false` otherwise. The initial value is `true`.
	 */
	bool isStopped() const;
	
	/**
	 * Returns `true` if the timer is paused, `false` otherwise. The initial value is `false`.
	 */
	bool isPaused() const;
	
	/**
	 * Returns the elapsed duration.
	 */
	std::chrono::high_resolution_clock::duration duration() const;
	
	/**
	 * Returns the elapsed duration in nanoseconds.
	 */
	std::chrono::nanoseconds nanoseconds() const;
	
	/**
	 * Returns the elapsed duration in microseconds.
	 */
	std::chrono::microseconds microseconds() const;
	
	/**
	 * Returns the elapsed duration in milliseconds.
	 */
	std::chrono::milliseconds milliseconds() const;
	
	/**
	 * Returns the elapsed duration in seconds.
	 */
	std::chrono::seconds seconds() const;
	
	/**
	 * Returns the elapsed duration in minutes.
	 */
	std::chrono::minutes minutes() const;
	
	/**
	 * Returns the elapsed duration in hours.
	 */
	std::chrono::hours hours() const;
	
private:
	bool stopped;
	bool paused;
	std::chrono::high_resolution_clock::time_point t0;
	std::chrono::high_resolution_clock::time_point t1;
};

inline bool Timer::isStopped() const
{
	return stopped;
}

inline bool Timer::isPaused() const
{
	return paused;
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_TIMER_HPP
