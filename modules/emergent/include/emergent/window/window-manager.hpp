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

#ifndef EMERGENT_WINDOW_WINDOW_MANAGER_HPP
#define EMERGENT_WINDOW_WINDOW_MANAGER_HPP

#include <list>

namespace Emergent
{

class OSInterface;
class Window;

/**
 * Enumerates window creation flags.
 *
 * @ingroup window
 */
namespace WindowFlag
{
	enum
	{
		/// Indicates the window should be resizable
		RESIZABLE = 1,

		/// Indicates the window should be borderless
		BORDERLESS = 2,

		/// Indicates the window should start minimized
		MINIMIZED = 4,

		/// Indicates the window should start maximized
		MAXIMIZED = 8
	};
}

/**
 * Abstract base class for window managers. Provides window management functions and access to an input manager.
 *
 * @ingroup window
 */
class WindowManager
{
public:
	/**
	 * Creates a window.
	 *
	 * @param title UTF-8 encoded title string.
	 * @param x X-coordinate of the window position, when in windowed mode.
	 * @param y Y-coordinate of the window position, when in windowed mode.
	 * @param width Width of the window, when in windowed mode.
	 * @param height Height of the window, when in windowed mode.
	 * @param flags Window creation flags.
	 * @return Pointer to the created window, or nullptr if the window creation failed.
	 */
	Window* createWindow(const char* title, int x, int y, int width, int height, unsigned int flags);

	/**
	 * Destroys a window.
	 *
	 * @param window Window to destroy.
	 */
	void destroyWindow(Window* window);

	/// Returns the associated OS interface.
	const OSInterface* getOSInterface() const;

	/// @copydoc WindowManager::getOSInterface() const
	OSInterface* getOSInterface();

	/// Returns a list of the registered windows
	const std::list<Window*>* getWindows() const;

private:
	friend class OSInterface;
	friend class Window;
	
	/**
	 * Creates a window manager.
	 *
	 * @param osInterface OS interface through which windows will be managed.
	 */
	WindowManager(OSInterface* osInterface);

	/**
	 * Destroys a window manager.
	 */
	~WindowManager();

	/**
	 * Registers a window with this window manager.
	 *
	 * @param window Window to register.
	 */
	void registerWindow(Window* window);

	/**
	 * Unregisters a window from this window manager.
	 *
	 * @param window Window to unregister.
	 */
	void unregisterWindow(Window* window);

	/**
	 * Unregisters all windows.
	 */
	void unregisterWindows();

	OSInterface* osInterface;
	std::list<Window*> windows;
};

inline const OSInterface* WindowManager::getOSInterface() const
{
	return osInterface;
}

inline OSInterface* WindowManager::getOSInterface()
{
	return osInterface;
}

inline const std::list<Window*>* WindowManager::getWindows() const
{
	return &windows;
}

} // namespace Emergent

#endif // EMERGENT_WINDOW_WINDOW_MANAGER_HPP

