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

#include <emergent/utility/timer.hpp>

namespace Emergent
{

Timer::Timer():
	stopped(true),
	paused(false)
{}

Timer::~Timer()
{}

void Timer::start()
{
	if (stopped)
	{
		t0 = std::chrono::high_resolution_clock::now();
		stopped = false;
	}
	else if (paused)
	{
		t0 = std::chrono::high_resolution_clock::now() - (t1 - t0);
		paused = false;
	}
}

void Timer::stop()
{
	if (!stopped)
	{
		paused = false;
		stopped = true;
		t1 = std::chrono::high_resolution_clock::now();
	}
}

void Timer::pause()
{
	if (!stopped && !paused)
	{
		paused = true;
		stopped = false;
		t1 = std::chrono::high_resolution_clock::now();
	}
}

void Timer::reset()
{
	t0 = t1 = std::chrono::high_resolution_clock::now();
}

std::chrono::high_resolution_clock::duration Timer::duration() const
{
	if (!stopped && !paused)
		return (std::chrono::high_resolution_clock::now() - t0);
	
	return (t1 - t0);
}

std::chrono::nanoseconds Timer::nanoseconds() const
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(duration());
}

std::chrono::microseconds Timer::microseconds() const
{
	return std::chrono::duration_cast<std::chrono::microseconds>(duration());
}

std::chrono::milliseconds Timer::milliseconds() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration());
}

std::chrono::seconds Timer::seconds() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(duration());
}

std::chrono::minutes Timer::minutes() const
{
	return std::chrono::duration_cast<std::chrono::minutes>(duration());
}

std::chrono::hours Timer::hours() const
{
	return std::chrono::duration_cast<std::chrono::hours>(duration());
}

} // namespace Emergent
