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

#ifndef EMERGENT_INPUT_GAMEPAD_HPP
#define EMERGENT_INPUT_GAMEPAD_HPP

#include <emergent/input/input-device.hpp>
#include <list>

namespace Emergent
{

class GamepadButtonObserver;
class GamepadAxisObserver;

/**
 * Gamepad input device.
 *
 * @ingroup input
 */
class Gamepad: public InputDevice
{
public:
	/**
	 * Creates a gamepad input device.
	 *
	 * @param name Name of the gamepad.
	 */
	Gamepad(const std::string& name);

	/// Destroys a gamepad input device.
	virtual ~Gamepad();
	
	/// Returns InputDevice::Type::GAMEPAD.
	InputDevice::Type getType() const;
	
	/// Adds a gamepad button observer to this gamepad.
	void addGamepadButtonObserver(GamepadButtonObserver* observer);

	/// Removes a gamepad button observer from this gamepad.
	void removeGamepadButtonObserver(GamepadButtonObserver* observer);

	/// Removes all gamepad button observers from this gamepad.
	void removeGamepadButtonObservers();
	
	/// Adds a gamepad axis observer to this gamepad.
	void addGamepadAxisObserver(GamepadAxisObserver* observer);

	/// Removes a gamepad axis observer from this gamepad.
	void removeGamepadAxisObserver(GamepadAxisObserver* observer);

	/// Removes all gamepad axis observers from this gamepad.
	void removeGamepadAxisObservers();
	
	/**
	 * Simulates a gamepad button press. Notifies all gamepad button observers via GamepadButtonObserver::gamepadButtonPressed().
	 *
	 * @param button Index of the pressed button.
	 */
	void press(int button);

	/**
	 * Simulates a gamepad button release. Notifies all gamepad button observers via GamepadButtonObserver::gamepadButtonReleased().
	 *
	 * @param button Index of the released button.
	 */
	void release(int button);

	/**
	 * Simulates a gamepad axis movement. Notifies all gamepad axis observers via GamepadAxisObserver::gamepadAxisMoved().
	 *
	 * @param axis Index of the moved axis.
	 * @param negative Whether the movement was negative or positive.
	 * @param value Normalized degree of movement.
	 */
	void move(int axis, bool negative, float value);
	
private:
	std::list<GamepadButtonObserver*> buttonObservers;
	std::list<GamepadAxisObserver*> axisObservers;
};

inline InputDevice::Type Gamepad::getType() const
{
	return InputDevice::Type::GAMEPAD;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_GAMEPAD_HPP

