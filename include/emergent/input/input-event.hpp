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

#include <tuple>
#include <utility>

namespace Emergent
{

class Keyboard;
class Mouse;
class Gamepad;

/**
 * An input event which can be used for binding controls.
 *
 * @ingroup input.
 */
class InputEvent
{
public:
	/// Enumerates the types of input events.
	enum class Type
	{
		/// Indicates a null event.
		NONE,

		/// Indicates key press or release event.
		KEY,

		/// Indicates a mouse button press or release event.
		MOUSE_BUTTON,

		/// Indicates a mouse wheel scroll event.
		MOUSE_WHEEL,

		/// Indicates a gamepad button press or release event.
		GAMEPAD_BUTTON,

		/// Indicates a gamepad axis movement event.
		GAMEPAD_AXIS
	};
	
	/// Creates an input event.
	InputEvent();
	
	InputEvent::Type type;
	std::pair<Keyboard*, int> key;
	std::pair<Mouse*, int> mouseButton;
	std::tuple<Mouse*, int, int> mouseWheel;
	std::pair<Gamepad*, int> gamepadButton;
	std::tuple<Gamepad*, int, int> gamepadAxis;
};

} // namespace Emergent

#endif // EMERGENT_INPUT_INPUT_EVENT_HPP

