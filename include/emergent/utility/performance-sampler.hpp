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

#ifndef EMERGENT_UTILITY_PERFORMANCE_SAMPLER_HPP
#define EMERGENT_UTILITY_PERFORMANCE_SAMPLER_HPP

#include <cstdlib>

namespace Emergent
{

/**
 * Measures the mean frame time of an application.
 *
 * @ingroup utility
 */
class PerformanceSampler
{
public:
	/// Creates a performance sampler.
	PerformanceSampler();

	/// Destroys a performance sampler.
	~PerformanceSampler() = default;

	/**
	 * Adds a frame to the sample.
	 *
	 * @param frameDuration Duration of the frame.
	 */
	void sample(double frameDuration);

	/**
	 * Resets the sampling process.
	 */
	void reset();

	/**
	 * Sets the number of frames in a sample.
	 *
	 * @param size Number of frames in a sample.
	 */
	void setSampleSize(std::size_t size);

	/**
	 * Returns the mean frame duration.
	 */
	double getMeanFrameDuration() const;

private:
	std::size_t sampleSize;
	std::size_t sampleCount;
	double sampleDuration;
	double meanFrameDuration;
};

inline double PerformanceSampler::getMeanFrameDuration() const
{
	return meanFrameDuration;
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_PERFORMANCE_SAMPLER_HPP

