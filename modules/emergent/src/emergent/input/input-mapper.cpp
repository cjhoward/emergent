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
#include <emergent/input/control.hpp>
#include <emergent/input/input-mapping.hpp>
#include <emergent/input/mouse.hpp>
#include <emergent/utility/event-dispatcher.hpp>

namespace Emergent
{

InputMapper::InputMapper(EventDispatcher* eventDispatcher):
	eventDispatcher(eventDispatcher)
{
	eventDispatcher->subscribe<KeyPressedEvent>(this);
	eventDispatcher->subscribe<KeyReleasedEvent>(this);
	eventDispatcher->subscribe<MouseMovedEvent>(this);
	eventDispatcher->subscribe<MouseWheelScrolledEvent>(this);
	eventDispatcher->subscribe<MouseButtonPressedEvent>(this);
	eventDispatcher->subscribe<MouseButtonReleasedEvent>(this);
	eventDispatcher->subscribe<GamepadAxisMovedEvent>(this);
	eventDispatcher->subscribe<GamepadButtonPressedEvent>(this);
	eventDispatcher->subscribe<GamepadButtonReleasedEvent>(this);
}

InputMapper::~InputMapper()
{
	reset();

	eventDispatcher->unsubscribe<KeyPressedEvent>(this);
	eventDispatcher->unsubscribe<KeyReleasedEvent>(this);
	eventDispatcher->unsubscribe<MouseMovedEvent>(this);
	eventDispatcher->unsubscribe<MouseWheelScrolledEvent>(this);
	eventDispatcher->unsubscribe<MouseButtonPressedEvent>(this);
	eventDispatcher->unsubscribe<MouseButtonReleasedEvent>(this);
	eventDispatcher->unsubscribe<GamepadAxisMovedEvent>(this);
	eventDispatcher->unsubscribe<GamepadButtonPressedEvent>(this);
	eventDispatcher->unsubscribe<GamepadButtonReleasedEvent>(this);
}

void InputMapper::map(Control* control, Keyboard* keyboard, Scancode scancode)
{
	KeyMapping* mapping = new KeyMapping(control, keyboard, scancode);
	controls[control].push_back(mapping);
	keyMappings.push_back(mapping);
}

void InputMapper::map(Control* control, Mouse* mouse, MouseMotionAxis axis)
{
	MouseMotionMapping* mapping = new MouseMotionMapping(control, mouse, axis);
	controls[control].push_back(mapping);
	mouseMotionMappings.push_back(mapping);
}

void InputMapper::map(Control* control, Mouse* mouse, MouseWheelAxis axis)
{
	MouseWheelMapping* mapping = new MouseWheelMapping(control, mouse, axis);
	controls[control].push_back(mapping);
	mouseWheelMappings.push_back(mapping);
}

void InputMapper::map(Control* control, Mouse* mouse, int button)
{
	MouseButtonMapping* mapping = new MouseButtonMapping(control, mouse, button);
	controls[control].push_back(mapping);
	mouseButtonMappings.push_back(mapping);
}

void InputMapper::map(Control* control, Gamepad* gamepad, int axis, bool negative)
{
	GamepadAxisMapping* mapping = new GamepadAxisMapping(control, gamepad, axis, negative);
	controls[control].push_back(mapping);
	gamepadAxisMappings.push_back(mapping);
}

void InputMapper::map(Control* control, Gamepad* gamepad, int button)
{
	GamepadButtonMapping* mapping = new GamepadButtonMapping(control, gamepad, button);
	controls[control].push_back(mapping);
	gamepadButtonMappings.push_back(mapping);
}

void InputMapper::unmap(Control* control)
{
	auto it = controls.find(control);
	if (it != controls.end())
	{
		for (InputMapping* mapping: it->second)
		{
			switch (mapping->getType())
			{
				case InputMappingType::KEY:
					keyMappings.remove(static_cast<KeyMapping*>(mapping));
					break;

				case InputMappingType::MOUSE_MOTION:
					mouseMotionMappings.remove(static_cast<MouseMotionMapping*>(mapping));
					break;

				case InputMappingType::MOUSE_WHEEL:
					mouseWheelMappings.remove(static_cast<MouseWheelMapping*>(mapping));
					break;

				case InputMappingType::MOUSE_BUTTON:
					mouseButtonMappings.remove(static_cast<MouseButtonMapping*>(mapping));
					break;

				case InputMappingType::GAMEPAD_AXIS:
					gamepadAxisMappings.remove(static_cast<GamepadAxisMapping*>(mapping));
					break;

				case InputMappingType::GAMEPAD_BUTTON:
					gamepadButtonMappings.remove(static_cast<GamepadButtonMapping*>(mapping));
					break;

				default:
					break;
			}

			delete mapping;
		}

		controls.erase(it);
	}
}

void InputMapper::reset()
{
	for (auto it = controls.begin(); it != controls.end(); ++it)
	{
		for (InputMapping* mapping: it->second)
		{
			delete mapping;
		}
	}

	controls.clear();
	keyMappings.clear();
	mouseMotionMappings.clear();
	mouseWheelMappings.clear();
	mouseButtonMappings.clear();
	gamepadAxisMappings.clear();
	gamepadButtonMappings.clear();
}

void InputMapper::handleEvent(const KeyPressedEvent& event)
{
	for (const KeyMapping* mapping: keyMappings)
	{
		if (mapping->keyboard == event.keyboard && mapping->scancode == event.scancode)
		{
			mapping->control->setCurrentValue(1.0f);
		}
	}
}

void InputMapper::handleEvent(const KeyReleasedEvent& event)
{
	for (const KeyMapping* mapping: keyMappings)
	{
		if (mapping->keyboard == event.keyboard && mapping->scancode == event.scancode)
		{
			mapping->control->setCurrentValue(0.0f);
		}
	}
}

void InputMapper::handleEvent(const MouseMovedEvent& event)
{
	for (const MouseMotionMapping* mapping: mouseMotionMappings)
	{
		if (mapping->mouse == event.mouse)
		{
			if (mapping->axis == MouseMotionAxis::NEGATIVE_X && event.dx < 0)
			{
				mapping->control->setTemporaryValue(-event.dx);
			}
			else if (mapping->axis == MouseMotionAxis::POSITIVE_X && event.dx > 0)
			{
				mapping->control->setTemporaryValue(event.dx);
			}
			else if (mapping->axis == MouseMotionAxis::NEGATIVE_Y && event.dy < 0)
			{
				mapping->control->setTemporaryValue(-event.dy);
			}
			else if (mapping->axis == MouseMotionAxis::POSITIVE_Y && event.dy > 0)
			{
				mapping->control->setTemporaryValue(event.dy);
			}
		}
	}
}

void InputMapper::handleEvent(const MouseWheelScrolledEvent& event)
{
	for (const MouseWheelMapping* mapping: mouseWheelMappings)
	{
		if (mapping->mouse == event.mouse)
		{
			if (mapping->axis == MouseWheelAxis::NEGATIVE_X && event.x < 0)
			{
				mapping->control->setTemporaryValue(-event.x);
			}
			else if (mapping->axis == MouseWheelAxis::POSITIVE_X && event.x > 0)
			{
				mapping->control->setTemporaryValue(event.x);
			}
			else if (mapping->axis == MouseWheelAxis::NEGATIVE_Y && event.y < 0)
			{
				mapping->control->setTemporaryValue(-event.y);
			}
			else if (mapping->axis == MouseWheelAxis::POSITIVE_Y && event.y > 0)
			{
				mapping->control->setTemporaryValue(event.y);
			}
		}
	}
}

void InputMapper::handleEvent(const MouseButtonPressedEvent& event)
{
	for (const MouseButtonMapping* mapping: mouseButtonMappings)
	{
		if (mapping->mouse == event.mouse && mapping->button == event.button)
		{
			mapping->control->setCurrentValue(1.0f);
		}
	}
}

void InputMapper::handleEvent(const MouseButtonReleasedEvent& event)
{
	for (const MouseButtonMapping* mapping: mouseButtonMappings)
	{
		if (mapping->mouse == event.mouse && mapping->button == event.button)
		{
			mapping->control->setCurrentValue(0.0f);
		}
	}
}

void InputMapper::handleEvent(const GamepadAxisMovedEvent& event)
{
	for (const GamepadAxisMapping* mapping: gamepadAxisMappings)
	{
		if (mapping->gamepad == event.gamepad && mapping->axis == event.axis && mapping->negative == event.negative)
		{
			mapping->control->setCurrentValue(event.value);
		}
	}
}

void InputMapper::handleEvent(const GamepadButtonPressedEvent& event)
{
	for (const GamepadButtonMapping* mapping: gamepadButtonMappings)
	{
		if (mapping->gamepad == event.gamepad && mapping->button == event.button)
		{
			mapping->control->setCurrentValue(1.0f);
		}
	}
}

void InputMapper::handleEvent(const GamepadButtonReleasedEvent& event)
{
	for (const GamepadButtonMapping* mapping: gamepadButtonMappings)
	{
		if (mapping->gamepad == event.gamepad && mapping->button == event.button)
		{
			mapping->control->setCurrentValue(0.0f);
		}
	}
}

} // namespace Emergent

