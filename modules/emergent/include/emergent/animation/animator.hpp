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

#ifndef EMERGENT_ANIMATION_ANIMATOR_HPP
#define EMERGENT_ANIMATION_ANIMATOR_HPP

#include <list>

namespace Emergent
{

class AnimationBase;

/**
 * Animates a list of animations.
 *
 * @ingroup animation
 */
class Animator
{
public:
	/**
	 * Animates all playing animations.
	 *
	 * @param dt Delta-time, in seconds.
	 */
	void animate(float dt);

	/**
	 * Adds an animation to the animator.
	 *
	 * @param animation Animation to add.
	 */
	void addAnimation(AnimationBase* animation);

	/**
	 * Removes an animation from the animator.
	 *
	 * @param animation Animation to remove.
	 */
	void removeAnimation(AnimationBase* animation);

	/**
	 * Removes all animations from the animator.
	 */
	void removeAnimations();

private:
	std::list<AnimationBase*> animations;
	std::list<AnimationBase*> queuedAnimations;
	std::list<AnimationBase*> dequeuedAnimations;
};

} // namespace Emergent

#endif // EMERGENT_ANIMATION_ANIMATOR_HPP

