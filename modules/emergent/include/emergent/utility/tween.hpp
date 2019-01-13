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

#ifndef EMERGENT_UTILITY_TWEEN_HPP
#define EMERGENT_UTILITY_TWEEN_HPP

#include <emergent/math/interpolation.hpp>

namespace Emergent
{

/**
 * Abstract base class for tweens.
 *
 * @ingroup utility
 */
class TweenBase
{
public:
	/**
	 * Sets state0 equal to state1.
	 */
	virtual void update() = 0;

	/**
	 * Calculates the substate by interpolating between state0 and state1.
	 *
	 * @param t Interpolation ratio
	 */
	virtual void interpolate(float t) = 0;
};

/**
 * A variable which can be interpolated between two states.
 *
 * @tparam T Variable type
 * @tparam F Function used to interpolate between state0 and state1.
 *
 * @ingroup utility
 */
template <typename T, T (*F)(const T&, const T&, float) = lerp<T>>
class Tween: public TweenBase
{
public:
	/**
	 * Creates a tween.
	 *
	 * @param value Initial value of state0 and state1.
	 */
	explicit Tween(const T& value);

	/// Creates a tween.
	Tween();

	/// @copydoc TweenBase::update
	virtual void update();

	/// @copydoc TweenBase::interpolate
	virtual void interpolate(float t);

	/// Sets the value of state0
	void setState0(const T& value);

	/// Sets the value of state1
	void setState1(const T& value);

	/// Returns the value of state0
	const T& getState0() const;

	/// Returns the value of state1
	const T& getState1() const;

	/// Returns the value of the substate
	const T& getSubstate() const;

private:
	T state0;
	T state1;
	T substate;
};

template <typename T, T (*F)(const T&, const T&, float)>
Tween<T, F>::Tween(const T& value):
	state0(value),
	state1(value)
{}

template <typename T, T (*F)(const T&, const T&, float)>
Tween<T, F>::Tween()
{}

template <typename T, T (*F)(const T&, const T&, float)>
inline void Tween<T, F>::update()
{
	state0 = state1;
	substate = state1;
}

template <typename T, T (*F)(const T&, const T&, float)>
inline void Tween<T, F>::interpolate(float t)
{
	if (state0 != state1)
	{
		substate = F(state0, state1, t);
	}
}

template <typename T, T (*F)(const T&, const T&, float)>
inline void Tween<T, F>::setState0(const T& value)
{
	state0 = value;
}

template <typename T, T (*F)(const T&, const T&, float)>
inline void Tween<T, F>::setState1(const T& value)
{
	state1 = value;
}

template <typename T, T (*F)(const T&, const T&, float)>
inline const T& Tween<T, F>::getState0() const
{
	return state0;
}

template <typename T, T (*F)(const T&, const T&, float)>
inline const T& Tween<T, F>::getState1() const
{
	return state1;
}

template <typename T, T (*F)(const T&, const T&, float)>
inline const T& Tween<T, F>::getSubstate() const
{
	return substate;
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_TWEEN_HPP

