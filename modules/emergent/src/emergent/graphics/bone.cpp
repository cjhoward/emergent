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

#include <emergent/graphics/bone.hpp>
#include <emergent/graphics/skeleton.hpp>

namespace Emergent
{

Bone::Bone(Skeleton* skeleton, std::size_t index):
	skeleton(skeleton),
	index(index),
	parent(nullptr),
	relativeTransform(Transform::getIdentity()),
	length(1.0f)
{}

Bone::~Bone()
{}

Bone* Bone::createChild()
{
	Bone* child = skeleton->createBone();
	child->parent = this;
	children.push_back(child);
	
	return child;
}

void Bone::setName(const std::string& name)
{
	skeleton->renameBone(this, name);
}

const Bone* Bone::getChild(const std::string& name) const
{
	const Bone* bone = skeleton->getBone(name);
	if (bone && bone->parent == this)
	{
		return bone;
	}
	
	return nullptr;
}

Bone* Bone::getChild(const std::string& name)
{
	Bone* bone = skeleton->getBone(name);
	if (bone && bone->parent == this)
	{
		return bone;
	}
	
	return nullptr;
}

} // namespace Emergent
