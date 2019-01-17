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

#include <emergent/animation/step-interpolator.hpp>
#include <emergent/animation/tween.hpp>

namespace Emergent
{

void StepInterpolator::reset()
{
	for (TweenBase* tween: tweens)
	{
		tween->reset();
	}
}

void StepInterpolator::interpolate(float a)
{
	for (TweenBase* tween: tweens)
	{
		tween->interpolate(a);
	}
}

void StepInterpolator::addTween(TweenBase* tween)
{
	tweens.push_back(tween);
}

void StepInterpolator::removeTween(TweenBase* tween)
{
	tweens.remove(tween);
}

void StepInterpolator::removeTweens()
{
	tweens.clear();
}

} // namespace Emergent

