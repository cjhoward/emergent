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

#ifndef EMERGENT_INPUT_CONTROL_HPP
#define EMERGENT_INPUT_CONTROL_HPP

#include <emergent/input/observers.hpp>
#include <functional>
#include <list>
#include <tuple>
#include <utility>

namespace Emergent
{

enum class MouseWheelAxis;
enum class Scancode;
class InputEvent;
class Keyboard;
class Mouse;
class Gamepad;

/**
 * A control can be bound to multiple types of input events.
 *
 * @ingroup input
 */
class Control:
	public KeyObserver,
	public MouseButtonObserver,
	public MouseWheelObserver,
	public GamepadButtonObserver,
	public GamepadAxisObserver
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

	/// Returns true if the control is not bound to any input events.
	bool isUnbound() const;
	
	/**
	 * Binds the control to keyboard key.
	 *
	 * @param keyboard Pointer to a keyboard.
	 * @param scancode Scancode of the key to which the control will be bound.
	 */
	void bindKey(Keyboard* keyboard, Scancode scancode);

	/**
	 * Binds the control to a mouse button.
	 *
	 * @param mouse Pointer to a mouse.
	 * @param button Index of the mouse button to which the control will be bound.
	 */
	void bindMouseButton(Mouse* mouse, int button);

	/**
	 * Binds the control to a mouse wheel axis.
	 *
	 * @param mouse Pointer to a mouse.
	 * @param axis Mouse wheel axis to which the control will be bound.
	 */
	void bindMouseWheelAxis(Mouse* mouse, MouseWheelAxis axis);

	/**
	 * Binds the control to a gamepad button.
	 *
	 * @param gamepad Pointer to a gamepad.
	 * @param button Index of the gamepad button to which the control will be bound.
	 */
	void bindGamepadButton(Gamepad* gamepad, int button);

	/**
	 * Binds the control to a gamepad axis.
	 *
	 * @param gamepad Pointer to a gamepad.
	 * @param axis Index of the gamepad axis to which the control will be bound.
	 * @param negative Indicates whether the axis is negative or positive.
	 */
	void bindGamepadAxis(Gamepad* gamepad, int axis, bool negative);

	/**
	 * Binds the control to an input event.
	 *
	 * @param event Input event to which the control will be bound.
	 */
	void bind(const InputEvent& event);
	
	/**
	 * Unbinds the control from all input events.
	 */
	void unbind();
	
	/// @copydoc KeyObserver::keyPressed()
	virtual void keyPressed(Scancode scancode);

	/// @copydoc KeyObserver::keyReleased()
	virtual void keyReleased(Scancode scancode);

	/// @copdoc MouseButtonObserver::mouseButtonPressed()
	virtual void mouseButtonPressed(int button, int x, int y);

	/// @copdoc MouseButtonObserver::mouseButtonReleased()
	virtual void mouseButtonReleased(int button, int x, int y);

	/// @copydoc MouseWheelObserver::mouseWheelScrolled()
	virtual void mouseWheelScrolled(int x, int y);

	/// @copydoc GamepadButtonObserver::gamepadButtonPressed()
	virtual void gamepadButtonPressed(int button);

	/// @copydoc GamepadButtonObserver::gamepadButtonReleased()
	virtual void gamepadButtonReleased(int button);

	/// @copydoc GamepadAxisObserver::gamepadAxisMoved()
	virtual void gamepadAxisMoved(int axis, bool negative, float value);
	
	/// Returns a list of bound keys.
	const std::list<std::pair<Keyboard*, Scancode>>* getBoundKeys() const;

	/// Returns a list of bound mouse buttons.
	const std::list<std::pair<Mouse*, int>>* getBoundMouseButtons() const;

	/// Returns a list of bound mouse wheel axes.
	const std::list<std::pair<Mouse*, MouseWheelAxis>>* getBoundMouseWheelAxes() const;

	/// Returns a list of bound gamepad buttons.
	const std::list<std::pair<Gamepad*, int>>* getBoundGamepadButtons() const;

	/// Returns a list of bound gamepad axes.
	const std::list<std::tuple<Gamepad*, int, bool>>* getBoundGamepadAxes() const;
	
private:
	float deadzone;
	float currentValue;
	float previousValue;
	
	std::list<std::pair<Keyboard*, Scancode>> boundKeys;
	std::list<std::pair<Mouse*, int>> boundMouseButtons;
	std::list<std::pair<Mouse*, MouseWheelAxis>> boundMouseWheelAxes;
	std::list<std::pair<Gamepad*, int>> boundGamepadButtons;
	std::list<std::tuple<Gamepad*, int, bool>> boundGamepadAxes;
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

