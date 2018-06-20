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

#include <emergent/input/mouse.hpp>
#include <emergent/input/input-event.hpp>
#include <emergent/input/input-manager.hpp>

namespace Emergent
{

Mouse::Mouse(InputManager* inputManager, const std::string& name):
	InputDevice(inputManager, name)
{}

Mouse::~Mouse()
{}

void Mouse::press(int button, int x, int y)
{
	MouseButtonPressedEvent event;
	event.mouse = this;
	event.button = button;
	event.x = x;
	event.y = y;

	getInputManager()->queue(event);
}

void Mouse::release(int button, int x, int y)
{
	MouseButtonReleasedEvent event;
	event.mouse = this;
	event.button = button;
	event.x = x;
	event.y = y;

	getInputManager()->queue(event);
}

void Mouse::move(int x, int y)
{
	MouseMovedEvent event;
	event.mouse = this;
	event.x = x;
	event.y = y;

	getInputManager()->queue(event);
}

void Mouse::scroll(int x, int y)
{
	MouseWheelScrolledEvent event;
	event.mouse = this;
	event.x = x;
	event.y = y;

	getInputManager()->queue(event);
}

} // namespace Emergent

