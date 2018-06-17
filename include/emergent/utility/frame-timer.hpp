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

#ifndef EMERGENT_UTILITY_FRAME_TIMER_HPP
#define EMERGENT_UTILITY_FRAME_TIMER_HPP

#include <emergent/utility/timer.hpp>
#include <cstdlib>

namespace Emergent
{

/**
 * 
 */
class FrameTimer
{
public:
	/// Creates a frame timer.
	FrameTimer();

	/**
	 * Resets the frame timer. This should be called right before entering the main loop.
	 */
	void reset();

	/**
	 * Determines the number of logical steps to be performed according to the duration of the previous frame. This should be called after a frame has been drawn.
	 */
	void nextFrame();

	/**
	 * Sets the timestep.
	 *
	 * @param timestep The amount of time between each logical step, in seconds.
	 */
	void setTimestep(double timestep);

	/**
	 * Sets the maximum duration of a frame.
	 *
	 * @param duration Maximum frame duration, in seconds.
	 */
	void setMaxFrameDuration(double duration);

	/// Returns the timestep, in seconds.
	double getTimestep() const;

	/// Returns the number of logical steps to be performed this frame.
	std::size_t getSteps() const;

	/**
	 * Returns the degree of interpolation that should be performed between the previous state and the current state.
	 */
	double getSubsteps() const;

private:
	double timestep;
	double maxFrameDuration;
	double frameDuration;
	double accumulator;
	double steps;
	double substeps;
	Timer timer;
};

inline double FrameTimer::getTimestep() const
{
	return timestep;
}

inline std::size_t FrameTimer::getSteps() const
{
	return static_cast<std::size_t>(steps);
}

inline double FrameTimer::getSubsteps() const
{
	return substeps;
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_FRAME_TIMER_HPP

