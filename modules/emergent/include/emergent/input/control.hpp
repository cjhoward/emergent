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

#ifndef EMERGENT_INPUT_CONTROL_HPP
#define EMERGENT_INPUT_CONTROL_HPP

#include <functional>

namespace Emergent
{

/**
 * A control can be bound to multiple types of input events.
 *
 * @ingroup input
 */
class Control
{
public:
	/// Creates a control.
	Control();

	/// Destroys a control.
	virtual ~Control();

	/**
	 * Performs callbacks then sets the previous value equal to the current value.
	 */
	void update();

	/**
	 * Sets the current value of the control.
	 *
	 * @param value Control value.
	 */
	void setCurrentValue(float value);

	/**
	 * This works the same as setting the current value, but causes the value to be reset on the next call to update.
	 */
	void setTemporaryValue(float value);

	/**
	 * Sets the deadzone value. If the current value of the control is not greater than the deadzone value, the control will not be considered active.
	 *
	 * @param value Deadzone value.
	 */
	void setDeadzone(float value);


	/// Sets the callback for when the control is activated.
	void setActivatedCallback(std::function<void()> callback);

	/// Sets the callback for when the control is deactivated.
	void setDeactivatedCallback(std::function<void()> callback);

	/// Sets the callback for when the control value is changed.
	void setValueChangedCallback(std::function<void(float)> callback);

	/**
	 * Enables or disables callbacks.
	 *
	 * @param enabled Whether to enable or disable callbacks.
	 */
	void setCallbacksEnabled(bool enabled);

	/// Returns the deadzone value. The default value is 0.0.
	float getDeadzone() const;

	/// Returns the current value of the control.
	float getCurrentValue() const;

	/// Returns the previous value of the control.
	float getPreviousValue() const;

	/// Returns true if the control is currently active.
	bool isActive() const;

	/// Returns true if the control was previously active when update() was last called.
	bool wasActive() const;

private:
	float deadzone;
	float currentValue;
	float previousValue;
	bool reset;
	std::function<void()> activatedCallback;
	std::function<void()> deactivatedCallback;
	std::function<void(float)> valueChangedCallback;
	bool callbacksEnabled;
};

inline void Control::setCallbacksEnabled(bool enabled)
{
	this->callbacksEnabled = enabled;
}

inline float Control::getDeadzone() const
{
	return deadzone;
}

inline float Control::getCurrentValue() const
{
	return currentValue;
}

inline float Control::getPreviousValue() const
{
	return previousValue;
}

inline bool Control::isActive() const
{
	return currentValue > deadzone;
}

inline bool Control::wasActive() const
{
	return previousValue > deadzone;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_CONTROL_HPP

