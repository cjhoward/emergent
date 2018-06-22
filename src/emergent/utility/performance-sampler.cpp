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

#include <emergent/utility/performance-sampler.hpp>

namespace Emergent
{

PerformanceSampler::PerformanceSampler():
	sampleSize(1),
	sampleCount(0),
	sampleDuration(0.0),
	meanFrameDuration(0.0)
{}

void PerformanceSampler::sample(double frameDuration)
{
	sampleDuration += frameDuration;

	if (++sampleCount >= sampleSize)
	{
		meanFrameDuration = sampleDuration / static_cast<double>(sampleSize);
		sampleCount = 0;
		sampleDuration = 0.0;
	}
}

void PerformanceSampler::reset()
{
	sampleCount = 0;
	sampleDuration = 0.0;
	meanFrameDuration = 0.0;
}

void PerformanceSampler::setSampleSize(std::size_t size)
{
	sampleSize = size;
}

} // namespace Emergent

