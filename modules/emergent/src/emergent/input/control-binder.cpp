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

#include <emergent/input/control-binder.hpp>
#include <emergent/input/control.hpp>
#include <emergent/input/mouse.hpp>

namespace Emergent
{

ControlBinder::ControlBinder():
	control(nullptr)
{}

ControlBinder::~ControlBinder()
{}

void ControlBinder::bind(Control* control)
{
	this->control = control;
}

void ControlBinder::handleEvent(const KeyPressedEvent& event)
{
	if (control != nullptr)
	{
		control->bindKey(event.keyboard, event.scancode);
		control = nullptr;
	}
}

void ControlBinder::handleEvent(const MouseButtonPressedEvent& event)
{
	if (control != nullptr)
	{
		control->bindMouseButton(event.mouse, event.button);
		control = nullptr;
	}
}

void ControlBinder::handleEvent(const MouseWheelScrolledEvent& event)
{
	if (control != nullptr)
	{
		MouseWheelAxis axis;
		if (event.x > 0)
			axis = MouseWheelAxis::POSITIVE_X;
		else if (event.x < 0)
			axis = MouseWheelAxis::NEGATIVE_X;
		else if (event.y > 0)
			axis = MouseWheelAxis::POSITIVE_Y;
		else if (event.y < 0)
			axis = MouseWheelAxis::NEGATIVE_Y;
		else
			return;

		control->bindMouseWheelAxis(event.mouse, axis);
		control = nullptr;
	}
}

void ControlBinder::handleEvent(const GamepadButtonPressedEvent& event)
{
	if (control != nullptr)
	{
		control->bindGamepadButton(event.gamepad, event.button);
		control = nullptr;
	}
}

void ControlBinder::handleEvent(const GamepadAxisMovedEvent& event)
{
	if (control != nullptr)
	{
		control->bindGamepadAxis(event.gamepad, event.axis, event.negative);
		control = nullptr;
	}
}

} // namespace Emergent

