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

#include <emergent/graphics/animation-channel.hpp>
#include <emergent/graphics/key-frame.hpp>

namespace Emergent
{

AnimationChannel::AnimationChannel(std::size_t channelID):
	channelID(channelID)
{}

AnimationChannel::~AnimationChannel()
{
	for (KeyFrame* keyFrame: keyFrames)
	{
		delete keyFrame;
	}
}

KeyFrame* AnimationChannel::insertKeyFrame(float time)
{
	// Check if keyframe already exists at the specified time
	if (timeline.find(time) != timeline.end())
	{
		return nullptr;
	}
	
	// Allocate keyframe
	KeyFrame* keyFrame = new KeyFrame(time);
	
	// Find the keyframe which comes after the inserted time
	auto it = timeline.upper_bound(time);
	if (it != timeline.end())
	{
		// Determine position at which to insert keyframe
		std::size_t index = std::distance(timeline.begin(), it);
		
		// Insert keyframe at specified position
		keyFrames.insert(keyFrames.begin() + index, keyFrame);
	}
	else
	{
		// No keyframe exists after inserted time, add keyframe at back of the vector
		keyFrames.push_back(keyFrame);
	}
	
	// Insert time into timeline
	timeline.insert(time);
	
	return keyFrame;
}

std::tuple<std::size_t, std::size_t> AnimationChannel::getBoundingKeyFrames(float time) const
{
	auto it = timeline.upper_bound(time);
	if (it == timeline.end() || it == timeline.begin())
	{
		return std::make_tuple(keyFrames.size() - 1, keyFrames.size() - 1);
	}
	
	std::size_t rightIndex = std::distance(timeline.begin(), it);
	std::size_t leftIndex = rightIndex - 1;
	
	return std::make_tuple(leftIndex, rightIndex);
}

Transform AnimationChannel::interpolateBoundingKeyFrames(float time) const
{
	// Determine bounding keyframes for the specified time
	auto boundingKeyFrames = getBoundingKeyFrames(time);
	
	const KeyFrame* left = keyFrames[std::get<0>(boundingKeyFrames)];
	const KeyFrame* right = keyFrames[std::get<1>(boundingKeyFrames)];
	
	if (left == right)
	{
		return left->getTransform();
	}
	
	const Transform& leftTransform = left->getTransform();
	const Transform& rightTransform = right->getTransform();
	
	// Calculate interpolation factor according to specified time
	float interpolationFactor = (time - left->getTime()) / (right->getTime() - left->getTime());
	
	// Interpolate between left and right keyframes
	Transform interpolatedTransform;
	interpolatedTransform.translation = glm::lerp(leftTransform.translation, rightTransform.translation, interpolationFactor);
	interpolatedTransform.rotation = glm::slerp(leftTransform.rotation, rightTransform.rotation, interpolationFactor);
	interpolatedTransform.scale = glm::lerp(leftTransform.scale, rightTransform.scale, interpolationFactor);
	
	return interpolatedTransform;
}

} // namespace Emergent
