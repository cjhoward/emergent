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

#ifndef EMERGENT_UTILITY_STEP_SCHEDULER_HPP
#define EMERGENT_UTILITY_STEP_SCHEDULER_HPP

#include <cstdlib>

namespace Emergent
{

/**
 * Schedules steps independently of frame rate.
 *
 * @ingroup utility
 */
class StepScheduler
{
public:
	/// Creates a step scheduler.
	StepScheduler();

	/// Destroys a step scheduler.
	~StepScheduler();

	/**
	 * Schedules steps for the next frame according to the duration of the most recent frame. This should be called immediately after a frame has been drawn.
	 *
	 * @param frameDuration Duration of the most recent frame, in seconds.
	 */
	void schedule(double frameDuration);

	/**
	 * Resets the number of scheduled steps and the accumulator.
	 */
	void reset();

	/**
	 * Sets the maximum frame duration which can be added to the accumulator at one time.
	 *
	 * @param duration Max frame duration, in seconds.
	 */
	void setMaxFrameDuration(double duration);

	/**
	 * Sets the frequency at which steps are scheduled.
	 *
	 * @param frequency Frequency of steps, in hertz.
	 */
	void setStepFrequency(double frequency);

	/// Returns the max frame duration, in seconds.
	double getMaxFrameDuration() const;

	/// Returns the frequency at which steps are scheduled, in hertz.
	double getStepFrequency() const;

	/// Returns the time elapsed between each step, in seconds. Also known as the timestep.
	double getStepPeriod() const;

	/// Returns the number of steps scheduled for this frame.
	std::size_t getScheduledSteps();

	/**
	 * Returns the number of substeps scheduled for this frame. This number will be in the range [0, 1) and can be used to interpolate between steps.
	 */
	double getScheduledSubsteps() const;

private:
	double maxFrameDuration;
	double frequency;
	double period;
	double accumulator;
	double steps;
	double substeps;
};

inline double StepScheduler::getMaxFrameDuration() const
{
	return maxFrameDuration;
}

inline double StepScheduler::getStepFrequency() const
{
	return frequency;
}

inline double StepScheduler::getStepPeriod() const
{
	return period;
}

inline std::size_t StepScheduler::getScheduledSteps()
{
	return static_cast<std::size_t>(steps);
}

inline double StepScheduler::getScheduledSubsteps() const
{
	return substeps;
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_STEP_SCHEDULER_HPP

