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

#include <emergent/graphics/bind-pose.hpp>
#include <emergent/graphics/skeleton.hpp>
#include <emergent/graphics/bone.hpp>

namespace Emergent
{

BindPose::BindPose(const Skeleton* skeleton):
	Pose(skeleton)
{
	inverseAbsoluteTransforms.resize(skeleton->getBoneCount());
}

BindPose::BindPose()
{}

BindPose::~BindPose()
{}

const Transform& BindPose::getInverseAbsoluteTransform(std::size_t index) const
{
	if (dirtyFlags[index])
	{
		// Find top-most bone which is flagged
		const Bone* bone = skeleton->getBone(index);
		while (bone->getParent() && dirtyFlags[bone->getParent()->getIndex()])
		{
			bone = bone->getParent();
		}

		// Concatenate the hierarchy
		concatenate(bone);
	}
	
	return inverseAbsoluteTransforms[index];
}

void BindPose::calculateAbsoluteTransform(const Bone* bone) const
{
	std::size_t index = bone->getIndex();

	Pose::calculateAbsoluteTransform(bone);
	inverseAbsoluteTransforms[index] = absoluteTransforms[index].inverse();
}

void BindPose::calculateSkinningMatrix(const Bone* bone) const
{
	matrixPalette[bone->getIndex()] = glm::inverse(absoluteTransforms[bone->getIndex()].toMatrix());
}

} // namespace Emergent
