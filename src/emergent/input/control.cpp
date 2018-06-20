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

#include <emergent/input/control.hpp>
#include <emergent/input/mouse.hpp>
#include <emergent/input/keyboard.hpp>
#include <emergent/input/gamepad.hpp>
#include <emergent/input/input-event.hpp>
#include <emergent/input/input-manager.hpp>

namespace Emergent
{

Control::Control():
	deadzone(0.0f),
	currentValue(0.0f),
	previousValue(0.0f),
	activatedCallback(nullptr),
	deactivatedCallback(nullptr),
	valueChangedCallback(nullptr),
	callbacksEnabled(true)
{}

Control::~Control()
{}

void Control::update()
{
	// Perform callbacks, if enabled
	if (callbacksEnabled)
	{
		if (activatedCallback)
		{
			if (isActive() && !wasActive())
			{
				activatedCallback();
			}
		}

		if (deactivatedCallback)
		{
			if (!isActive() && wasActive())
			{
				deactivatedCallback();
			}
		}

		if (valueChangedCallback)
		{
			if (currentValue != previousValue)
			{
				if (isActive() || wasActive())
				{
					valueChangedCallback(currentValue);
				}
			}
		}
	}

	// Stop infinite mouse wheel scrolling
	if (!boundMouseWheelAxes.empty())
	{
		currentValue = 0.0f;
	}
	
	// Update previous value
	previousValue = currentValue;
}

void Control::setDeadzone(float value)
{
	deadzone = value;
}

void Control::setActivatedCallback(std::function<void()> callback)
{
	this->activatedCallback = callback;
}

void Control::setDeactivatedCallback(std::function<void()> callback)
{
	this->deactivatedCallback = callback;
}

void Control::setValueChangedCallback(std::function<void(float)> callback)
{
	this->valueChangedCallback = callback;
}

bool Control::isUnbound() const
{
	return (boundKeys.empty() && boundMouseButtons.empty() && boundMouseWheelAxes.empty() && boundGamepadButtons.empty() && boundGamepadAxes.empty());
}

void Control::bindKey(Keyboard* keyboard, Scancode scancode)
{
	// Check if subscribed to keyboard events
	if (boundKeys.empty())
	{
		keyboard->getInputManager()->subscribe<KeyPressedEvent>(this);
		keyboard->getInputManager()->subscribe<KeyReleasedEvent>(this);
	}

	// Check if already bound to this scancode
	for (auto it: boundKeys)
	{
		if (it.first == keyboard && it.second == scancode)
		{
			return;
		}
	}
	
	// Bind to the key
	boundKeys.push_back(std::pair<Keyboard*, Scancode>(keyboard, scancode));
}

void Control::bindMouseButton(Mouse* mouse, int button)
{
	// Check if subscribed to mouse button events
	if (boundMouseButtons.empty())
	{
		mouse->getInputManager()->subscribe<MouseButtonPressedEvent>(this);
		mouse->getInputManager()->subscribe<MouseButtonReleasedEvent>(this);
	}

	// Checking if already bound to this mouse button
	for (auto it: boundMouseButtons)
	{
		if (it.first == mouse && it.second == button)
		{
			return;
		}
	}
	
	// Bind to the mouse button
	boundMouseButtons.push_back(std::pair<Mouse*, int>(mouse, button));
}

void Control::bindMouseWheelAxis(Mouse* mouse, MouseWheelAxis axis)
{
	if (boundMouseWheelAxes.empty())
	{
		mouse->getInputManager()->subscribe<MouseWheelScrolledEvent>(this);
	}

	// Checking if already observing this mouse
	for (auto it: boundMouseWheelAxes)
	{
		if (it.first == mouse && it.second == axis)
		{
			return;
		}
	}
	
	boundMouseWheelAxes.push_back(std::pair<Mouse*, MouseWheelAxis>(mouse, axis));
}

void Control::bindGamepadButton(Gamepad* gamepad, int button)
{
	if (boundGamepadButtons.empty())
	{
		gamepad->getInputManager()->subscribe<GamepadButtonPressedEvent>(this);
		gamepad->getInputManager()->subscribe<GamepadButtonReleasedEvent>(this);
	}

	for (auto it: boundGamepadButtons)
	{
		if (it.first == gamepad && it.second == button)
		{
			return;
		}
	}
	
	boundGamepadButtons.push_back(std::pair<Gamepad*, int>(gamepad, button));
}

void Control::bindGamepadAxis(Gamepad* gamepad, int axis, bool negative)
{
	if (boundGamepadAxes.empty())
	{
		gamepad->getInputManager()->subscribe<GamepadAxisMovedEvent>(this);
	}

	for (auto it: boundGamepadAxes)
	{
		if (std::get<0>(it) == gamepad && std::get<1>(it) == axis && std::get<2>(it) == negative)
		{
			return;
		}
	}
	
	boundGamepadAxes.push_back(std::make_tuple(gamepad, axis, negative));
}

void Control::unbind()
{
	for (auto it = boundKeys.begin(); it != boundKeys.end(); ++it)
	{
		it->first->getInputManager()->unsubscribe<KeyPressedEvent>(this);
		it->first->getInputManager()->unsubscribe<KeyReleasedEvent>(this);
	}
	boundKeys.clear();

	for (auto it = boundMouseButtons.begin(); it != boundMouseButtons.end(); ++it)
	{
		it->first->getInputManager()->unsubscribe<MouseButtonPressedEvent>(this);
		it->first->getInputManager()->unsubscribe<MouseButtonReleasedEvent>(this);
	}
	boundMouseButtons.clear();

	for (auto it = boundMouseWheelAxes.begin(); it != boundMouseWheelAxes.end(); ++it)
	{
		it->first->getInputManager()->unsubscribe<MouseWheelScrolledEvent>(this);
	}
	boundMouseWheelAxes.clear();

	for (auto it = boundGamepadButtons.begin(); it != boundGamepadButtons.end(); ++it)
	{
		it->first->getInputManager()->unsubscribe<GamepadButtonPressedEvent>(this);
		it->first->getInputManager()->unsubscribe<GamepadButtonReleasedEvent>(this);
	}
	boundGamepadButtons.clear();

	for (auto it = boundGamepadAxes.begin(); it != boundGamepadAxes.end(); ++it)
	{
		std::get<0>(*it)->getInputManager()->unsubscribe<GamepadAxisMovedEvent>(this);
	}
	boundGamepadAxes.clear();
}

void Control::handleEvent(const KeyPressedEvent& event)
{
	for (auto it: boundKeys)
	{
		if (it.first == event.keyboard && it.second == event.scancode)
		{
			currentValue = 1.0f;
			break;
		}
	}
}

void Control::handleEvent(const KeyReleasedEvent& event)
{
	for (auto it: boundKeys)
	{
		if (it.first == event.keyboard && it.second == event.scancode)
		{
			currentValue = 0.0f;
			break;
		}
	}
}

void Control::handleEvent(const MouseButtonPressedEvent& event)
{
	for (auto it: boundMouseButtons)
	{
		if (it.first == event.mouse && it.second == event.button)
		{
			currentValue = 1.0f;
			break;
		}
	}
}

void Control::handleEvent(const MouseButtonReleasedEvent& event)
{
	for (auto it: boundMouseButtons)
	{
		if (it.first == event.mouse && it.second == event.button)
		{
			currentValue = 0.0f;
			break;
		}
	}
}

void Control::handleEvent(const MouseWheelScrolledEvent& event)
{
	for (auto it: boundMouseWheelAxes)
	{
		if (it.first == event.mouse)
		{
			if (it.second == MouseWheelAxis::POSITIVE_X && event.x > 0)
			{
				currentValue += event.x;
				break;
			}
			else if (it.second == MouseWheelAxis::NEGATIVE_X && event.x < 0)
			{
				currentValue -= event.x;
				break;
			}
			else if (it.second == MouseWheelAxis::POSITIVE_Y && event.y > 0)
			{
				currentValue += event.y;
				break;
			}
			else if (it.second == MouseWheelAxis::NEGATIVE_Y && event.y < 0)
			{
				currentValue -= event.y;
				break;
			}
		}
	}
}

void Control::handleEvent(const GamepadButtonPressedEvent& event)
{
	for (auto it: boundGamepadButtons)
	{
		if (it.first == event.gamepad && it.second == event.button)
		{
			currentValue = 1.0f;
			break;
		}
	}
}

void Control::handleEvent(const GamepadButtonReleasedEvent& event)
{
	for (auto it: boundGamepadButtons)
	{
		if (it.first == event.gamepad && it.second == event.button)
		{
			currentValue = 0.0f;
			break;
		}
	}

}

void Control::handleEvent(const GamepadAxisMovedEvent& event)
{
	for (auto it: boundGamepadAxes)
	{
		if (std::get<0>(it) == event.gamepad && std::get<1>(it) == event.axis && std::get<2>(it) == event.negative)
		{
			currentValue = event.value;
			break;
		}
	}
}

const std::list<std::pair<Keyboard*, Scancode>>* Control::getBoundKeys() const
{
	return &boundKeys;
}

const std::list<std::pair<Mouse*, int>>* Control::getBoundMouseButtons() const
{
	return &boundMouseButtons;
}

const std::list<std::pair<Mouse*, MouseWheelAxis>>* Control::getBoundMouseWheelAxes() const
{
	return &boundMouseWheelAxes;
}

const std::list<std::pair<Gamepad*, int>>* Control::getBoundGamepadButtons() const
{
	return &boundGamepadButtons;
}

const std::list<std::tuple<Gamepad*, int, bool>>* Control::getBoundGamepadAxes() const
{
	return &boundGamepadAxes;
}

} // namespace Emergent

