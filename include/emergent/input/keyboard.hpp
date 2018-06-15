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

#ifndef EMERGENT_INPUT_KEYBOARD_HPP
#define EMERGENT_INPUT_KEYBOARD_HPP

#include <emergent/input/input-device.hpp>
#include <list>

namespace Emergent
{

class KeyObserver;

/**
 * Keyboard input device.
 *
 * @ingroup input
 */
class Keyboard: public InputDevice
{
public:
	/**
	 * Creates a keyboard input device.
	 *
	 * @param name Name of the keyboard
	 */
	Keyboard(const std::string& name);

	/// Destroys a keyboard input device.
	virtual ~Keyboard();
	
	/// Returns InputDevice::Type::KEYBOARD
	InputDevice::Type getType() const;
	
	/// Adds a key observer to this keyboard.
	void addKeyObserver(KeyObserver* observer);

	/// Removes a key observer from this keyboard.
	void removeKeyObserver(KeyObserver* observer);

	/// Removes all key observers from this keyboard.
	void removeKeyObservers();
	
	/**
	 * Simulates a key press. Notifies all key observers via KeyObserver::keyPressed().
	 *
	 * @param scancode Scancode of the simulated key press.
	 */
	void press(int scancode);

	/**
	 * Simulates a key release. Notifies all key observers via KeyObserver::keyReleased().
	 *
	 * @param scancode Scancode of the simulated key release.
	 */
	void release(int scancode);
	
private:
	std::list<KeyObserver*> keyObservers;
};

inline InputDevice::Type Keyboard::getType() const
{
	return InputDevice::Type::KEYBOARD;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_KEYBOARD_HPP

