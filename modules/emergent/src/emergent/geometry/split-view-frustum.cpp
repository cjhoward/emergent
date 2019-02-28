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

#include <emergent/geometry/split-view-frustum.hpp>
#include <cmath>

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
	float near;
	float far;
	bool orthographic = (getProjectionMatrix()[2][3] == 0.0f);
	
	// Derive near and far clipping planes from projection matrix
	// @see https://stackoverflow.com/questions/10830293/decompose-projection-matrix44-to-left-right-bottom-top-near-and-far-boundary
	if (orthographic)
	{
		// Orthographic projection
		near = (1.0f + getProjectionMatrix()[3][2]) / getProjectionMatrix()[2][2];
		far = -(1.0f - getProjectionMatrix()[3][2]) / getProjectionMatrix()[2][2];
	}
	else
	{
		// Perspective projection
		near = getProjectionMatrix()[3][2] / (getProjectionMatrix()[2][2] - 1.0f);
		far = getProjectionMatrix()[3][2] / (getProjectionMatrix()[2][2] + 1.0f);
	}
	
	// Calculate split distances
	for (std::size_t i = 1; i < subfrustumCount; ++i)
	{
		float part = static_cast<float>(i) / static_cast<float>(subfrustumCount);
		
		// Calculate uniform split distance
		float uniformSplitDistance = near + (far - near) * part;
		
		// Calculate logarithmic split distance
		float logSplitDistance = near * std::pow(far / near, part);
			
		// Interpolate between uniform and logarithmic split distances
		splitDistances[i] = logSplitDistance * splitSchemeWeight + uniformSplitDistance * (1.0f - splitSchemeWeight);
	}
	splitDistances[0] = near;
	splitDistances[subfrustumCount] = far;
	
	// Update subfrustums
	for (std::size_t i = 0; i < subfrustumCount; ++i)
	{
		// Determine near and far distances for this subfrustum
		float subfrustumNear = splitDistances[i];
		float subfrustumFar = splitDistances[i + 1];
		
		// Calculate subfrustum projection matrix
		Matrix4 subfrustumProjection = getProjectionMatrix();
		if (orthographic)
		{
			// Orthographic projection
			subfrustumProjection[2][2] = -2.0f / (subfrustumFar - subfrustumNear);
			subfrustumProjection[3][2] = -(subfrustumFar + subfrustumNear) / (subfrustumFar - subfrustumNear);
		}
		else
		{
			// Perspective projection
			subfrustumProjection[2][2] = -(subfrustumFar + subfrustumNear) / (subfrustumFar - subfrustumNear);
			subfrustumProjection[3][2] = -(2.0f * subfrustumFar * subfrustumNear) / (subfrustumFar - subfrustumNear);
		}
		
		// Set subfrustum matrices
		subfrustums[i].setMatrices(getViewMatrix(), subfrustumProjection);
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
