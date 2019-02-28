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

#include <emergent/input/input-event.hpp>

namespace Emergent
{

EventBase* ApplicationClosedEvent::clone() const
{
	ApplicationClosedEvent* event = new ApplicationClosedEvent();
	return event;
}

EventBase* WindowClosedEvent::clone() const
{
	WindowClosedEvent* event = new WindowClosedEvent();
	event->window = window;
	return event;
}

EventBase* WindowResizedEvent::clone() const
{
	WindowResizedEvent* event = new WindowResizedEvent();
	event->window = window;
	event->width = width;
	event->height = height;
	return event;
}

EventBase* KeyPressedEvent::clone() const
{
	KeyPressedEvent* event = new KeyPressedEvent();
	event->keyboard = keyboard;
	event->scancode = scancode;
	return event;
}

EventBase* KeyReleasedEvent::clone() const
{
	KeyReleasedEvent* event = new KeyReleasedEvent();
	event->keyboard = keyboard;
	event->scancode = scancode;
	return event;
}

EventBase* MouseMovedEvent::clone() const
{
	MouseMovedEvent* event = new MouseMovedEvent();
	event->mouse = mouse;
	event->x = x;
	event->y = y;
	event->dx = dx;
	event->dy = dy;
	return event;
}

EventBase* MouseButtonPressedEvent::clone() const
{
	MouseButtonPressedEvent* event = new MouseButtonPressedEvent();
	event->mouse = mouse;
	event->button = button;
	event->x = x;
	event->y = y;
	return event;
}

EventBase* MouseButtonReleasedEvent::clone() const
{
	MouseButtonReleasedEvent* event = new MouseButtonReleasedEvent();
	event->mouse = mouse;
	event->button = button;
	event->x = x;
	event->y = y;
	return event;
}

EventBase* MouseWheelScrolledEvent::clone() const
{
	MouseWheelScrolledEvent* event = new MouseWheelScrolledEvent();
	event->mouse = mouse;
	event->x = x;
	event->y = y;
	return event;
}

EventBase* GamepadButtonPressedEvent::clone() const
{
	GamepadButtonPressedEvent* event = new GamepadButtonPressedEvent();
	event->gamepad = gamepad;
	event->button = button;
	return event;
}

EventBase* GamepadButtonReleasedEvent::clone() const
{
	GamepadButtonReleasedEvent* event = new GamepadButtonReleasedEvent();
	event->gamepad = gamepad;
	event->button = button;
	return event;
}

EventBase* GamepadAxisMovedEvent::clone() const
{
	GamepadAxisMovedEvent* event = new GamepadAxisMovedEvent();
	event->gamepad = gamepad;
	event->axis = axis;
	event->negative = negative;
	event->value = value;
	return event;
}

} // namespace Emergent

