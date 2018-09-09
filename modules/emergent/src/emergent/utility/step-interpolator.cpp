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

#include <emergent/utility/step-interpolator.hpp>
#include <emergent/utility/tween.hpp>

namespace Emergent
{

void StepInterpolator::update()
{
	for (TweenBase* variable: variables)
	{
		variable->update();
	}
}

void StepInterpolator::interpolate(float t)
{
	for (TweenBase* variable: variables)
	{
		variable->interpolate(t);
	}
}

void StepInterpolator::addVariable(TweenBase* variable)
{
	variables.push_back(variable);
}

void StepInterpolator::removeVariable(TweenBase* variable)
{
	variables.remove(variable);
}

void StepInterpolator::removeVariables()
{
	variables.clear();
}

} // namespace Emergent

