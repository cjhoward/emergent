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

#ifndef EMERGENT_GRAPHICS_ANIMATION_CHANNEL_HPP
#define EMERGENT_GRAPHICS_ANIMATION_CHANNEL_HPP

#include <emergent/math/transform.hpp>
#include <set>
#include <tuple>
#include <vector>

namespace Emergent
{

class KeyFrame;

/**
 * A series of key frames which describe the motion of an individual bone in an animation sequence.
 *
 * @ingroup graphics
 */
class AnimationChannel
{
public:
	/**
	 * Creates an instance of AnimationChannel.
	 *
	 * @param channelID Specifies an ID with which to associate this animation channel.
	 */
	AnimationChannel(std::size_t channelID);
	
	/**
	 * Destroys an instance of AnimationChannel.
	 */
	~AnimationChannel();
	
	/**
	 * Creates a key frame.
	 *
	 * @param time Time at which to insert the keyframe.
	 */
	KeyFrame* insertKeyFrame(float time);
	
	/**
	 * Returns the ID of the this animation channel belongs.
	 */
	std::size_t getChannelID() const;
	
	/**
	 * Returns the number of key frames in the animation channel.
	 */
	std::size_t getKeyFrameCount() const;
	
	/**
	 * Returns the key frame at the specified index.
	 *
	 * @param index Specifies the index of a key frame.
	 * @exception IndexException Invalid key frame index.
	 */
	const KeyFrame* getKeyFrame(std::size_t index) const;
	
	/**
	 * @copydoc AnimationChannel::getKeyFrame() const
	 */
	KeyFrame* getKeyFrame(std::size_t index);
	
	/**
	 * Returns the indices of the keyframes on the left and right of the specified time.
	 *
	 * @param time Time for which to determine bounding keyframes.
	 */
	std::tuple<std::size_t, std::size_t> getBoundingKeyFrames(float time) const;
	
	/**
	 * Calculates the transform for this animation channel at the specified time by interpolating bounding keyframes.
	 *
	 * @param time Animation time
	 */
	Transform interpolateBoundingKeyFrames(float time) const;
	
private:
	std::size_t channelID;
	std::vector<KeyFrame*> keyFrames;
	std::set<float> timeline;
};

inline std::size_t AnimationChannel::getChannelID() const
{
	return channelID;
}

inline std::size_t AnimationChannel::getKeyFrameCount() const
{
	return keyFrames.size();
}

inline const KeyFrame* AnimationChannel::getKeyFrame(std::size_t index) const
{
	return keyFrames[index];
}

inline KeyFrame* AnimationChannel::getKeyFrame(std::size_t index)
{
	return keyFrames[index];
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_ANIMATION_CHANNEL_HPP
