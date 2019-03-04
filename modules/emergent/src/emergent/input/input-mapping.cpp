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

#include <emergent/input/input-mapping.hpp>

namespace Emergent
{

InputMapping::InputMapping(Control* control):
	control(control)
{}

KeyMapping::KeyMapping(const KeyMapping& mapping)
{
	*this = mapping;
}

KeyMapping::KeyMapping(Control* control, Keyboard* keyboard, Scancode scancode):
	InputMapping(control),
	keyboard(keyboard),
	scancode(scancode)
{}

KeyMapping& KeyMapping::operator=(const KeyMapping& mapping)
{
	control = mapping.control;
	keyboard = mapping.keyboard;
	scancode = mapping.scancode;
	return *this;
}

MouseMotionMapping::MouseMotionMapping(const MouseMotionMapping& mapping)
{
	*this = mapping;
}

MouseMotionMapping::MouseMotionMapping(Control* control, Mouse* mouse, MouseMotionAxis axis):
	InputMapping(control),
	mouse(mouse),
	axis(axis)
{}

MouseMotionMapping& MouseMotionMapping::operator=(const MouseMotionMapping& mapping)
{
	control = mapping.control;
	mouse = mapping.mouse;
	axis = mapping.axis;
	return *this;
}

MouseWheelMapping::MouseWheelMapping(const MouseWheelMapping& mapping)
{
	*this = mapping;
}

MouseWheelMapping::MouseWheelMapping(Control* control, Mouse* mouse, MouseWheelAxis axis):
	InputMapping(control),
	mouse(mouse),
	axis(axis)
{}

MouseWheelMapping& MouseWheelMapping::operator=(const MouseWheelMapping& mapping)
{
	control = mapping.control;
	mouse = mapping.mouse;
	axis = mapping.axis;
	return *this;
}

MouseButtonMapping::MouseButtonMapping(const MouseButtonMapping& mapping)
{
	*this = mapping;
}

MouseButtonMapping::MouseButtonMapping(Control* control, Mouse* mouse, int button):
	InputMapping(control),
	mouse(mouse),
	button(button)
{}

MouseButtonMapping& MouseButtonMapping::operator=(const MouseButtonMapping& mapping)
{
	control = mapping.control;
	mouse = mapping.mouse;
	button = mapping.button;
	return *this;
}

GamepadAxisMapping::GamepadAxisMapping(const GamepadAxisMapping& mapping)
{
	*this = mapping;
}

GamepadAxisMapping::GamepadAxisMapping(Control* control, Gamepad* gamepad, int axis, bool negative):
	InputMapping(control),
	gamepad(gamepad),
	axis(axis),
	negative(negative)
{}

GamepadAxisMapping& GamepadAxisMapping::operator=(const GamepadAxisMapping& mapping)
{
	control = mapping.control;
	gamepad = mapping.gamepad;
	axis = mapping.axis;
	negative = mapping.negative;
	return *this;
}

GamepadButtonMapping::GamepadButtonMapping(const GamepadButtonMapping& mapping)
{
	*this = mapping;
}

GamepadButtonMapping::GamepadButtonMapping(Control* control, Gamepad* gamepad, int button):
	InputMapping(control),
	gamepad(gamepad),
	button(button)
{}

GamepadButtonMapping& GamepadButtonMapping::operator=(const GamepadButtonMapping& mapping)
{
	control = mapping.control;
	gamepad = mapping.gamepad;
	button = mapping.button;
	return *this;
}

} // namespace Emergent

