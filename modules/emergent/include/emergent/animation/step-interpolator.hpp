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

#ifndef EMERGENT_ANIMATION_STEP_INTERPOLATOR_HPP
#define EMERGENT_ANIMATION_STEP_INTERPOLATOR_HPP

#include <list>

namespace Emergent
{

class TweenBase;

/**
 * Interpolates tweens between logical steps.
 *
 * @ingroup animation
 */
class StepInterpolator
{
public:
	/**
	 * Resets the step interpolation for each tween. This should be called at the beginning of each logical step.
	 */
	void reset();

	/**
	 * Calculates the substate of each tween by interpolating between state0 and state1. This should be called right before rendering.
	 *
	 * @param a Interpolation ratio.
	 */
	void interpolate(float a);

	/**
	 * Adds a tween to the step interpolator.
	 *
	 * @param tween Tween to add.
	 */
	void addTween(TweenBase* tween);

	/**
	 * Removes a tween from the step interpolator.
	 *
	 * @param tween Tween to remove.
	 */
	void removeTween(TweenBase* tween);

	/**
	 * Removes all tweens from the interpolator.
	 */
	void removeTweens();

private:
	std::list<TweenBase*> tweens;
};

} // namespace Emergent

#endif // EMERGENT_ANIMATION_STEP_INTERPOLATOR_HPP

