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

#ifndef EMERGENT_INPUT_INPUT_DEVICE_HPP
#define EMERGENT_INPUT_INPUT_DEVICE_HPP

#include <string>

namespace Emergent
{

class DeviceManager;

/**
 * Abstract base class for input devices such as keyboards, mice, and gamepads.
 *
 * @ingroup input
 */
class InputDevice
{
public:
	/// Enumerates the possible types of input devices.
	enum class Type
	{
		KEYBOARD,
		MOUSE,
		GAMEPAD
	};
	
	/**
	 * Creates an input device.
	 *
	 * @param deviceManager The parent device manager.
	 * @param name Specifies the device name
	 */
	InputDevice(DeviceManager* deviceManager, const std::string& name);

	/// Destroys an input device.
	virtual ~InputDevice();

	/// Returns the parent device manager.
	const DeviceManager* getDeviceManager() const;

	/// @copydoc getDeviceManager() const
	DeviceManager* getDeviceManager();

	/// Returns the name of the device.
	const std::string& getName() const;

	/// Returns the enumerated device type.
	virtual InputDevice::Type getType() const = 0;
	
	/// Flags the device as disconnected.
	void setDisconnected(bool disconnected);

	/// Returns whether the device is disconnected.
	bool isDisconnected() const;
	
private:
	DeviceManager* deviceManager;
	std::string name;
	bool disconnected;
};

inline const DeviceManager* InputDevice::getDeviceManager() const
{
	return deviceManager;
}

inline DeviceManager* InputDevice::getDeviceManager()
{
	return deviceManager;
}

inline const std::string& InputDevice::getName() const
{
	return name;
}

inline bool InputDevice::isDisconnected() const
{
	return disconnected;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_INPUT_DEVICE_HPP

