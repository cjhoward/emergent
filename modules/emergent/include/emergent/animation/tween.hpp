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

#ifndef EMERGENT_ANIMATION_TWEEN_HPP
#define EMERGENT_ANIMATION_TWEEN_HPP

#include <functional>

namespace Emergent
{

/**
 * Abstract base class for tweens.
 *
 * @ingroup animation
 */
class TweenBase
{
public:
	/**
	 * Clears interpolation by setting state0 and substate equal to state1.
	 */
	virtual void reset() = 0;

	/**
	 * Calculates the substate by interpolating between state0 and state1 via the specified interpolator function.
	 *
	 * @param a Interpolation ratio
	 */
	virtual void interpolate(float a) = 0;
};

/**
 * Keeps track of a variable's current and previous states in order to interpolate between the them.
 *
 * @ingroup animation
 */
template <typename T>
class Tween: public TweenBase
{
public:
	typedef std::function<T(const T&, const T&, float)> InterpolatorType;

	/**
	 * Creates a tween.
	 *
	 * @param variable Pointer to the variable to be tweened.
	 * @param interpolator Interpolation function.
	 */
	Tween(const T* variable, InterpolatorType interpolator);

	/// Destroys a tween.
	virtual ~Tween() = default;

	/// @copydoc TweenBase::reset
	virtual void reset();

	/// @copydoc TweenBase::interpolate
	virtual void interpolate(float t);

	/**
	 * Sets the function used to interpolate between state0 and state1.
	 *
	 * @param interpolator Interpolation function.
	 */
	void setInterpolator(InterpolatorType interpolator);

	/// Returns the value of the tweened variable since the last time Tween::reset() was called.
	const T& getState0() const;

	/// Reurns the current value of the tweened variable.
	const T& getState1() const;

	/// Returns the value between state0 and state1 that was calculated by the interpolation function when Tween::interpolate() was called.
	const T& getSubstate() const;

	/// Returns the function used to interpolate between state0 and state1.
	InterpolatorType getInterpolator() const;

private:
	T state0;
	const T* state1;
	T substate;
	InterpolatorType interpolator;
};

template <typename T>
Tween<T>::Tween(const T* variable, InterpolatorType interpolator):
	state0(*variable),
	state1(variable),
	substate(*variable),
	interpolator(interpolator)
{}

template <typename T>
inline void Tween<T>::reset()
{
	state0 = *state1;
	substate = state0;
}

template <typename T>
inline void Tween<T>::interpolate(float a)
{
	if (state0 == *state1)
	{
		return;
	}

	substate = interpolator(state0, *state1, a);
}

template <typename T>
inline void Tween<T>::setInterpolator(InterpolatorType interpolator)
{
	this->interpolator = interpolator;
}

template <typename T>
inline const T& Tween<T>::getState0() const
{
	return state0;
}

template <typename T>
inline const T& Tween<T>::getState1() const
{
	return *state1;
}

template <typename T>
inline const T& Tween<T>::getSubstate() const
{
	return substate;
}

template <typename T>
inline typename Tween<T>::InterpolatorType Tween<T>::getInterpolator() const
{
	return interpolator;
}

} // namespace Emergent

#endif // EMERGENT_ANIMATION_TWEEN_HPP

