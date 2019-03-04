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

#ifndef EMERGENT_INPUT_MAPPER_HPP
#define EMERGENT_INPUT_MAPPER_HPP

#include <emergent/input/input-event.hpp>
#include <emergent/utility/event-handler.hpp>
#include <list>
#include <map>

namespace Emergent
{

class Control;
class EventDispatcher;
class InputMapping;
class KeyMapping;
class MouseMotionMapping;
class MouseWheelMapping;
class MouseButtonMapping;
class GamepadAxisMapping;
class GamepadButtonMapping;
enum class MouseMotionAxis;
enum class MouseWheelAxis;

/**
 * Uses input mappings to route input events to controls.
 *
 * @ingroup input
 */
class InputMapper:
	public EventHandler<KeyPressedEvent>,
	public EventHandler<KeyReleasedEvent>,
	public EventHandler<MouseMovedEvent>,
	public EventHandler<MouseWheelScrolledEvent>,
	public EventHandler<MouseButtonPressedEvent>,
	public EventHandler<MouseButtonReleasedEvent>,
	public EventHandler<GamepadAxisMovedEvent>,
	public EventHandler<GamepadButtonPressedEvent>,
	public EventHandler<GamepadButtonReleasedEvent>
{
public:
	/**
	 * Creates an input mapper and subscribes it to the input events of the specified event dispatcher.
	 *
	 * @param eventDispatcher Event dispatcher from which input events will be dispatched.
	 */
	InputMapper(EventDispatcher* eventDispatcher);

	/**
	 * Destroys an input mapper and unsubscribes it from input events.
	 */
	~InputMapper();

	/// Maps a control to a keyboard key.
	void map(Control* control, Keyboard* keyboard, Scancode scancode);

	/// Maps a control to a mouse motion axis.
	void map(Control* control, Mouse* mouse, MouseMotionAxis axis);

	/// Maps a control to a mouse wheel axis.
	void map(Control* control, Mouse* mouse, MouseWheelAxis axis);

	/// Maps a control to a mouse button.
	void map(Control* control, Mouse* mouse, int button);

	/// Maps a control to a gamepad axis.
	void map(Control* control, Gamepad* gamepad, int axis, bool negative);

	/// Maps a control to a gamepad button.
	void map(Control* control, Gamepad* gamepad, int button);

	/// Unmaps a control.
	void unmap(Control* control);

	/// Unmaps all controls.
	void reset();
	
private:
	virtual void handleEvent(const KeyPressedEvent& event);
	virtual void handleEvent(const KeyReleasedEvent& event);
	virtual void handleEvent(const MouseMovedEvent& event);
	virtual void handleEvent(const MouseWheelScrolledEvent& event);
	virtual void handleEvent(const MouseButtonPressedEvent& event);
	virtual void handleEvent(const MouseButtonReleasedEvent& event);
	virtual void handleEvent(const GamepadAxisMovedEvent& event);
	virtual void handleEvent(const GamepadButtonPressedEvent& event);
	virtual void handleEvent(const GamepadButtonReleasedEvent& event);

	EventDispatcher* eventDispatcher;
	std::map<Control*, std::list<InputMapping*>> controls;
	std::list<KeyMapping*> keyMappings;
	std::list<MouseMotionMapping*> mouseMotionMappings;
	std::list<MouseWheelMapping*> mouseWheelMappings;
	std::list<MouseButtonMapping*> mouseButtonMappings;
	std::list<GamepadAxisMapping*> gamepadAxisMappings;
	std::list<GamepadButtonMapping*> gamepadButtonMappings;
};

} // namespace Emergent

#endif // EMERGENT_INPUT_MAPPER_HPP

