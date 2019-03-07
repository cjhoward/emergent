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

#include <emergent/input/input-mapper.hpp>
#include <emergent/utility/event-dispatcher.hpp>
#include <emergent/input/mouse.hpp>

namespace Emergent
{

InputMapper::InputMapper(EventDispatcher* eventDispatcher):
	eventDispatcher(eventDispatcher),
	control(nullptr),
	callback(nullptr),
	enabled(false)
{
	// Setup event handling
	eventDispatcher->subscribe<KeyPressedEvent>(this);
	eventDispatcher->subscribe<MouseMovedEvent>(this);
	eventDispatcher->subscribe<MouseButtonPressedEvent>(this);
	eventDispatcher->subscribe<MouseWheelScrolledEvent>(this);
	eventDispatcher->subscribe<GamepadButtonPressedEvent>(this);
	eventDispatcher->subscribe<GamepadAxisMovedEvent>(this);
}

InputMapper::~InputMapper()
{
	eventDispatcher->unsubscribe<KeyPressedEvent>(this);
	eventDispatcher->unsubscribe<MouseMovedEvent>(this);
	eventDispatcher->unsubscribe<MouseButtonPressedEvent>(this);
	eventDispatcher->unsubscribe<MouseWheelScrolledEvent>(this);
	eventDispatcher->unsubscribe<GamepadButtonPressedEvent>(this);
	eventDispatcher->unsubscribe<GamepadAxisMovedEvent>(this);
}

void InputMapper::setControl(Control* control)
{
	this->control = control;
}

void InputMapper::setCallback(std::function<void(const InputMapping&)> callback)
{
	this->callback = callback;
}

void InputMapper::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

void InputMapper::handleEvent(const KeyPressedEvent& event)
{
	if (!isEnabled() || !callback)
	{
		return;
	}

	callback(KeyMapping(control, event.keyboard, event.scancode));
}

void InputMapper::handleEvent(const MouseMovedEvent& event)
{
	if (!isEnabled() || !callback)
	{
		return;
	}

	if (event.dx != 0)
	{
		MouseMotionAxis axis = (event.dx < 0) ? MouseMotionAxis::NEGATIVE_X : MouseMotionAxis::POSITIVE_X;
		callback(MouseMotionMapping(control, event.mouse, axis));
	}

	if (event.dy != 0)
	{
		MouseMotionAxis axis = (event.dy < 0) ? MouseMotionAxis::NEGATIVE_Y : MouseMotionAxis::POSITIVE_Y;
		callback(MouseMotionMapping(control, event.mouse, axis));
	}
}

void InputMapper::handleEvent(const MouseButtonPressedEvent& event)
{
	if (!isEnabled() || !callback)
	{
		return;
	}

	callback(MouseButtonMapping(control, event.mouse, event.button));
}

void InputMapper::handleEvent(const MouseWheelScrolledEvent& event)
{
	if (!isEnabled() || !callback)
	{
		return;
	}

	if (event.x != 0)
	{
		MouseWheelAxis axis = (event.x < 0) ? MouseWheelAxis::NEGATIVE_X : MouseWheelAxis::POSITIVE_X;
		callback(MouseWheelMapping(control, event.mouse, axis));
	}

	if (event.y != 0)
	{
		MouseWheelAxis axis = (event.y < 0) ? MouseWheelAxis::NEGATIVE_Y : MouseWheelAxis::POSITIVE_Y;
		callback(MouseWheelMapping(control, event.mouse, axis));
	}
}

void InputMapper::handleEvent(const GamepadButtonPressedEvent& event)
{
	if (!isEnabled() || !callback)
	{
		return;
	}

	callback(GamepadButtonMapping(control, event.gamepad, event.button));
}

void InputMapper::handleEvent(const GamepadAxisMovedEvent& event)
{
	if (!isEnabled() || !callback)
	{
		return;
	}

	callback(GamepadAxisMapping(control, event.gamepad, event.axis, event.negative));
}

} // namespace Emergent

