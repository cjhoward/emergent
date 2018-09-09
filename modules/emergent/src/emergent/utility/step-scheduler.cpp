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

#include <emergent/utility/step-scheduler.hpp>
#include <algorithm>
#include <cmath>

namespace Emergent
{

StepScheduler::StepScheduler():
	maxFrameDuration(1.0),
	frequency(60.0),
	period(1.0 / 60.0),
	accumulator(0.0),
	steps(0.0),
	substeps(0.0)
{}

StepScheduler::~StepScheduler()
{}

void StepScheduler::schedule(double frameDuration)
{
	// Add frame duration to the accumulator
	accumulator += std::min<double>(maxFrameDuration, frameDuration);

	// Calculate the number of steps to schedule
	steps = std::floor(accumulator * frequency);
	substeps = accumulator * frequency - steps;

	// Subtract duration of scheduled steps from the accumulator
	accumulator -= steps * period;
}

void StepScheduler::reset()
{
	accumulator = 0.0;
	steps = 0.0;
	substeps = 0.0;
}

void StepScheduler::setMaxFrameDuration(double duration)
{
	maxFrameDuration = duration;
}

void StepScheduler::setStepFrequency(double frequency)
{
	this->frequency = frequency;
	period = 1.0 / frequency;
}

} // namespace Emergent

