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
 * Input event which indicates the application has been requested to close.
 *
 * @ingroup input
 */
class ApplicationClosedEvent: public Event<ApplicationClosedEvent>
{
public:
	virtual EventBase* clone() const;
};

/**
 * Input event which indicates a window has been closed.
 *
 * @ingroup input
 */
class WindowClosedEvent: public Event<WindowClosedEvent>
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
class WindowResizedEvent: public Event<WindowResizedEvent>
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
class KeyPressedEvent: public Event<KeyPressedEvent>
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
class KeyReleasedEvent: public Event<KeyReleasedEvent>
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
class MouseMovedEvent: public Event<MouseMovedEvent>
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
class MouseButtonPressedEvent: public Event<MouseButtonPressedEvent>
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
class MouseButtonReleasedEvent: public Event<MouseButtonReleasedEvent>
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
class MouseWheelScrolledEvent: public Event<MouseWheelScrolledEvent>
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
class GamepadButtonPressedEvent: public Event<GamepadButtonPressedEvent>
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
class GamepadButtonReleasedEvent: public Event<GamepadButtonReleasedEvent>
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
class GamepadAxisMovedEvent: public Event<GamepadAxisMovedEvent>
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

