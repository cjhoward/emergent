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

#include <emergent/animation/animation.hpp>

namespace Emergent
{

AnimationBase::AnimationBase():
	startTime(0.0f),
	endTime(0.0f),
	speed(1.0f),
	loop(false),
	playing(false),
	position(0.0f),
	startCallback(nullptr),
	endCallback(nullptr),
	loopCallback(nullptr)
{}

void AnimationBase::play()
{
	if (!playing)
	{
		playing = true;

		// Execute start callback
		if (startCallback)
		{
			startCallback();
		}
	}
}

void AnimationBase::pause()
{
	playing = false;
}

void AnimationBase::stop()
{
	playing = false;
	rewind();
}

void AnimationBase::seek(float position)
{
	this->position = position;
}

void AnimationBase::rewind()
{
	if (speed < 0.0f)
	{
		position = endTime;
	}
	else
	{
		position = startTime;
	}
}

void AnimationBase::setTimeFrame(float start, float end)
{
	startTime = start;
	endTime = end;
}

void AnimationBase::setTimeFrame(const std::tuple<float, float>& timeFrame)
{
	startTime = std::get<0>(timeFrame);
	endTime = std::get<1>(timeFrame);
}

void AnimationBase::setSpeed(float speed)
{
	this->speed = speed;
}

void AnimationBase::setLoop(bool loop)
{
	this->loop = loop;
}

void AnimationBase::setStartCallback(const std::function<void()> callback)
{
	startCallback = callback;
}

void AnimationBase::setEndCallback(const std::function<void()> callback)
{
	endCallback = callback;
}

void AnimationBase::setLoopCallback(const std::function<void()> callback)
{
	loopCallback = callback;
}

void AnimationBase::animate(float dt)
{
	position += dt * speed;
	
	// If the animation is playing in reverse
	if (speed < 0.0f)
	{
		// If the animation has finished
		if (position <= startTime)
		{
			// If looping is enabled
			if (loop)
			{
				// Rewind to the end of the animation
				position += endTime - startTime;

				// Execute loop callback
				if (loopCallback)
				{
					loopCallback();
				}
			}
			else
			{
				// Stop the animation
				position = startTime;
				playing = false;
			}
		}
	}
	else
	{
		// If the animation has finished
		if (position >= endTime)
		{
			// If looping is enabled
			if (loop)
			{
				// Rewind to the beginning of the animation
				position -= endTime - startTime;

				// Execute loop callback
				if (loopCallback)
				{
					loopCallback();
				}
			}
			else
			{
				// Stop the animation
				position = endTime;
				playing = false;
			}
		}
	}

	// Interpolate animation channel keyframes
	interpolate(position);

	if (!playing)
	{
		// Execute end callback
		if (endCallback != nullptr)
		{
			endCallback();
		}
	}
}

} // namespace Emergent

