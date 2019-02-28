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

#include <emergent/utility/device-manager.hpp>
#include <emergent/input/gamepad.hpp>
#include <algorithm>

namespace Emergent
{

DeviceManager::DeviceManager(OSInterface* osInterface):
	osInterface(osInterface)
{}

DeviceManager::~DeviceManager()
{}

void DeviceManager::registerDisplay(Display* display)
{
	displays.push_back(display);
}

void DeviceManager::registerKeyboard(Keyboard* keyboard)
{
	keyboards.push_back(keyboard);
}

void DeviceManager::registerMouse(Mouse* mouse)
{
	mice.push_back(mouse);
}

void DeviceManager::registerGamepad(Gamepad* gamepad)
{
	gamepads.push_back(gamepad);
}

void DeviceManager::unregisterDisplay(Display* display)
{
	displays.remove(display);
}

void DeviceManager::unregisterKeyboard(Keyboard* keyboard)
{
	keyboards.remove(keyboard);
}

void DeviceManager::unregisterMouse(Mouse* mouse)
{
	mice.remove(mouse);
}

void DeviceManager::unregisterGamepad(Gamepad* gamepad)
{
	gamepads.remove(gamepad);
}

bool DeviceManager::isRegistered(const Display* display) const
{
	auto it = std::find(displays.begin(), displays.end(), display);
	if (it == displays.end())
	{
		return false;
	}

	return true;
}

bool DeviceManager::isRegistered(const Keyboard* keyboard) const
{
	auto it = std::find(keyboards.begin(), keyboards.end(), keyboard);
	if (it == keyboards.end())
	{
		return false;
	}

	return true;
}

bool DeviceManager::isRegistered(const Mouse* mouse) const
{
	auto it = std::find(mice.begin(), mice.end(), mouse);
	if (it == mice.end())
	{
		return false;
	}

	return true;
}

bool DeviceManager::isRegistered(const Gamepad* gamepad) const
{
	auto it = std::find(gamepads.begin(), gamepads.end(), gamepad);
	if (it == gamepads.end())
	{
		return false;
	}

	return true;
}

const Gamepad* DeviceManager::getGamepad(const std::string& name) const
{
	for (auto gamepad: gamepads)
	{
		if (gamepad->getName() == name)
			return gamepad;
	}
	
	return nullptr;
}

Gamepad* DeviceManager::getGamepad(const std::string& name)
{
	for (auto gamepad: gamepads)
	{
		if (gamepad->getName() == name)
			return gamepad;
	}
	
	return nullptr;
}

} // namespace Emergent

