/*
 * Copyright (C) 2011-2014  Christopher J. Howard
 *
 * This file is part of Open Graphics Framework (OGF).
 *
 * OGF is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OGF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OGF.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <emergent/graphics/animation.hpp>
#include <emergent/graphics/animation-channel.hpp>

namespace Emergent
{

Animation::Animation():
	startTime(0.0f),
	endTime(0.0f)
{}

Animation::~Animation()
{
	for (auto channel: channels)
	{
		delete channel;
	}
}

AnimationChannel* Animation::createChannel(std::size_t channelID)
{
	AnimationChannel* channel = new AnimationChannel(channelID);
	channels.push_back(channel);
	
	return channel;
}

void Animation::setName(const std::string& name)
{
	this->name = name;
}

void Animation::setTimeFrame(float start, float end)
{
	startTime = start;
	endTime = end;
}

} // namespace Emergent
