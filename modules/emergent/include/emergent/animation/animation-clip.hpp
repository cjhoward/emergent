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

#ifndef EMERGENT_ANIMATION_ANIMATION_CLIP_HPP
#define EMERGENT_ANIMATION_ANIMATION_CLIP_HPP

#include <emergent/animation/animation-channel.hpp>
#include <emergent/math/interpolation.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <map>
#include <tuple>
#include <vector>

namespace Emergent
{

/**
 * A templated keyframe animation.
 *
 * @ingroup animation
 */
template <typename T>
class AnimationClip
{
public:
	/// Creates an animation clip
	AnimationClip();

	/// Destroys an animation clip
	~AnimationClip();

	/**
	 * Sets the function used to interpolate between keyframes.
	 *
	 * @param function Keyframe interpolation function.
	 */
	void setInterpolator(std::function<T(const T&, const T&, float)> function);

	/**
	 * Adds a channel to the animation clip.
	 *
	 * @param id ID of the animation channel.
	 * @return Newly created animation channel.
	 */
	AnimationChannel<T>* addChannel(std::size_t id);

	/**
	 * Removes a channel from the animation clip.
	 *
	 * @param index Index of the channel to remove.
	 */
	void removeChannelByIndex(std::size_t index);

	/**
	 * Removes a channel from the animation clip.
	 *
	 * @param id ID of the channel to remove.
	 */
	void removeChannelByID(std::size_t id);

	/**
	 * Removes all channels from the animation clip.
	 */
	void removeChannels();

	/// Returns the function used to interpolate between keyframes.
	std::function<T(const T&, const T&, float)> getInterpolator() const;

	/**
	 * Returns the number of channels in the animation clip.
	 */
	std::size_t getChannelCount() const;

	/**
	 * Returns the specified animation channel.
	 *
	 * @param index Index of an animation channel.
	 */
	const AnimationChannel<T>* getChannelByIndex(std::size_t index) const;

	/// @copydoc AnimationClip<T>::getChannelByIndex(std::size_t) const
	AnimationChannel<T>* getChannelByIndex(std::size_t index);

	/**
	 * Returns the specified animation channel.
	 *
	 * @param id ID of an animation channel.
	 */
	const AnimationChannel<T>* getChannelByID(std::size_t id) const;
	
	/// @copydoc AnimationClip<T>::getChannelByID(std::size_t) const
	AnimationChannel<T>* getChannelByID(std::size_t id);

	/**
	 * Returns the time frame of the animation clip.
	 */
	std::tuple<float, float> getTimeFrame() const;

private:
	friend class AnimationChannel<T>;

	/// Calculates the time frame according to the time frames of each animation channel.
	void calculateTimeFrame();

	std::function<T(const T&, const T&, float)> interpolator;
	std::vector<AnimationChannel<T>*> channels;
	std::map<std::size_t, AnimationChannel<T>*> channelMap;
	std::tuple<float, float> timeFrame;
};

template <typename T>
AnimationClip<T>::AnimationClip():
	interpolator(lerp<T>)
{
	calculateTimeFrame();
}

template <typename T>
AnimationClip<T>::~AnimationClip()
{
	removeChannels();
}

template <typename T>
void AnimationClip<T>::setInterpolator(std::function<T(const T&, const T&, float)> function)
{
	interpolator = function;
}

template <typename T>
AnimationChannel<T>* AnimationClip<T>::addChannel(std::size_t id)
{
	auto it = channelMap.find(id);
	if (it != channelMap.end())
	{
		return it->second;
	}

	AnimationChannel<T>* channel = new AnimationChannel<T>(this, id);

	channels.push_back(channel);
	channelMap[id] = channel;

	calculateTimeFrame();

	return channel;
}

template <typename T>
void AnimationClip<T>::removeChannelByIndex(std::size_t index)
{
	auto channelIt = channels.begin() + index;
	auto channelMapIt = channelMap.find((*channelIt)->getChannelID());

	delete (*channelIt);

	channels.erase(channelIt);
	channelMap.erase(channelMapIt);

	calculateTimeFrame();
}

template <typename T>
void AnimationClip<T>::removeChannelByID(std::size_t id)
{
	auto channelMapIt = channelMap.find(id);
	if (channelMapIt != channelMap.end())
	{
		AnimationChannel<T>* channel = channelMapIt->second;
		channelMap.erase(channelMapIt);

		for (auto channelIt = channels.begin(); channelIt != channels.end(); ++channelIt)
		{
			if ((*channelIt) == channel)
			{
				channels.erase(channelIt);
				break;
			}
		}

		delete channel;
	}

	calculateTimeFrame();
}

template <typename T>
void AnimationClip<T>::removeChannels()
{
	for (auto it = channels.begin(); it != channels.end(); ++it)
	{
		delete (*it);
	}

	channels.clear();
	channelMap.clear();

	calculateTimeFrame();
}


template <typename T>
inline std::function<T(const T&, const T&, float)> AnimationClip<T>::getInterpolator() const
{
	return interpolator;
}

template <typename T>
inline std::size_t AnimationClip<T>::getChannelCount() const
{
	return channels.size();
}

template <typename T>
inline const AnimationChannel<T>* AnimationClip<T>::getChannelByIndex(std::size_t index) const
{
	return channels[index];
}

template <typename T>
inline AnimationChannel<T>* AnimationClip<T>::getChannelByIndex(std::size_t index)
{
	return channels[index];
}

template <typename T>
inline const AnimationChannel<T>* AnimationClip<T>::getChannelByID(std::size_t id) const
{
	auto it = channelMap.find(id);
	if (it == channelMap.end())
	{
		return nullptr;
	}

	return it->second;
}


template <typename T>
inline AnimationChannel<T>* AnimationClip<T>::getChannelByID(std::size_t id)
{
	auto it = channelMap.find(id);
	if (it == channelMap.end())
	{
		return nullptr;
	}

	return it->second;
}

template <typename T>
inline std::tuple<float, float> AnimationClip<T>::getTimeFrame() const
{
	return timeFrame;
}

template <typename T>
void AnimationClip<T>::calculateTimeFrame()
{
	if (channels.empty())
	{
		std::get<0>(timeFrame) = 0.0f;
		std::get<1>(timeFrame) = 0.0f;
	}
	else
	{
		timeFrame = channels.front()->getTimeFrame();

		for (auto it = channels.begin() + 1; it != channels.end(); ++it)
		{
			std::tuple<float, float> channelTimeFrame = (*it)->getTimeFrame();
			std::get<0>(timeFrame) = std::min<float>(std::get<0>(timeFrame), std::get<0>(channelTimeFrame));
			std::get<1>(timeFrame) = std::max<float>(std::get<1>(timeFrame), std::get<1>(channelTimeFrame));
		}
	}
}

template <typename T>
void AnimationChannel<T>::calculateTimeFrame()
{
	if (keyframes.empty())
	{
		std::get<0>(timeFrame) = 0.0f;
		std::get<1>(timeFrame) = 0.0f;
	}
	else
	{
		std::get<0>(timeFrame) = std::get<0>(keyframes.front());
		std::get<1>(timeFrame) = std::get<0>(keyframes.back());
	}

	clip->calculateTimeFrame();
}

} // namespace Emergent

#endif // EMERGENT_ANIMATION_ANIMATION_CLIP_HPP

