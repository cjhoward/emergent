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

#ifndef EMERGENT_ANIMATION_ANIMATION_HPP
#define EMERGENT_ANIMATION_ANIMATION_HPP

#include <emergent/animation/animation-channel.hpp>
#include <emergent/animation/animation-clip.hpp>
#include <functional>
#include <tuple>
#include <utility>

namespace Emergent
{

/**
 * Abstract base class for animations.
 *
 * @ingroup animation
 */
class AnimationBase
{
public:
	/// Creates an animation base.
	AnimationBase();

	/// Destroys an animation base.
	virtual ~AnimationBase() = default;

	/**
	 * Starts playing the animation.
	 */
	void play();

	/**
	 * Stops playing the animation while preserving the elapsed time.
	 */
	void pause();

	/**
	 * Stops playing the animation and rewinds the elapsed time.
	 */
	void stop();

	/**
	 * Skips to the specified playback position.
	 *
	 * @param position Playback position, in seconds.
	 */
	void seek(float position);

	/**
	 * Sets the elapsed time to the start time if the playback speed is positive, or to the end time if the playback speed is negative.
	 */
	void rewind();

	/**
	 * Sets the time frame of the animation.
	 *
	 * @param start Start time of the animation, in seconds.
	 * @param end End time of the animation, in seconds.
	 */
	void setTimeFrame(float start, float end);

	/**
	 * Sets the time frame of the animation.
	 *
	 * @param timeFrame Tuple containing the start and end times of the animation, in seconds.
	 */
	void setTimeFrame(const std::tuple<float, float>& timeFrame);

	
	/**
	 * Sets the playback speed of the animation. A negative value means the animation will play in reverse.
	 *
	 * @param speed Animation playback speed multiplier,
	 */
	void setSpeed(float speed);

	/**
	 * Enables or disables looping the animation.
	 */
	void setLoop(bool loop);

	/// Sets the callback for when the animation starts playing.
	void setStartCallback(const std::function<void()> callback);

	/// Sets the callback for when the animation stops playing.
	void setEndCallback(const std::function<void()> callback);

	/// Sets the callback for when the animation loops.
	void setLoopCallback(const std::function<void()> callback);

	/// Returns the animation time frame.
	std::tuple<float, float> getTimeFrame() const;

	/// Returns true if the animation is currently playing.
	bool isPlaying() const;

	/// Returns the curent playback position of the animation.
	float getPosition() const;

	/// Returns the current playback speed multiplier.
	float getSpeed() const;

	/// Returns true if the animation is looping.
	bool isLooping() const;

private:
	friend class Animator;

	/**
	 * Progresses the animation.
	 *
	 * @param dt Delta-time, in seconds.
	 */
	void animate(float dt);

	/**
	 * Interpolates the keyframes of each animation channel according the playback time.
	 *
	 * @param time Playback time.
	 */
	virtual void interpolate(float time) = 0;

	float startTime;
	float endTime;
	float speed;
	bool loop;
	bool playing;
	float position;
	std::function<void()> startCallback;
	std::function<void()> endCallback;
	std::function<void()> loopCallback;
};

inline std::tuple<float, float> AnimationBase::getTimeFrame() const
{
	return std::make_tuple(startTime, endTime);
}

inline bool AnimationBase::isPlaying() const
{
	return playing;
}

inline float AnimationBase::getPosition() const
{
	return position;
}

inline float AnimationBase::getSpeed() const
{
	return speed;
}

inline bool AnimationBase::isLooping() const
{
	return loop;
}

/**
 * Animation
 *
 * @ingroup animation
 */
template <typename T>
class Animation: public AnimationBase
{
public:
	/// Creates an animation.
	Animation();

	/// Destroys an animation
	virtual ~Animation();

	/**
	 * Sets the animation clip.
	 *
	 * @param clip Animation clip to set.
	 */
	void setClip(const AnimationClip<T>* clip);

	/**
	 * Sets the callback for each time an animation channel is animated. The first parameter in the callback is the ID of an animation channel. The second parameter is the interpolated frame of the animation channel.
	 */
	void setAnimateCallback(const std::function<void(std::size_t, const T&)> callback);

private:
	virtual void interpolate(float time);

	const AnimationClip<T>* clip;
	std::function<void(std::size_t, const T&)> animateCallback;
};

template <typename T>
Animation<T>::Animation():
	clip(nullptr),
	animateCallback(nullptr)
{}

template <typename T>
Animation<T>::~Animation()
{}

template <typename T>
inline void Animation<T>::setClip(const AnimationClip<T>* clip)
{
	this->clip = clip;
}

template <typename T>
void Animation<T>::setAnimateCallback(const std::function<void(std::size_t, const T&)> callback)
{
	animateCallback = callback;
}

template <typename T>
void Animation<T>::interpolate(float time)
{
	if (!clip || !animateCallback)
	{
		return;
	}

	// For each animation channel in the clip
	for (std::size_t i = 0; i < clip->getChannelCount(); ++i)
	{
		const AnimationChannel<T>* channel = clip->getChannelByIndex(i);

		// Skip empty channels
		if (!channel->hasKeyframes())
		{
			continue;
		}

		// Get bounding keyframes for the current time
		std::tuple<std::size_t, std::size_t> keyframes = channel->getBoundingKeyframes(time);
		Keyframe<T> left = channel->getKeyframe(std::get<0>(keyframes));
		Keyframe<T> right = channel->getKeyframe(std::get<1>(keyframes));

		// If only one bounding keyframe
		if (std::get<0>(keyframes) == std::get<1>(keyframes))
		{
			// Pass keyframe to the animate callback
			animateCallback(channel->getChannelID(), *std::get<1>(left));
		}
		else
		{
			// Determine interpolation ratio according to the time
			float interpolationRatio = (time - std::get<0>(left)) / (std::get<0>(right) - std::get<0>(left));

			// Interpolate between the left and right keyframes
			T frame = clip->getInterpolator()(*std::get<1>(left), *std::get<1>(right), interpolationRatio);

			// Pass interpolated frame to the animate callback
			animateCallback(channel->getChannelID(), frame);
		}
	}
}

} // namespace Emergent

#endif // EMERGENT_ANIMATION_ANIMATION_HPP

