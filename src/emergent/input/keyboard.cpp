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

#include <emergent/input/keyboard.hpp>
#include <emergent/input/observers.hpp>

namespace Emergent
{

Keyboard::Keyboard(const std::string& name):
	InputDevice(name)
{}

Keyboard::~Keyboard()
{}

void Keyboard::addKeyObserver(KeyObserver* observer)
{
	keyObservers.push_back(observer);
}

void Keyboard::removeKeyObserver(KeyObserver* observer)
{
	keyObservers.remove(observer);
}

void Keyboard::removeKeyObservers()
{
	keyObservers.clear();
}

void Keyboard::press(int scancode)
{
	for (auto observer: keyObservers)
	{
		observer->keyPressed(scancode);
	}
}

void Keyboard::release(int scancode)
{
	for (auto observer: keyObservers)
	{
		observer->keyReleased(scancode);
	}
}

} // namespace Emergent

