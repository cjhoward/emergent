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

#include <emergent/animation/animator.hpp>
#include <emergent/animation/animation.hpp>

namespace Emergent
{

void Animator::animate(float dt)
{
	// Process queued animations
	for (AnimationBase* animation: queuedAnimations)
	{
		animations.push_back(animation);
	}
	queuedAnimations.clear();

	// Process dequeued animations
	for (AnimationBase* animation: dequeuedAnimations)
	{
		animations.remove(animation);
	}
	dequeuedAnimations.clear();

	// Animate playing animationss
	for (AnimationBase* animation: animations)
	{
		if (animation->isPlaying())
		{
			animation->animate(dt);
		}
	}
}

void Animator::addAnimation(AnimationBase* animation)
{
	queuedAnimations.push_back(animation);
}

void Animator::removeAnimation(AnimationBase* animation)
{
	queuedAnimations.remove(animation);
	dequeuedAnimations.push_back(animation);
}

void Animator::removeAnimations()
{
	queuedAnimations.clear();
	dequeuedAnimations.clear();
	animations.clear();
}

} // namespace Emergent

