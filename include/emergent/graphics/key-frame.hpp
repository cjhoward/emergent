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
	 * @param time Specifies the time at which this keyframe occurs.
	 */
	KeyFrame(float time);
	
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
	 * Returns the time of the key frame
	 */
	float getTime() const;
	
	/**
	 * Returns the transform at this key frame.
	 */
	const Transform& getTransform() const;
	
private:
	float time;
	Transform transform;
};

inline KeyFrame::KeyFrame(float time):
	time(time),
	transform(Transform::getIdentity())
{}

inline KeyFrame::~KeyFrame()
{}

inline void KeyFrame::setTransform(const Transform& transform)
{
	this->transform = transform;
}

inline float KeyFrame::getTime() const
{
	return time;
}

inline const Transform& KeyFrame::getTransform() const
{
	return transform;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_KEY_FRAME_HPP
