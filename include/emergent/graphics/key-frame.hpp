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

#ifndef EMERGENT_GRAPHICS_KEY_FRAME_HPP
#define EMERGENT_GRAPHICS_KEY_FRAME_HPP

#include <emergent/math/transform.hpp>

namespace Emergent
{

/**
 * A key frame which describes a transform in an animation channel.
 *
 * @ingroup graphics
 */
class KeyFrame
{
public:
	/**
	 * Creates an instance of KeyFrame.
	 *
	 * @param transform Specifies the key frame transform.
	 */
	KeyFrame(const Transform& transform);

	/**
	 * Creates an instance of KeyFrame.
	 */
	KeyFrame();
	
	/**
	 * Destroys an instance of KeyFrame.
	 */
	~KeyFrame();
	
	/**
	 * Sets the transform at this key frame.
	 *
	 * @param transform Specifies a transform.
	 */
	void setTransform(const Transform& transform);

	/**
	 * Returns the transform at this key frame.
	 */
	const Transform& getTransform() const;
	
private:
	Transform transform;
};

inline KeyFrame::KeyFrame(const Transform& transform):
	transform(transform)
{}

inline KeyFrame::KeyFrame():
	KeyFrame(Transform::getIdentity())
{}

inline KeyFrame::~KeyFrame()
{}

inline void KeyFrame::setTransform(const Transform& transform)
{
	this->transform = transform;
}

inline const Transform& KeyFrame::getTransform() const
{
	return transform;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_KEY_FRAME_HPP
