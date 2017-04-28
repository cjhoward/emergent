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
	for (auto keyFrame: keyFrames)
	{
		delete keyFrame;
	}
}

KeyFrame* AnimationChannel::createKeyFrame(const Transform& transform)
{
	KeyFrame* keyFrame = new KeyFrame(transform);
	keyFrames.push_back(keyFrame);
	
	return keyFrame;
}

} // namespace Emergent
