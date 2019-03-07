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

#ifndef EMERGENT_INPUT_INPUT_MAPPING_HPP
#define EMERGENT_INPUT_INPUT_MAPPING_HPP

namespace Emergent
{

enum class MouseMotionAxis;
enum class MouseWheelAxis;
enum class Scancode;
class Control;
class Keyboard;
class Mouse;
class Gamepad;

/**
 * Enumerates the supported types of control mappings.
 *
 * @ingroup input
 */
enum class InputMappingType
{
	KEY,
	MOUSE_MOTION,
	MOUSE_WHEEL,
	MOUSE_BUTTON,
	GAMEPAD_AXIS,
	GAMEPAD_BUTTON
};

/**
 * Abstract base class for input mappings.
 *
 * @ingroup input
 */
class InputMapping
{
public:
	InputMapping() = default;
	InputMapping(Control* control);
	virtual ~InputMapping() = default;

	/// Returns this control mapping's type.
	virtual InputMappingType getType() const = 0;

	Control* control;
};

/**
 * A mapping between a control and a keyboard key.
 *
 * @ingroup input
 */
class KeyMapping: public InputMapping
{
public:
	KeyMapping() = default;
	KeyMapping(const KeyMapping& mapping);
	KeyMapping(Control* control, Keyboard* keyboard, Scancode scancode);
	virtual ~KeyMapping() = default;
	KeyMapping& operator=(const KeyMapping& mapping);
	virtual InputMappingType getType() const;

	Keyboard* keyboard;
	Scancode scancode;
};

inline InputMappingType KeyMapping::getType() const
{
	return InputMappingType::KEY;
}

/**
 * A mapping between a control and a mouse motion axis.
 *
 * @ingroup input
 */
class MouseMotionMapping: public InputMapping
{
public:
	MouseMotionMapping() = default;
	MouseMotionMapping(const MouseMotionMapping& mapping);
	MouseMotionMapping(Control* control, Mouse* mouse, MouseMotionAxis axis);
	virtual ~MouseMotionMapping() = default;
	MouseMotionMapping& operator=(const MouseMotionMapping& mapping);
	virtual InputMappingType getType() const;

	Mouse* mouse;
	MouseMotionAxis axis;
};

inline InputMappingType MouseMotionMapping::getType() const
{
	return InputMappingType::MOUSE_MOTION;
}

/**
 * A mapping between a control and a mouse wheel axis.
 *
 * @ingroup input
 */
class MouseWheelMapping: public InputMapping
{
public:
	MouseWheelMapping() = default;
	MouseWheelMapping(const MouseWheelMapping& mapping);
	MouseWheelMapping(Control* control, Mouse* mouse, MouseWheelAxis axis);
	virtual ~MouseWheelMapping() = default;
	MouseWheelMapping& operator=(const MouseWheelMapping& mapping);
	virtual InputMappingType getType() const;

	Mouse* mouse;
	MouseWheelAxis axis;
};

inline InputMappingType MouseWheelMapping::getType() const
{
	return InputMappingType::MOUSE_WHEEL;
}

/**
 * A mapping between a control and a mouse button.
 *
 * @ingroup input
 */
class MouseButtonMapping: public InputMapping
{
public:
	MouseButtonMapping() = default;
	MouseButtonMapping(const MouseButtonMapping& mapping);
	MouseButtonMapping(Control* control, Mouse* mouse, int button);
	virtual ~MouseButtonMapping() = default;
	MouseButtonMapping& operator=(const MouseButtonMapping& mapping);
	virtual InputMappingType getType() const;

	Mouse* mouse;
	int button;
};

inline InputMappingType MouseButtonMapping::getType() const
{
	return InputMappingType::MOUSE_BUTTON;
}

/**
 * A mapping between a control and a gamepad axis.
 *
 * @ingroup input
 */
class GamepadAxisMapping: public InputMapping
{
public:
	GamepadAxisMapping() = default;
	GamepadAxisMapping(const GamepadAxisMapping& mapping);
	GamepadAxisMapping(Control* control, Gamepad* gamepad, int axis, bool negative);
	virtual ~GamepadAxisMapping() = default;
	GamepadAxisMapping& operator=(const GamepadAxisMapping& mapping);
	virtual InputMappingType getType() const;

	Gamepad* gamepad;
	int axis;
	bool negative;
};

inline InputMappingType GamepadAxisMapping::getType() const
{
	return InputMappingType::GAMEPAD_AXIS;
}

/**
 * A mapping between a control and a gamepad button.
 *
 * @ingroup input.
 */
class GamepadButtonMapping: public InputMapping
{
public:
	GamepadButtonMapping() = default;
	GamepadButtonMapping(const GamepadButtonMapping& mapping);
	GamepadButtonMapping(Control* control, Gamepad* gamepad, int button);
	virtual ~GamepadButtonMapping() = default;
	GamepadButtonMapping& operator=(const GamepadButtonMapping& mapping);
	virtual InputMappingType getType() const;

	Gamepad* gamepad;
	int button;
};

inline InputMappingType GamepadButtonMapping::getType() const
{
	return InputMappingType::GAMEPAD_BUTTON;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_INPUT_MAPPING_HPP

