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
#include <emergent/utility/os-interface.hpp>
#include <emergent/utility/device-manager.hpp>
#include <emergent/utility/event-dispatcher.hpp>

namespace Emergent
{

Mouse::Mouse(DeviceManager* DeviceManager, const std::string& name):
	InputDevice(DeviceManager, name)
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

	getDeviceManager()->getOSInterface()->getEventDispatcher()->queue(event);
}

void Mouse::release(int button, int x, int y)
{
	MouseButtonReleasedEvent event;
	event.mouse = this;
	event.button = button;
	event.x = x;
	event.y = y;

	getDeviceManager()->getOSInterface()->getEventDispatcher()->queue(event);
}

void Mouse::move(int x, int y)
{
	MouseMovedEvent event;
	event.mouse = this;
	event.x = x;
	event.y = y;

	getDeviceManager()->getOSInterface()->getEventDispatcher()->queue(event);
}

void Mouse::scroll(int x, int y)
{
	MouseWheelScrolledEvent event;
	event.mouse = this;
	event.x = x;
	event.y = y;

	getDeviceManager()->getOSInterface()->getEventDispatcher()->queue(event);
}

void Mouse::warp(Window* window, int x, int y)
{
	getDeviceManager()->getOSInterface()->warpMousePosition(window, x, y);
}

void Mouse::setRelativeMode(bool enabled)
{
	getDeviceManager()->getOSInterface()->setRelativeMouseMode(this, enabled);
}

void Mouse::setVisible(bool visible)
{
	getDeviceManager()->getOSInterface()->setMouseVisible(this, visible);
}

} // namespace Emergent

