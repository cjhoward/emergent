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

#include <emergent/utility/frame-timer.hpp>
#include <algorithm>
#include <cmath>

namespace Emergent
{

FrameTimer::FrameTimer():
	timestep(1.0 / 60.0),
	maxFrameDuration(0.25),
	frameDuration(0.0),
	accumulator(0.0),
	steps(0.0),
	substeps(0.0)
{}

void FrameTimer::reset()
{
	frameDuration = 0.0;
	accumulator = 0.0;
	steps = 0.0;
	substeps = 0.0;
	timer.start();
	timer.reset();
}

void FrameTimer::nextFrame()
{
	// Calculate the frame duration (in seconds)
	frameDuration = static_cast<double>(timer.microseconds().count()) / 1000000.0;

	// Reset the timer
	timer.reset();
	
	// Add frame duration to the accumulator
	accumulator += std::min<double>(maxFrameDuration, frameDuration);

	// Calculate the number of logical steps to be performed
	steps = std::floor(accumulator / timestep);
	substeps = accumulator / timestep - steps;

	// Subtract duration of steps from accumulator
	accumulator -= steps * timestep;
}

void FrameTimer::setTimestep(double timestep)
{
	this->timestep = timestep;
}

void FrameTimer::setMaxFrameDuration(double duration)
{
	maxFrameDuration = duration;
}

} // namespace Emergent

