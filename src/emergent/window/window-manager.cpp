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

#include <emergent/window/window-manager.hpp>
#include <emergent/window/sdl-window-manager.hpp>

namespace Emergent
{

WindowManager* WindowManager::wm = nullptr;

void WindowManager::allocate()
{
	if (wm == nullptr)
	{
		wm = new SDLWindowManager();
	}
}

void WindowManager::deallocate()
{
	delete wm;
	wm = nullptr;
}

WindowManager* WindowManager::instance()
{
	return wm;
}

WindowManager::WindowManager():
	inputManager(nullptr)
{}

WindowManager::~WindowManager()
{}

void WindowManager::registerDisplay(Display* display)
{
	displays.push_back(display);
}

void WindowManager::unregisterDisplay(Display* display)
{
	for (auto it = displays.begin(); it != displays.end(); ++it)
	{
		if (display == (*it))
		{
			displays.erase(it);
			return;
		}
	}
}

void WindowManager::unregisterDisplays()
{
	displays.clear();
}

void WindowManager::registerWindow(Window* window)
{
	windows.push_back(window);
}

void WindowManager::unregisterWindow(Window* window)
{
	for (auto it = windows.begin(); it != windows.end(); ++it)
	{
		if (window == (*it))
		{
			windows.erase(it);
			return;
		}
	}
}

void WindowManager::unregisterWindows()
{
	windows.clear();
}

} // namespace Emergent
