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

#ifndef EMERGENT_UTILITY_STATE_INTERPOLATOR_HPP
#define EMERGENT_UTILITY_STATE_INTERPOLATOR_HPP

#include <list>

namespace Emergent
{

class TweenBase;

/**
 * Interpolates variables between two states.
 *
 * @ingroup utility
 */
class StateInterpolator
{
public:
	/**
	 * For each variable, sets state0 equal to state1. This should be called at the beginning of each logical step.
	 */
	void update();

	/**
	 * Calculates the substate of each variable by interpolating between state0 and state1. This should be called before rendering.
	 *
	 * @param t Interpolation ratio
	 */
	void interpolate(float t);

	/**
	 * Adds a variable to the interpolator.
	 *
	 * @param variable Variable to add.
	 */
	void addVariable(TweenBase* variable);

	/**
	 * Removes a variable from the interpolator.
	 *
	 * @param variable Variable to remove.
	 */
	void removeVariable(TweenBase* variable);

	/**
	 * Removes all variables from the interpolator.
	 */
	void removeVariables();

private:
	std::list<TweenBase*> variables;
};

} // namespace Emergent

#endif // EMERGENT_UTILITY_STATE_INTERPOLATOR_HPP

