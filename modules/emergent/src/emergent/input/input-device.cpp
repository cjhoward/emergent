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

#include <emergent/input/input-device.hpp>

namespace Emergent
{

InputDevice::InputDevice(DeviceManager* deviceManager, const std::string& name):
	deviceManager(deviceManager),
	name(name),
	disconnected(true)
{}

InputDevice::~InputDevice()
{}

void InputDevice::setDisconnected(bool disconnected)
{
	this->disconnected = disconnected;
}

} // namespace Emergent

