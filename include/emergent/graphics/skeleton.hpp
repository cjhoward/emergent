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

#ifndef EMERGENT_GRAPHICS_SKELETON_HPP
#define EMERGENT_GRAPHICS_SKELETON_HPP

#include <cstdlib>
#include <string>
#include <vector>
#include <map>

namespace Emergent
{

class Bone;
class BindPose;

/**
 * Skeleton of a rigged model.
 *
 * @ingroup graphics
 */
class Skeleton
{
public:
	/**
	 * Creates an instance of Skeleton.
	 */
	Skeleton();
	
	/**
	 * Destroys an instance of Skeleton.
	 */
	~Skeleton();
	
	/**
	 * Forms a bind pose
	 */
	void calculateBindPose();
	
	/**
	 * Returns the number of bones in the skeleton.
	 */
	std::size_t getBoneCount() const;
	
	/**
	 * Returns the root bone of the skeleton.
	 *
	 * @return Pointer to the root bone.
	 */
	const Bone* getRootBone() const;
	
	/**
	 * @copydoc Skeleton::getRootBone() const
	 */
	Bone* getRootBone();
	
	/**
	 * Returns the specified bone.
	 *
	 * @param index Specifies the index of a bone.
	 * @return Pointer to the specified bone.
	 */
	const Bone* getBone(std::size_t index) const;
	
	/**
	 * @copydoc Skeleton::getBone(std::size_t) const
	 */
	Bone* getBone(std::size_t index);
	
	/**
	 * Returns the specified bone.
	 *
	 * @param name Specifies the name of a bone.
	 * @return Pointer to the bone, or `nullptr` if a bone with the specified name could not be found.
	 */
	const Bone* getBone(const std::string& name) const;
	
	/**
	 * @copydoc Skeleton::getBone(const std::string&) const
	 */
	Bone* getBone(const std::string& name);
	
	/**
	 * Returns the bind pose of the skeleton.
	 */
	const BindPose* getBindPose() const;
	
private:
	friend class Bone;
	
	/**
	 * Creates a new bone.
	 *
	 * @return Pointer to the created bone.
	 */
	Bone* createBone();
	
	/**
	 * Renames a bone.
	 *
	 * @param bone Specifies a bone to rename.
	 * @param name Specifies the new name of the bone. Must be unique to this bone set.
	 */
	void renameBone(Bone* bone, const std::string& name);
	
	Bone* root;
	std::vector<Bone*> bones;
	std::map<std::string, Bone*> boneMap;
	BindPose* bindPose;
};

inline std::size_t Skeleton::getBoneCount() const
{
	return bones.size();
}

inline const Bone* Skeleton::getRootBone() const
{
	return root;
}

inline Bone* Skeleton::getRootBone()
{
	return root;
}

inline const Bone* Skeleton::getBone(std::size_t index) const
{
	if (index >= bones.size())
	{
		return nullptr;
	}
	
	return bones[index];
}

inline Bone* Skeleton::getBone(std::size_t index)
{
	if (index >= bones.size())
	{
		return nullptr;
	}
	
	return bones[index];
}

inline const BindPose* Skeleton::getBindPose() const
{
	return bindPose;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SKELETON_HPP
