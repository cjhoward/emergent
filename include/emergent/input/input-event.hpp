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

#ifndef EMERGENT_INPUT_INPUT_EVENT_HPP
#define EMERGENT_INPUT_INPUT_EVENT_HPP

#include <emergent/utility/event.hpp>

namespace Emergent
{

enum class Scancode;
class Window;
class Keyboard;
class Mouse;
class Gamepad;

/**
 * Enumerates all possible input event type identifiers.
 *
 * @ingroup input
 */
enum class InputEventType
{
	APPLICATION_CLOSED,
	WINDOW_CLOSED,
	WINDOW_RESIZED,
	KEY_PRESSED,
	KEY_RELEASED,
	MOUSE_MOVED,
	MOUSE_BUTTON_PRESSED,
	MOUSE_BUTTON_RELEASED,
	MOUSE_WHEEL_SCROLLED,
	GAMEPAD_BUTTON_PRESSED,
	GAMEPAD_BUTTON_RELEASED,
	GAMEPAD_AXIS_MOVED
};

/**
 * Abstract base class for input events.
 *
 * @ingroup input
 */
template <InputEventType inputEventType>
class InputEvent: public Event<static_cast<std::size_t>(inputEventType)>
{
public:
	/// Flag to indicate this class is an input event
	static const bool IS_INPUT_EVENT = true;
	
	virtual EventBase* clone() const = 0;
};

/**
 * Input event which indicates the application has been requested to close.
 *
 * @ingroup input
 */
class ApplicationClosedEvent: public InputEvent<InputEventType::APPLICATION_CLOSED>
{
public:
	virtual EventBase* clone() const;
};

/**
 * Input event which indicates a window has been closed.
 *
 * @ingroup input
 */
class WindowClosedEvent: public InputEvent<InputEventType::WINDOW_CLOSED>
{
public:
	virtual EventBase* clone() const;

	Window* window;
};

/**
 * Input event which indicates a window has been resized.
 *
 * @ingroup input
 */
class WindowResizedEvent: public InputEvent<InputEventType::WINDOW_RESIZED>
{
public:
	virtual EventBase* clone() const;

	Window* window;
	int width;
	int height;
};

/**
 * Input event which indicates a keyboard key has been pressed.
 *
 * @ingroup input
 */
class KeyPressedEvent: public InputEvent<InputEventType::KEY_PRESSED>
{
public:
	virtual EventBase* clone() const;

	Keyboard* keyboard;
	Scancode scancode;
};

/**
 * Input event which indicates a keyboard key has been released.
 *
 * @ingroup input
 */
class KeyReleasedEvent: public InputEvent<InputEventType::KEY_RELEASED>
{
public:
	virtual EventBase* clone() const;

	Keyboard* keyboard;
	Scancode scancode;
};

/**
 * Input event which indicates a mouse has been moved.
 *
 * @ingroup input
 */
class MouseMovedEvent: public InputEvent<InputEventType::MOUSE_MOVED>
{
public:
	virtual EventBase* clone() const;

	Mouse* mouse;
	int x;
	int y;
};

/**
 * Input event which indicates a mouse button has been pressed.
 *
 * @ingroup input
 */
class MouseButtonPressedEvent: public InputEvent<InputEventType::MOUSE_BUTTON_PRESSED>
{
public:
	virtual EventBase* clone() const;

	Mouse* mouse;
	int button;
	int x;
	int y;
};

/**
 * Input event which indicates a mouse button has been released.
 *
 * @ingroup input
 */
class MouseButtonReleasedEvent: public InputEvent<InputEventType::MOUSE_BUTTON_RELEASED>
{
public:
	virtual EventBase* clone() const;

	Mouse* mouse;
	int button;
	int x;
	int y;
};

/**
 * Input event which indicates a mouse wheel has been scrolled.
 *
 * @ingroup input
 */
class MouseWheelScrolledEvent: public InputEvent<InputEventType::MOUSE_WHEEL_SCROLLED>
{
public:
	virtual EventBase* clone() const;

	Mouse* mouse;
	int x;
	int y;
};

/**
 * Input event which indicates a gamepad button has been pressed.
 *
 * @ingroup input
 */
class GamepadButtonPressedEvent: public InputEvent<InputEventType::GAMEPAD_BUTTON_PRESSED>
{
public:
	virtual EventBase* clone() const;

	Gamepad* gamepad;
	int button;
};

/**
 * Input event which indicates a gamepad button has been released.
 *
 * @ingroup input
 */
class GamepadButtonReleasedEvent: public InputEvent<InputEventType::GAMEPAD_BUTTON_RELEASED>
{
public:
	virtual EventBase* clone() const;

	Gamepad* gamepad;
	int button;
};

/**
 * Input event which indicates a gamepad axis has been moved.
 *
 * @ingroup input
 */
class GamepadAxisMovedEvent: public InputEvent<InputEventType::GAMEPAD_AXIS_MOVED>
{
public:
	virtual EventBase* clone() const;

	Gamepad* gamepad;
	int axis;
	bool negative;
	float value;
};

} // namespace Emergent

#endif // EMERGENT_INPUT_INPUT_EVENT_HPP

