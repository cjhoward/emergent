/*
 * Copyright (C) 2017  Christopher J. Howard
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

#include <emergent/geometry/split-view-frustum.hpp>
#include <cmath>
#include <iostream>

namespace Emergent
{

SplitViewFrustum::SplitViewFrustum(std::size_t subfrustumCount):
	subfrustumCount(subfrustumCount),
	subfrustums(nullptr),
	splitSchemeWeight(0.5f),
	splitDistances(nullptr)
{
	subfrustums = new ViewFrustum[subfrustumCount];
	splitDistances = new float[subfrustumCount + 1];
}

SplitViewFrustum::~SplitViewFrustum()
{
	delete[] subfrustums;
	delete[] splitDistances;
}

void SplitViewFrustum::distributeSubfrustums()
{
	float near = getNear().getDistance();
	float far = getFar().getDistance();
	
	// Calculate split distances
	for (std::size_t i = 1; i < subfrustumCount; ++i)
	{
		float part = static_cast<float>(i) / static_cast<float>(subfrustumCount);
		
		// Calculate uniform split distance
		float uniformSplitDistance = near + (far - near) * part;
		
		// Calculate logarithmic split distance
		float logSplitDistance = near * std::pow(far / near, part);
		
		//std::cout << i << "uni: " << uniformSplitDistance << ", log: " << logSplitDistance << std::endl;
		
		// Interpolate between uniform and logarithmic split distances
		splitDistances[i] = logSplitDistance * splitSchemeWeight + uniformSplitDistance * (1.0f - splitSchemeWeight);
	}
	splitDistances[0] = near;
	splitDistances[subfrustumCount] = far;
	
	std::cout << "near: " << near << ", far: " << far << std::endl;
	
	// Update subfrustums
	for (std::size_t i = 0; i < subfrustumCount; ++i)
	{
		// Determine near and far distances for this subfrustum
		float splitNear = splitDistances[i];
		float splitFar = splitDistances[i + 1];
		
		std::cout << i << "dist: " << splitNear << ", " << splitFar << std::endl;
		
		// Calculate subfrustum projection matrix
		Matrix4 splitProjection = getProjectionMatrix();
		splitProjection[2][2] = -2.0f / (splitFar - splitNear);
		splitProjection[3][2] = -(splitFar + splitNear) / (splitFar - splitNear);
		
		// Set subfrustum matrices
		subfrustums[i].setMatrices(getViewMatrix(), splitProjection);
	}
}

void SplitViewFrustum::setSplitSchemeWeight(float weight)
{
	splitSchemeWeight = weight;
	distributeSubfrustums();
}

void SplitViewFrustum::recalculateFrustum()
{
	ViewFrustum::recalculateFrustum();
	distributeSubfrustums();
}

} // namespace Emergent
