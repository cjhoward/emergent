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
	// Check if already observing this keyboard
	bool observing = false;
	for (auto it: boundKeys)
	{
		if (it.first == keyboard)
		{
			observing = true;
			break;
		}
	}
	
	if (!observing)
		keyboard->addKeyObserver(static_cast<KeyObserver*>(this));
	boundKeys.push_back(std::pair<Keyboard*, Scancode>(keyboard, scancode));
}

void Control::bindMouseButton(Mouse* mouse, int button)
{
	// Checking if already observing this mouse
	bool observing = false;
	for (auto it: boundMouseButtons)
	{
		if (it.first == mouse)
		{
			observing = true;
			break;
		}
	}
	
	if (!observing)
		mouse->addMouseButtonObserver(static_cast<MouseButtonObserver*>(this));
	boundMouseButtons.push_back(std::pair<Mouse*, int>(mouse, button));
}

void Control::bindMouseWheelAxis(Mouse* mouse, MouseWheelAxis axis)
{
	// Checking if already observing this mouse
	bool observing = false;
	for (auto it: boundMouseWheelAxes)
	{
		if (it.first == mouse)
		{
			observing = true;
			break;
		}
	}
	
	if (!observing)
		mouse->addMouseWheelObserver(static_cast<MouseWheelObserver*>(this));
	boundMouseWheelAxes.push_back(std::pair<Mouse*, MouseWheelAxis>(mouse, axis));
}

void Control::bindGamepadButton(Gamepad* gamepad, int button)
{
	bool observing = false;
	for (auto it: boundGamepadButtons)
	{
		if (it.first == gamepad)
		{
			observing = true;
			break;
		}
	}
	
	if (!observing)
		gamepad->addGamepadButtonObserver(static_cast<GamepadButtonObserver*>(this));
	boundGamepadButtons.push_back(std::pair<Gamepad*, int>(gamepad, button));
}

void Control::bindGamepadAxis(Gamepad* gamepad, int axis, bool negative)
{
	bool observing = false;
	for (auto it: boundGamepadAxes)
	{
		if (std::get<0>(it) == gamepad)
		{
			observing = true;
			break;
		}
	}
	
	if (!observing)
		gamepad->addGamepadAxisObserver(static_cast<GamepadAxisObserver*>(this));
	boundGamepadAxes.push_back(std::make_tuple(gamepad, axis, negative));
}

void Control::bind(const InputEvent& event)
{
	switch (event.type)
	{
		case InputEvent::Type::KEY:
			bindKey(event.key.first, event.key.second);
			break;
		
		case InputEvent::Type::MOUSE_BUTTON:
			bindMouseButton(event.mouseButton.first, event.mouseButton.second);
			break;
		
		case InputEvent::Type::MOUSE_WHEEL:
		{
			int x = std::get<1>(event.mouseWheel);
			int y = std::get<2>(event.mouseWheel);
			
			MouseWheelAxis axis;
			if (x > 0)
				axis = MouseWheelAxis::POSITIVE_X;
			else if (x < 0)
				axis = MouseWheelAxis::NEGATIVE_X;
			else if (y > 0)
				axis = MouseWheelAxis::POSITIVE_Y;
			else if (y < 0)
				axis = MouseWheelAxis::NEGATIVE_Y;
			else
				break;
			
			bindMouseWheelAxis(std::get<0>(event.mouseWheel), axis);
			break;
		}
		
		case InputEvent::Type::GAMEPAD_BUTTON:
			bindGamepadButton(event.gamepadButton.first, event.gamepadButton.second);
			break;
		
		case InputEvent::Type::GAMEPAD_AXIS:
			bindGamepadAxis(std::get<0>(event.gamepadAxis), std::get<1>(event.gamepadAxis), std::get<2>(event.gamepadAxis));
			break;
		
		default:
			break;
	}
}

void Control::unbind()
{
	while (!boundKeys.empty())
	{
		// Remove the first bound key and stop observing its keyboard
		Keyboard* keyboard = boundKeys.front().first;
		keyboard->removeKeyObserver(static_cast<KeyObserver*>(this));
		boundKeys.pop_front();
		
		// Remove other bound keys which are associated with the keyboard
		auto it = boundKeys.begin();
		while (it != boundKeys.end())
		{
			if (it->first == keyboard)
				boundKeys.erase(it++);
			else
				++it;
		}
	}
	
	while (!boundMouseButtons.empty())
	{
		// Remove the first bound mouse button and stop observing its mouse
		Mouse* mouse = boundMouseButtons.front().first;
		mouse->removeMouseButtonObserver(static_cast<MouseButtonObserver*>(this));
		boundMouseButtons.pop_front();
		
		// Remove other bound mouse buttons which are associated with the mouse
		auto it = boundMouseButtons.begin();
		while (it != boundMouseButtons.end())
		{
			if (it->first == mouse)
				boundMouseButtons.erase(it++);
			else
				++it;
		}
	}
	
	while (!boundMouseWheelAxes.empty())
	{
		// Remove the first bound mouse button and stop observing its mouse
		Mouse* mouse = boundMouseWheelAxes.front().first;
		mouse->removeMouseWheelObserver(static_cast<MouseWheelObserver*>(this));
		boundMouseWheelAxes.pop_front();
		
		// Remove other bound mouse buttons which are associated with the mouse
		auto it = boundMouseWheelAxes.begin();
		while (it != boundMouseWheelAxes.end())
		{
			if (it->first == mouse)
				boundMouseWheelAxes.erase(it++);
			else
				++it;
		}
	}
	
	while (!boundGamepadButtons.empty())
	{
		// Remove the first bound gamepad button and stop observing its gamepad
		Gamepad* gamepad = boundGamepadButtons.front().first;
		gamepad->removeGamepadButtonObserver(static_cast<GamepadButtonObserver*>(this));
		boundGamepadButtons.pop_front();
		
		// Remove other bound gamepad buttons which are associated with the gamepad
		auto it = boundGamepadButtons.begin();
		while (it != boundGamepadButtons.end())
		{
			if (it->first == gamepad)
				boundGamepadButtons.erase(it++);
			else
				++it;
		}
	}
	
	while (!boundGamepadAxes.empty())
	{
		// Remove the first bound gamepad axis and stop observing its gamepad
		Gamepad* gamepad = std::get<0>(boundGamepadAxes.front());
		gamepad->removeGamepadAxisObserver(static_cast<GamepadAxisObserver*>(this));
		boundGamepadAxes.pop_front();
		
		// Remove other bound gamepad axes which are associated with the gamepad
		auto it = boundGamepadAxes.begin();
		while (it != boundGamepadAxes.end())
		{
			if (std::get<0>(*it) == gamepad)
				boundGamepadAxes.erase(it++);
			else
				++it;
		}
	}
}

void Control::keyPressed(Scancode scancode)
{
	for (auto it: boundKeys)
	{
		if (it.second == scancode)
		{
			currentValue = 1.0f;
			break;
		}
	}
}

void Control::keyReleased(Scancode scancode)
{
	for (auto it: boundKeys)
	{
		if (it.second == scancode)
		{
			currentValue = 0.0f;
			break;
		}
	}
}

void Control::mouseButtonPressed(int button, int x, int y)
{
	for (auto it: boundMouseButtons)
	{
		if (it.second == button)
		{
			currentValue = 1.0f;
			break;
		}
	}
}

void Control::mouseButtonReleased(int button, int x, int y)
{
	for (auto it: boundMouseButtons)
	{
		if (it.second == button)
		{
			currentValue = 0.0f;
			break;
		}
	}
}

void Control::mouseWheelScrolled(int x, int y)
{
	for (auto it: boundMouseWheelAxes)
	{
		if (it.second == MouseWheelAxis::POSITIVE_X && x > 0)
		{
			currentValue += x;
			break;
		}
		else if (it.second == MouseWheelAxis::NEGATIVE_X && x < 0)
		{
			currentValue -= x;
			break;
		}
		else if (it.second == MouseWheelAxis::POSITIVE_Y && y > 0)
		{
			currentValue += y;
			break;
		}
		else if (it.second == MouseWheelAxis::NEGATIVE_Y && y < 0)
		{
			currentValue -= y;
			break;
		}
	}
}

void Control::gamepadButtonPressed(int button)
{
	for (auto it: boundGamepadButtons)
	{
		if (it.second == button)
		{
			currentValue = 1.0f;
			break;
		}
	}
}

void Control::gamepadButtonReleased(int button)
{
	for (auto it: boundGamepadButtons)
	{
		if (it.second == button)
		{
			currentValue = 0.0f;
			break;
		}
	}
}

void Control::gamepadAxisMoved(int axis, bool negative, float value)
{
	for (auto it: boundGamepadAxes)
	{
		if (std::get<1>(it) == axis && std::get<2>(it) == negative)
		{
			currentValue = value;
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

