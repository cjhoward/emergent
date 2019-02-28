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

#ifndef EMERGENT_GRAPHICS_BIND_POSE_HPP
#define EMERGENT_GRAPHICS_BIND_POSE_HPP

#include <emergent/graphics/pose.hpp>

namespace Emergent
{

/**
 * Skeleton pose which additionally stores inverse absolute transforms.
 *
 * @ingroup graphics
 */
class BindPose: public Pose
{
public:
	using Pose::concatenate;

	/**
	 * Creates an instance of Pose.
	 *
	 * @param skeleton Specifies the skeleton with which to associate this bind pose.
	 */
	BindPose(const Skeleton* skeleton);

	/**
	 * Creates an instance of Pose.
	 */
	BindPose();
	
	/**
	 * Destroys an instance of Pose.
	 */
	virtual ~BindPose();

	/**
	 * Returns the inverse absolute transform of the specified bone.
	 *
	 * @param index Specifies the index of a bone.
	 * @return Inverse absolute transform of the specified bone.
	 */
	const Transform& getInverseAbsoluteTransform(std::size_t index) const;

private:
	/// @copydoc Pose::calculateAbsoluteTransform
	virtual void calculateAbsoluteTransform(const Bone* bone) const;

	/// @copydoc Pose::calculateSkinningMatrix
	virtual void calculateSkinningMatrix(const Bone* bone) const;
	
	mutable std::vector<Transform> inverseAbsoluteTransforms;
};

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_BIND_POSE_HPP
