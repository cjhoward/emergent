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

#ifndef EMERGENT_GRAPHICS_BONE_HPP
#define EMERGENT_GRAPHICS_BONE_HPP

#include <emergent/math/transform.hpp>
#include <cstdlib>
#include <string>
#include <vector>

namespace Emergent
{

class Skeleton;

/**
 * Skeletal animation bone.
 *
 * @ingroup graphics
 */
class Bone
{
public:
	/**
	 * Creates a child bone.
	 *
	 * @return Pointer to the created child bone.
	 */
	Bone* createChild();
	
	/**
	 * Sets the name of the bone.
	 *
	 * @param name Specifies the new name of the bone. Must be unique within the skeleton.
	 */
	void setName(const std::string& name);

	/**
	 * Sets the transform of this bone, relative to the parent bone.
	 *
	 * @param transform Specifies the local transform.
	 */
	void setRelativeTransform(const Transform& transform);

	/**
	 * Sets the length of the bone.
	 *
	 * @param length Specifies the bone length
	 */
	void setLength(float length);
	
	/**
	 * Returns the index of the bone.
	 */
	std::size_t getIndex() const;

	/**
	 * Returns the name of the bone.
	 */
	const std::string& getName() const;
	
	/**
	 * Returns the parent bone, if any.
	 */
	const Bone* getParent() const;
	
	/**
	 * @copydoc Bone::getParent() const
	 */
	Bone* getParent();

	/**
	 * Returns the number of child bones.
	 */
	std::size_t getChildCount() const;
	
	/**
	 * Returns the specified child bone.
	 *
	 * @param index Specifies the index of the child bone, relative to how many children exist in this bone.
	 * @return Pointer to the child bone.
	 */
	const Bone* getChild(std::size_t index) const;
	
	/**
	 * @copydoc Bone::getChild(std::size_t) const;
	 */
	Bone* getChild(std::size_t index);
	
	/**
	 * Returns the specified child bone.
	 *
	 * @param name Specifies the name of a child bone.
	 * @return Pointer to the child bone, or `nullptr` if a child bone with the specified name could not be found.
	 */
	const Bone* getChild(const std::string& name) const;
	
	/**
	 * @copydoc Bone::getChild(const std::string&) const
	 */
	Bone* getChild(const std::string& name);

	/**
	 * Returns the transform of this bone, relative to the parent bone.
	 */
	const Transform& getRelativeTransform() const;

	/**
	 * Returns the length of the bone.
	 */
	float getLength() const;
	
private:
	friend class Skeleton;
	
	/**
	 * Creates an instance of Bone.
	 *
	 * @param skeleton Specifies the skeleton to which this bone belongs.
	 * @param index Specifies the index of the bone.
	 */
	Bone(Skeleton* skeleton, std::size_t index);
	
	/**
	 * Destroys an instance of Bone.
	 */
	~Bone();
	
	Skeleton* skeleton;
	std::size_t index;
	Bone* parent;
	std::string name;
	std::vector<Bone*> children;
	Transform relativeTransform;
	float length;
};

inline void Bone::setRelativeTransform(const Transform& transform)
{
	this->relativeTransform = transform;
}

inline void Bone::setLength(float length)
{
	this->length = length;
}

inline std::size_t Bone::getIndex() const
{
	return index;
}

inline const std::string& Bone::getName() const
{
	return name;
}

inline const Bone* Bone::getParent() const
{
	return parent;
}

inline Bone* Bone::getParent()
{
	return parent;
}

inline std::size_t Bone::getChildCount() const
{
	return children.size();
}

inline const Bone* Bone::getChild(std::size_t index) const
{
	if (index >= children.size())
	{
		return nullptr;
	}
	
	return children[index];
}

inline Bone* Bone::getChild(std::size_t index)
{
	if (index >= children.size())
	{
		return nullptr;
	}
	
	return children[index];
}

inline const Transform& Bone::getRelativeTransform() const
{
	return relativeTransform;
}

inline float Bone::getLength() const
{
	return length;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_BONE_HPP
