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

#include <emergent/utility/os-interface.hpp>
#include <emergent/utility/device-manager.hpp>
#include <emergent/window/window-manager.hpp>
#include <emergent/input/mouse.hpp>

namespace Emergent
{

OSInterface::OSInterface(EventDispatcher* eventDispatcher):
	deviceManager(nullptr),
	eventDispatcher(eventDispatcher)
{
	deviceManager = new DeviceManager(this);
	windowManager = new WindowManager(this);
}

OSInterface::~OSInterface()
{
	delete deviceManager;
	delete windowManager;
}

void OSInterface::updateMousePosition(Mouse* mouse, int x, int y)
{
	mouse->previousPosition = mouse->currentPosition;
	std::get<0>(mouse->currentPosition) = x;
	std::get<1>(mouse->currentPosition) = y;
}

} // namespace Emergent

