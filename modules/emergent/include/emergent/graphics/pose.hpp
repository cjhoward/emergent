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

#ifndef EMERGENT_GRAPHICS_POSE_HPP
#define EMERGENT_GRAPHICS_POSE_HPP

#include <emergent/math/types.hpp>
#include <cstdlib>
#include <vector>

namespace Emergent
{

class Skeleton;
class Bone;

/**
 * Contains transforms corresponding to each bone in a skeleton.
 *
 * @ingroup graphics
 */
class Pose
{
public:
	/**
	 * Creates an instance of Pose.
	 *
	 * @param skeleton Specifies the skeleton with which to associate this pose.
	 */
	Pose(const Skeleton* skeleton);

	/**
	 * Creates an instance of Pose.
	 */
	Pose();
	
	/**
	 * Destroys an instance of Pose.
	 */
	virtual ~Pose();

	/**
	 * Manually recalculates all flagged absolute transforms.
	 */
	void concatenate() const;
	
	/**
	 * Copies the transforms of a pose into this pose.
	 *
	 * @param pose Pose from which to copy transforms.
	 */
	void copy(const Pose* pose);
	
	/**
	 * Resets the transform of the specified bone to its bind pose transform.
	 *
	 * @param index Index of the bone transform to reset.
	 */
	void reset(std::size_t index);
	
	/**
	 * Resets all transforms to bind pose transforms.
	 */
	void reset();
	
	/**
	 * Sets the transform of the specified bone, relative to its parent bone.
	 *
	 * @param index Specifies the index of a bone.
	 * @param transform Specifies the transform.
	 */
	void setRelativeTransform(std::size_t index, const Transform& transform);
	
	/**
	 * Returns the skeleton with which this pose is associated.
	 *
	 * @return Skeleton with which this pose is associated.
	 */
	const Skeleton* getSkeleton() const;
	
	/**
	 * Returns the transform of the specified bone, relative to its parent bone.
	 *
	 * @param index Specifies the index of a bone.
	 * @return Transform of the specified bone, relative to its parent bone.
	 */
	const Transform& getRelativeTransform(std::size_t index) const;

	/**
	 * Returns the absolute transform of the specified bone.
	 *
	 * @param index Specifies the index of a bone.
	 * @return Absolute transform of the specified bone.
	 */
	const Transform& getAbsoluteTransform(std::size_t index) const;

	/**
	 * Returns the matrix palette used for skinning.
	 */
	const Matrix4* getMatrixPalette() const;

	/**
	 * Returns `true` if the pose requires concatenation.
	 */
	bool isDirty() const;

protected:
	/**
	 * Sets the dirty flag for a bone and its children, indicating their absolute transforms require updating.
	 *
	 * @param index Specifies the index of a bone.
	 */
	void setDirty(std::size_t index) const;

	/**
	 * Calculates absolute transforms and skinning matrices by concatenating relative transforms.
	 *
	 * @param index Specifies the index of the first bone from which concatenation will begin.
	 */
	void concatenate(const Bone* bone) const;

	/**
	 * Calculates the absolute transform for a bone.
	 *
	 * @param bone Specifies a bone.
	 */
	virtual void calculateAbsoluteTransform(const Bone* bone) const;

	/**
	 * Calculates the skinning matrix for a bone.
	 *
	 * @param bone Specifies a bone.
	 */
	virtual void calculateSkinningMatrix(const Bone* bone) const;
	
	const Skeleton* skeleton;
	std::vector<Transform> relativeTransforms;
	mutable std::vector<Transform> absoluteTransforms;
	mutable std::vector<Matrix4> matrixPalette;
	mutable std::vector<bool> dirtyFlags;
	mutable std::size_t dirtyCount;
};

inline void Pose::setRelativeTransform(std::size_t index, const Transform& transform)
{
	relativeTransforms[index] = transform;
	setDirty(index);
}

inline const Skeleton* Pose::getSkeleton() const
{
	return skeleton;
}

inline const Transform& Pose::getRelativeTransform(std::size_t index) const
{
	return relativeTransforms[index];
}

inline const Matrix4* Pose::getMatrixPalette() const
{
	return matrixPalette.data();
}

inline bool Pose::isDirty() const
{
	return (dirtyCount > 0);
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_POSE_HPP
