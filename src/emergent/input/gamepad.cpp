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

#include <emergent/input/gamepad.hpp>
#include <emergent/input/observers.hpp>

namespace Emergent
{

Gamepad::Gamepad(const std::string& name):
	InputDevice(name)
{}

Gamepad::~Gamepad()
{}

void Gamepad::addGamepadButtonObserver(GamepadButtonObserver* observer)
{
	buttonObservers.push_back(observer);
}

void Gamepad::removeGamepadButtonObserver(GamepadButtonObserver* observer)
{
	buttonObservers.remove(observer);
}

void Gamepad::removeGamepadButtonObservers()
{
	buttonObservers.clear();
}

void Gamepad::addGamepadAxisObserver(GamepadAxisObserver* observer)
{
	axisObservers.push_back(observer);
}

void Gamepad::removeGamepadAxisObserver(GamepadAxisObserver* observer)
{
	axisObservers.remove(observer);
}

void Gamepad::removeGamepadAxisObservers()
{
	axisObservers.clear();
}

void Gamepad::press(int button)
{
	for (auto observer: buttonObservers)
	{
		observer->gamepadButtonPressed(button);
	}
}

void Gamepad::release(int button)
{
	for (auto observer: buttonObservers)
	{
		observer->gamepadButtonReleased(button);
	}
}

void Gamepad::move(int axis, bool negative, float value)
{
	for (auto observer: axisObservers)
	{
		observer->gamepadAxisMoved(axis, negative, value);
	}
}

} // namespace Emergent

