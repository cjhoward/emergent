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

#include <emergent/input/input-manager.hpp>
#include <emergent/input/gamepad.hpp>

namespace Emergent
{

InputManager::InputManager():
	closed(false)
{}

InputManager::~InputManager()
{}

void InputManager::registerKeyboard(Keyboard* keyboard)
{
	keyboards.push_back(keyboard);
}

void InputManager::registerMouse(Mouse* mouse)
{
	mice.push_back(mouse);
}

void InputManager::registerGamepad(Gamepad* gamepad)
{
	gamepads.push_back(gamepad);
}

void InputManager::unregisterKeyboard(Keyboard* keyboard)
{
	keyboards.remove(keyboard);
}

void InputManager::unregisterMouse(Mouse* mouse)
{
	mice.remove(mouse);
}

void InputManager::unregisterGamepad(Gamepad* gamepad)
{
	gamepads.remove(gamepad);
}

bool InputManager::isRegistered(const Keyboard* keyboard) const
{
	for (auto it = keyboards.begin(); it != keyboards.end(); ++it)
	{
		if (*it == keyboard)
			return true;
	}
	
	return false;
}

bool InputManager::isRegistered(const Mouse* mouse) const
{
	for (auto it = mice.begin(); it != mice.end(); ++it)
	{
		if (*it == mouse)
			return true;
	}
	
	return false;
}

bool InputManager::isRegistered(const Gamepad* gamepad) const
{
	for (auto it = gamepads.begin(); it != gamepads.end(); ++it)
	{
		if (*it == gamepad)
			return true;
	}
	
	return false;
}

const Gamepad* InputManager::getGamepad(const std::string& name) const
{
	for (auto gamepad: gamepads)
	{
		if (gamepad->getName() == name)
			return gamepad;
	}
	
	return nullptr;
}

Gamepad* InputManager::getGamepad(const std::string& name)
{
	for (auto gamepad: gamepads)
	{
		if (gamepad->getName() == name)
			return gamepad;
	}
	
	return nullptr;
}

} // namespace Emergent

