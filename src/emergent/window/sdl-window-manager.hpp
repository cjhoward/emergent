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

#ifndef EMERGENT_WINDOW_SDL_WINDOW_MANAGER_HPP
#define EMERGENT_WINDOW_SDL_WINDOW_MANAGER_HPP

#include <emergent/window/window-manager.hpp>
#include <SDL2/SDL.h>
#include <map>

namespace Emergent
{

class SDLWindow;

/**
 * An SDL window manager.
 *
 * @ingroup window
 */
class SDLWindowManager: public WindowManager
{
public:
	/// @copydoc WindowManager::createWindow
	virtual Window* createWindow(const char* title, int x, int y, int width, int height, bool fullscreen, unsigned int flags);

	/// @copydoc WindowManager::destroyWindow
	virtual void destroyWindow(Window* window);

private:
	friend class WindowManager;
	friend class SDLWindow;
	friend class SDLInputManager;

	/**
	 * Creates an SDL window manager, thereby initializing SDL.
	 */
	SDLWindowManager();

	/**
	 * Destroys an SDL window manager, thereby quitting SDL.
	 */
	virtual ~SDLWindowManager();

	/// Sets the window with grabbed input.
	void setGrabbedWindow(SDLWindow* window);

	/// Returns the window with grabbed input.
	SDLWindow* getGrabbedWindow();

	std::map<Uint32, SDLWindow*> windowMap;
	SDLWindow* grabbedWindow;
};

} // namespace Emergent

#endif // EMERGENT_WINDOW_SDL_WINDOW_MANAGER_HPP

