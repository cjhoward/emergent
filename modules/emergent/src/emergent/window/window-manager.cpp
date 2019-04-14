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

#include <emergent/window/window-manager.hpp>
#include <emergent/window/window.hpp>
#include <emergent/utility/os-interface.hpp>

namespace Emergent
{

WindowManager::WindowManager(OSInterface* osInterface):
	osInterface(osInterface)
{}

WindowManager::~WindowManager()
{
	osInterface = nullptr;
}

Window* WindowManager::createWindow(const char* title, int x, int y, int width, int height, unsigned int flags)
{
	void* data = osInterface->openWindow(title, x, y, width, height, flags);
	if (data == nullptr)
	{
		return nullptr;
	}

	Window* window = new Window(this, flags, data);
	registerWindow(window);

	return window;
}

void WindowManager::destroyWindow(Window* window)
{
	osInterface->closeWindow(window);
	unregisterWindow(window);
	delete window;
}

void WindowManager::registerWindow(Window* window)
{
	windows.push_back(window);
}

void WindowManager::unregisterWindow(Window* window)
{
	windows.remove(window);
}

void WindowManager::unregisterWindows()
{
	windows.clear();
}

} // namespace Emergent
