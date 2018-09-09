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

#ifndef EMERGENT_UTILITY_DEVICE_MANAGER_HPP
#define EMERGENT_UTILITY_DEVICE_MANAGER_HPP

#include <list>
#include <string>

namespace Emergent
{

class OSInterface;
class Display;
class Keyboard;
class Mouse;
class Gamepad;

/**
 * Maintains lists of hardware devices.
 *
 * @ingroup utility
 */
class DeviceManager
{
public:
	/**
	 * Creates a device manager.
	 *
	 * @param osInterface OS interface with which to associate this device manager.
	 */
	DeviceManager(OSInterface* osInterface);

	/**
	 * Destroys a device manager.
	 */
	~DeviceManager();

	/// Registers a display with this window manager.
	void registerDisplay(Display* display);

	/// Registers a keyboard with this device manager.
	void registerKeyboard(Keyboard* keyboard);

	/// Registers a mouse with this device manager.
	void registerMouse(Mouse* mouse);

	/// Registers a gamepad with this device manager.
	void registerGamepad(Gamepad* gamepad);
	
	/// Unregisters a display from this window manager.
	void unregisterDisplay(Display* display);
	
	/// Unregisters a keyboard from this device manager.
	void unregisterKeyboard(Keyboard* keyboard);

	/// Unregisters a mouse from this device manager.
	void unregisterMouse(Mouse* mouse);

	/// Unregisters a gamepad from this device manager.
	void unregisterGamepad(Gamepad* gamepad);

	/// Returns whether a display is registered with this device manager.
	bool isRegistered(const Display* display) const;
	
	/// Returns whether a keyboard is registered with this device manager.
	bool isRegistered(const Keyboard* keyboard) const;

	/// Returns whether a mouse is registered with this device manager.
	bool isRegistered(const Mouse* mouse) const;

	/// Returns whether a gamepad is registered with this device manager.
	bool isRegistered(const Gamepad* gamepad) const;

	/// Returns the associated OS interface.
	const OSInterface* getOSInterface() const;

	/// @copydoc DeviceManager::getOSInterface() const
	OSInterface* getOSInterface();
	
	/// Returns the registered gamepad with the specified name, or nullptr if a gamepad with that name has not been registered.
	const Gamepad* getGamepad(const std::string& name) const;

	/// @copydoc DeviceManager::getGamepad(const std::string&) const
	Gamepad* getGamepad(const std::string& name);

	/// Returns the list of registered displays.
	const std::list<Display*>* getDisplays() const;

	/// Returns the list of registered keyboards.
	const std::list<Keyboard*>* getKeyboards() const;

	/// Returns the list of registered mice.
	const std::list<Mouse*>* getMice() const;

	/// Returns the list of registered gamepads.
	const std::list<Gamepad*>* getGamepads() const;

private:
	OSInterface* osInterface;
	std::list<Display*> displays;
	std::list<Keyboard*> keyboards;
	std::list<Mouse*> mice;
	std::list<Gamepad*> gamepads;
};

inline const OSInterface* DeviceManager::getOSInterface() const
{
	return osInterface;
}

inline OSInterface* DeviceManager::getOSInterface()
{
	return osInterface;
}

inline const std::list<Display*>* DeviceManager::getDisplays() const
{
	return &displays;
}

inline const std::list<Keyboard*>* DeviceManager::getKeyboards() const
{
	return &keyboards;
}

inline const std::list<Mouse*>* DeviceManager::getMice() const
{
	return &mice;
}

inline const std::list<Gamepad*>* DeviceManager::getGamepads() const
{
	return &gamepads;
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_DEVICE_MANAGER_HPP

