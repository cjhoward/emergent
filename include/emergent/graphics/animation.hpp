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

#ifndef EMERGENT_GRAPHICS_ANIMATION_HPP
#define EMERGENT_GRAPHICS_ANIMATION_HPP

#include <string>
#include <vector>

namespace Emergent
{

class AnimationChannel;
class Pose;

/**
 * A skeletal animation.
 *
 * @ingroup graphics
 */
class Animation
{
public:
	/**
	 * Creates an instance of Animation.
	 */
	Animation();
	
	/**
	 * Destroys an instance of Animation.
	 */
	~Animation();

	/**
	 * Creates a new animation channel.
	 *
	 * @param channelID Specifies an ID with which to associate the animation channel.
	 * @return Pointer to the created animation channel.
	 */
	AnimationChannel* createChannel(std::size_t channelID);
	
	/**
	 * Applies this animation to a skeleton pose. Note that Pose::concatenate() needs to be called after for the animation to take effect.
	 *
	 * @param pose Skeleton pose to be animated
	 * @param time Time in the animation from which to apply.
	 */
	void animate(Pose* pose, float time) const;
	
	/**
	 * Sets the name of the animation.
	 *
	 * @param name Specifies the new name of the animation. Must be unique within the skeleton.
	 */
	void setName(const std::string& name);
	
	/**
	 * Sets the time frame of the animation.
	 *
	 * @param start Start time of the animation.
	 * @param end End time of the animation.
	 */
	void setTimeFrame(float start, float end);
	
	/**
	 * Returns the name of the animation.
	 */
	const std::string& getName() const;
	
	/**
	 * Returns the start time of the animation.
	 */
	float getStartTime() const;
	
	/**
	 * Returns the end time of the animation.
	 */
	float getEndTime() const;
	
	/**
	 * Returns the number of animation channels in the animation.
	 */
	std::size_t getChannelCount() const;
	
	/**
	 * Returns the animation channel at the specified index.
	 *
	 * @param index Specifies the index of an animation channel.
	 *
	 * @exception IndexException Invalid animation channel index.
	 */
	const AnimationChannel* getChannel(std::size_t index) const;
	
	/**
	 * @copydoc Animation::getChannel() const
	 */
	AnimationChannel* getChannel(std::size_t index);
	
private:	
	std::string name;
	float startTime;
	float endTime;
	std::vector<AnimationChannel*> channels;
};

inline const std::string& Animation::getName() const
{
	return name;
}

inline float Animation::getStartTime() const
{
	return startTime;
}

inline float Animation::getEndTime() const
{
	return endTime;
}

inline std::size_t Animation::getChannelCount() const
{
	return channels.size();
}

inline const AnimationChannel* Animation::getChannel(std::size_t index) const
{
	return channels[index];
}

inline AnimationChannel* Animation::getChannel(std::size_t index)
{
	return channels[index];
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_ANIMATION_HPP
