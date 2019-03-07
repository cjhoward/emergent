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

#ifndef EMERGENT_INPUT_ROUTER_HPP
#define EMERGENT_INPUT_ROUTER_HPP

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
class InputRouter:
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
	 * Creates an input router and subscribes it to the input events of the specified event dispatcher.
	 *
	 * @param eventDispatcher Event dispatcher from which input events will be dispatched.
	 */
	InputRouter(EventDispatcher* eventDispatcher);

	/**
	 * Destroys an input router and unsubscribes it from input events.
	 */
	~InputRouter();

	/**
	 * Adds an input mapping to the router.
	 *
	 * @param mapping Input mapping to add.
	 */
	void addMapping(const InputMapping& mapping);


	/**
	 * Removes all input mappings from the router that are associated with the specified control.
	 *
	 * @param control Control with which associated input mappings should be removed.
	 */
	void removeMappings(Control* control);

	/**
	 * Removes all input mappings from the router.
	 */
	void reset();

	/// Returns a list of mappings for the specified control, or nullptr if the control is unmapped.
	const std::list<InputMapping*>* getMappings(Control* control) const;
	
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

#endif // EMERGENT_INPUT_ROUTER_HPP

