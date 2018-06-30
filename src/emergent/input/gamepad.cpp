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
#include <emergent/input/input-event.hpp>
#include <emergent/input/input-manager.hpp>
#include <emergent/utility/event-dispatcher.hpp>

namespace Emergent
{

Gamepad::Gamepad(InputManager* inputManager, const std::string& name):
	InputDevice(inputManager, name)
{}

Gamepad::~Gamepad()
{}

void Gamepad::press(int button)
{
	GamepadButtonPressedEvent event;
	event.gamepad = this;
	event.button = button;

	getInputManager()->getEventDispatcher()->queue(event);
}

void Gamepad::release(int button)
{
	GamepadButtonReleasedEvent event;
	event.gamepad = this;
	event.button = button;

	getInputManager()->getEventDispatcher()->queue(event);
}

void Gamepad::move(int axis, bool negative, float value)
{
	GamepadAxisMovedEvent event;
	event.gamepad = this;
	event.axis = axis;
	event.negative = negative;
	event.value = value;

	getInputManager()->getEventDispatcher()->queue(event);
}

} // namespace Emergent

