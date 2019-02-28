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

#include <emergent/graphics/pose.hpp>
#include <emergent/graphics/skeleton.hpp>
#include <emergent/graphics/bone.hpp>
#include <emergent/graphics/bind-pose.hpp>

namespace Emergent
{

Pose::Pose(const Skeleton* skeleton):
	skeleton(skeleton)
{
	relativeTransforms.resize(skeleton->getBoneCount());
	absoluteTransforms.resize(skeleton->getBoneCount());
	matrixPalette.resize(skeleton->getBoneCount());
	dirtyFlags.resize(skeleton->getBoneCount(), true);
	dirtyCount = dirtyFlags.size();
}

Pose::Pose()
{}

Pose::~Pose()
{}

void Pose::concatenate() const
{
	for (std::size_t i = 0; dirtyCount > 0 && i < dirtyFlags.size(); ++i)
	{
		if (dirtyFlags[i])
		{
			// Find top-most bone which is flagged
			const Bone* bone = skeleton->getBone(i);
			while (bone->getParent() && dirtyFlags[bone->getParent()->getIndex()])
			{
				bone = bone->getParent();
			}

			// Concatenate the hierarchy
			concatenate(bone);
		}
	}
}

void Pose::copy(const Pose* pose)
{
	for (std::size_t i = 0; i < skeleton->getBoneCount(); ++i)
	{
		setRelativeTransform(i, pose->getRelativeTransform(i));
	}
}

void Pose::reset(std::size_t index)
{
	setRelativeTransform(index, skeleton->getBindPose()->getRelativeTransform(index));
}

void Pose::reset()
{
	for (std::size_t i = 0; i < skeleton->getBoneCount(); ++i)
	{
		setRelativeTransform(i, skeleton->getBindPose()->getRelativeTransform(i));
	}
}

const Transform& Pose::getAbsoluteTransform(std::size_t index) const
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
	
	return absoluteTransforms[index];
}

void Pose::setDirty(std::size_t index) const
{
	dirtyFlags[index] = true;
	++dirtyCount;

	const Bone* bone = skeleton->getBone(index);
	for (std::size_t i = 0; i < bone->getChildCount(); ++i)
	{
		setDirty(bone->getChild(i)->getIndex());
	}
}

void Pose::concatenate(const Bone* bone) const
{
	calculateAbsoluteTransform(bone);
	calculateSkinningMatrix(bone);

	// Clear dirty flag
	dirtyFlags[bone->getIndex()] = false;
	--dirtyCount;

	// Concatenate child bones
	for (std::size_t i = 0; i < bone->getChildCount(); ++i)
	{
		concatenate(bone->getChild(i));
	}
}

void Pose::calculateAbsoluteTransform(const Bone* bone) const
{
	std::size_t index = bone->getIndex();

	// Calculate absolute transform
	if (bone->getParent())
	{
		std::size_t parentIndex = bone->getParent()->getIndex();
		absoluteTransforms[index] = absoluteTransforms[parentIndex] * relativeTransforms[index];
	}
	else
	{
		absoluteTransforms[index] = relativeTransforms[index];
	}
}

void Pose::calculateSkinningMatrix(const Bone* bone) const
{
	std::size_t index = bone->getIndex();
	const BindPose* bindPose = skeleton->getBindPose();

	matrixPalette[index] = absoluteTransforms[index].toMatrix() * bindPose->getMatrixPalette()[index];
}

} // namespace Emergent
