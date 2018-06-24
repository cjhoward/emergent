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

#ifndef EMERGENT_ANIMATION_ANIMATION_CHANNEL_HPP
#define EMERGENT_ANIMATION_ANIMATION_CHANNEL_HPP

#include <cstdlib>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

namespace Emergent
{

template <typename T>
class AnimationClip;

/**
 * A tuple containing the keyframe playback position and the keyframe value.
 *
 * @ingroup animation
 */
template <typename T>
using Keyframe = std::tuple<float, T*>;

/**
 * Describes the keyframe animation of a single property.
 * 
 * @ingroup animation
 */
template <typename T>
class AnimationChannel
{
public:
	/**
	 * Inserts a keyframe.
	 *
	 * @param position Playback position, in seconds, at which a keyframe should be inserted.
	 * @param value Value of the keyframe.
	 * @return The keyframe at the specified playback position.
	 */
	Keyframe<T> insertKeyframe(float position, const T& value);

	/**
	 * Removes a keyframe.
	 *
	 * @param index Index of the keyframe to remove.
	 */
	void removeKeyframe(std::size_t index);

	/**
	 * Removes all keyframes.
	 */
	void removeKeyframes();

	/// Returns the animation channel ID.
	std::size_t getChannelID() const;

	/// Returns the number of keyframes in this animation channel.
	std::size_t getKeyframeCount() const;

	/// Returns true if this animation channel has any keyframes.
	bool hasKeyframes() const;

	/// Returns the keyframe at the specified index.
	Keyframe<T> getKeyframe(std::size_t index) const;

	/**
	 * Returns the indices of the bounding keyframes for the specified playback position.
	 *
	 * @param position Playback position, in seconds, for which to find the bounding keyframes.
	 * @return Indicies of the bounding keyframes.
	 */
	std::tuple<std::size_t, std::size_t> getBoundingKeyframes(float position) const;

	/**
	 * Returns the time frame of the animation channel.
	 */
	std::tuple<float, float> getTimeFrame() const;

private:
	friend class AnimationClip<T>;

	/**
	 * Creates an animation channel.
	 *
	 * @param clip Parent animation clip.
	 * @param id Channel ID.
	 */
	AnimationChannel(AnimationClip<T>* clip, std::size_t id);

	/// Destroys an animation channel.
	~AnimationChannel();

	/// Calclate the time frame of this animation channel
	void calculateTimeFrame();

	AnimationClip<T>* clip;
	std::size_t id;
	std::vector<Keyframe<T>> keyframes;
	std::set<float> timeline;
	std::tuple<float, float> timeFrame;
};

template <typename T>
AnimationChannel<T>::AnimationChannel(AnimationClip<T>* clip, std::size_t id):
	clip(clip),
	id(id)
{
	std::get<0>(timeFrame) = 0.0f;
	std::get<1>(timeFrame) = 0.0f;
}

template <typename T>
AnimationChannel<T>::~AnimationChannel()
{
	removeKeyframes();
}

template <typename T>
Keyframe<T> AnimationChannel<T>::insertKeyframe(float position, const T& value)
{
	// Check if keyframe already exists at the specified playback position
	auto it = timeline.find(position);
	if (it != timeline.end())
	{
		std::size_t index = std::distance(timeline.begin(), it);
		return keyframes[index];
	}

	// Allocate keyframe
	Keyframe<T> keyframe;
	std::get<0>(keyframe) = position;
	std::get<1>(keyframe) = new T(value);
	
	// Find the keyframe which comes after the inserted position
	it = timeline.upper_bound(position);
	if (it != timeline.end())
	{
		// Determine position at which to insert keyframe
		std::size_t index = std::distance(timeline.begin(), it);
		
		// Insert keyframe at specified position
		keyframes.insert(keyframes.begin() + index, keyframe);
	}
	else
	{
		// No keyframe exists after inserted time, add keyframe at back of the vector
		keyframes.push_back(keyframe);
	}
	
	// Insert time into timeline
	timeline.insert(position);

	calculateTimeFrame();
	
	return keyframe;
}

template <typename T>
void AnimationChannel<T>::removeKeyframe(std::size_t index)
{
	auto keyframesIt = keyframes.begin() + index;
	auto timelineIt = timeline.find(std::get<0>(*keyframesIt));

	delete std::get<1>(*keyframesIt);
	
	keyframes.erase(keyframesIt);
	timeline.erase(timelineIt);

	calculateTimeFrame();
}

template <typename T>
void AnimationChannel<T>::removeKeyframes()
{
	for (auto it = keyframes.begin(); it != keyframes.end(); ++it)
	{
		delete std::get<1>(*it);
	}

	keyframes.clear();
	timeline.clear();

	calculateTimeFrame();
}

template <typename T>
inline std::size_t AnimationChannel<T>::getChannelID() const
{
	return id;
}

template <typename T>
inline std::size_t AnimationChannel<T>::getKeyframeCount() const
{
	return keyframes.size();
}

template <typename T>
inline bool AnimationChannel<T>::hasKeyframes() const
{
	return (!keyframes.empty());
}

template <typename T>
inline Keyframe<T> AnimationChannel<T>::getKeyframe(std::size_t index) const
{
	return keyframes[index];
}

template <typename T>
std::tuple<std::size_t, std::size_t> AnimationChannel<T>::getBoundingKeyframes(float position) const
{
	auto it = timeline.upper_bound(position);
	if (it == timeline.begin())
	{
		return std::make_tuple(0, 0);
	}
	else if (it == timeline.end())
	{
		return std::make_tuple(keyframes.size() - 1, keyframes.size() - 1);
	}

	std::size_t rightIndex = std::distance(timeline.begin(), it);
	std::size_t leftIndex = rightIndex - 1;
	
	return std::make_tuple(leftIndex, rightIndex);
}

template <typename T>
inline std::tuple<float, float> AnimationChannel<T>::getTimeFrame() const
{
	return timeFrame;
}

} // namespace Emergent

#endif // EMERGENT_ANIMATION_ANIMATION_CHANNEL_HPP

