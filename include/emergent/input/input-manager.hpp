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

#include <list>
#include <string>

namespace Emergent
{

class Keyboard;
class Mouse;
class Gamepad;
class InputEvent;

/**
 * Abstract base class for input managers.
 *
 * @ingroup input
 */
class InputManager
{
public:
	/// Creates an input manager.
	InputManager();

	/// Destroys an input manager.
	virtual ~InputManager();
	
	/**
	 * Processes input events.
	 */
	virtual void update() = 0;
	
	/**
	 * Listens for the next input event. Should be called before InputManager::update().
	 *
	 * @param inputEvent Pointer to input event which will be filled with the next event.
	 */
	virtual void listen(InputEvent* inputEvent) = 0;
	
	/// Returns whether the application has been requested to close.
	bool wasClosed() const;
	
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
	
	/// Returns the list of registered keyboard.
	const std::list<Keyboard*>* getKeyboards() const;

	/// Returns the list of registered mice.
	const std::list<Mouse*>* getMice() const;

	/// Returns the list of registered gamepads.
	const std::list<Gamepad*>* getGamepads() const;
	
protected:
	bool closed;
	
private:
	std::list<Keyboard*> keyboards;
	std::list<Mouse*> mice;
	std::list<Gamepad*> gamepads;
};

inline bool InputManager::wasClosed() const
{
	return closed;
}

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

} // namespace Emergent

#endif // EMERGENT_INPUT_INPUT_MANAGER_HPP
