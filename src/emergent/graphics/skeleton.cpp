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

#include <emergent/graphics/skeleton.hpp>
#include <emergent/graphics/bone.hpp>
#include <emergent/graphics/bind-pose.hpp>
#include <iostream>

namespace Emergent
{

Skeleton::Skeleton():
	bindPose(nullptr)
{
	root = createBone();
	
	/*
	bindPose = new SkeletonBindPose(this);
	for (std::size_t i = 0; i < bones.size(); ++i)
	{
		bindPose->setRelativeTransform(i, bones[i]->getRelativeTransform());
	}
	bindPose->concatenate();
	*/
}

Skeleton::~Skeleton()
{
	delete bindPose;
	
	for (auto it = bones.begin(); it != bones.end(); ++it)
	{
		delete *it;
	}
}

const Bone* Skeleton::getBone(const std::string& name) const
{
	auto it = boneMap.find(name);
	if (it != boneMap.end())
	{
		return it->second;
	}
	
	return nullptr;
}

Bone* Skeleton::getBone(const std::string& name)
{
	auto it = boneMap.find(name);
	if (it != boneMap.end())
	{
		return it->second;
	}
	
	return nullptr;
}

Bone* Skeleton::createBone()
{
	Bone* bone = new Bone(this, bones.size());
	bones.push_back(bone);
	
	return bone;
}

void Skeleton::renameBone(Bone* bone, const std::string& name)
{
	// Check for duplicate names
	if (!name.empty())
	{
		Bone* duplicate = getBone(name);
		if (duplicate != nullptr && duplicate != bone)
		{
			std::cerr << "Attempting to create duplicate bone in skeleton" << std::endl;
			return;
		}
	}
	
	// Erase old bone map entry
	if (!bone->name.empty())
	{
		boneMap.erase(boneMap.find(bone->name));
	}
	
	// Rename bone and add to bone map
	bone->name = name;
	if (!name.empty())
	{
		boneMap[name] = bone;
	}
}

} // namespace Emergent

