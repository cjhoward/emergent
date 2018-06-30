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

#ifndef EMERGENT_INPUT_INPUT_MANAGER_HPP
#define EMERGENT_INPUT_INPUT_MANAGER_HPP

#include <emergent/input/input-event.hpp>
#include <list>
#include <string>

namespace Emergent
{

class Clipboard;
class EventDispatcher;
class Gamepad;
class Keyboard;
class Mouse;

/**
 * Abstract base class for input managers.
 *
 * @ingroup input
 */
class InputManager
{
public:
	/**
	 * Creates an input manager.
	 *
	 * @param eventDispatcher Event dispatcher which will dispatch input events.
	 */
	InputManager(EventDispatcher* eventDispatcher);

	/// Destroys an input manager.
	virtual ~InputManager();
	
	/**
	 * Processes input events.
	 */
	virtual void update() = 0;

	/// Registers a keyboard with this input manager.
	void registerKeyboard(Keyboard* keyboard);

	/// Registers a mouse with this input manager.
	void registerMouse(Mouse* mouse);

	/// Registers a gamepad with this input manager.
	void registerGamepad(Gamepad* gamepad);
	
	/// Unregisters a keyboard from this input manager.
	void unregisterKeyboard(Keyboard* keyboard);

	/// Unregisters a mouse from this input manager.
	void unregisterMouse(Mouse* mouse);

	/// Unregisters a gamepad from this input manager.
	void unregisterGamepad(Gamepad* gamepad);
	
	/// Returns whether a keyboard is registered with this input manager.
	bool isRegistered(const Keyboard* keyboard) const;

	/// Returns whether a mouse is registered with this input manager.
	bool isRegistered(const Mouse* mouse) const;

	/// Returns whether a gamepad is registered with this input manager.
	bool isRegistered(const Gamepad* gamepad) const;
	
	/// Returns the registered gamepad with the specified name, or nullptr if a gamepad with that name has not been registered.
	const Gamepad* getGamepad(const std::string& name) const;

	/// @copydoc InputManager::getGamepad() const
	Gamepad* getGamepad(const std::string& name);

	/// Returns the clipboard.
	virtual const Clipboard* getClipboard() const = 0;

	/// @copydoc InputManager::getClipboard() const
	virtual Clipboard* getClipboard() = 0;
	
	/// Returns the list of registered keyboard.
	const std::list<Keyboard*>* getKeyboards() const;

	/// Returns the list of registered mice.
	const std::list<Mouse*>* getMice() const;

	/// Returns the list of registered gamepads.
	const std::list<Gamepad*>* getGamepads() const;

	/// Returns the event dispatcher used to dispatch input events.
	const EventDispatcher* getEventDispatcher() const;

	/// @copydoc InputManager::getEventDispatcher() const
	EventDispatcher* getEventDispatcher();

protected:
	EventDispatcher* eventDispatcher;
	
private:
	friend class Keyboard;
	friend class Mouse;
	friend class Gamepad;

	std::list<Keyboard*> keyboards;
	std::list<Mouse*> mice;
	std::list<Gamepad*> gamepads;
};

inline const std::list<Keyboard*>* InputManager::getKeyboards() const
{
	return &keyboards;
}

inline const std::list<Mouse*>* InputManager::getMice() const
{
	return &mice;
}

inline const std::list<Gamepad*>* InputManager::getGamepads() const
{
	return &gamepads;
}

inline const EventDispatcher* InputManager::getEventDispatcher() const
{
	return eventDispatcher;
}

inline EventDispatcher* InputManager::getEventDispatcher()
{
	return eventDispatcher;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_INPUT_MANAGER_HPP

