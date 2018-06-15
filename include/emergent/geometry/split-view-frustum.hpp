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

#ifndef EMERGENT_GEOMETRY_SPLIT_VIEW_FRUSTUM_HPP
#define EMERGENT_GEOMETRY_SPLIT_VIEW_FRUSTUM_HPP

#include <emergent/geometry/view-frustum.hpp>

namespace Emergent
{

/**
 * A view frustum which is split into parallel subfrustums.
 *
 * @ingroup geometry
 */
class SplitViewFrustum: public ViewFrustum
{
public:
	/**
	 * Creates an instance of SplitViewFrustum.
	 *
	 * @param subfrustumCount Number of subfrustums.
	 */
	explicit SplitViewFrustum(std::size_t subfrustumCount);
	
	/**
	 * Destroys an instance of SplitViewFrustum.
	 */
	~SplitViewFrustum();
	
	/**
	 * Sets the frustum split-scheme weight.
	 *
	 * @param weight Specifies the linear interpolation weight between uniform and logarithmic frustum-splitting schemes. A value of `0.0` indicates a uniform split scheme, while `1.`0 indicates a logarithmic split scheme. The initial value is `0.5`. 
	 */
	void setSplitSchemeWeight(float weight);
	
	/**
	 * Returns the number of subfrustums.
	 */
	std::size_t getSubfrustumCount() const;
	
	/**
	 * Returns the subfrustum at the specified index.
	 *
	 * @param index Index of a subfrustum.
	 */
	const ViewFrustum& getSubfrustum(std::size_t index) const;
	
	/**
	 * Returns the frustum split-scheme weight.
	 */
	float getSplitSchemeWeight() const;
	
	/**
	 * Returns the distance to the split at the specified index. The distance at index `0` is the near clipping plane. The distance at index `subfrustumCount` is the far clipping plane. The distances in-between are the split distances.
	 */
	float getSplitDistance(std::size_t index) const;
	
private:
	virtual void recalculateFrustum();
	
	/**
	 * Distributes the split subfrustums according to the parent view frustum and split scheme weight.
	 */
	void distributeSubfrustums();
	
	std::size_t subfrustumCount;
	ViewFrustum* subfrustums;
	float splitSchemeWeight;
	float* splitDistances;
};

inline std::size_t SplitViewFrustum::getSubfrustumCount() const
{
	return subfrustumCount;
}

inline const ViewFrustum& SplitViewFrustum::getSubfrustum(std::size_t index) const
{
	return subfrustums[index];
}

inline float SplitViewFrustum::getSplitSchemeWeight() const
{
	return splitSchemeWeight;
}

inline float SplitViewFrustum::getSplitDistance(std::size_t index) const
{
	return splitDistances[index];
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_SPLIT_VIEW_FRUSTUM_HPP
