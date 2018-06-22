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

#ifndef EMERGENT_WINDOW_WINDOW_MANAGER_HPP
#define EMERGENT_WINDOW_WINDOW_MANAGER_HPP

#include <vector>

namespace Emergent
{

class Application;
class Display;
class InputManager;
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
	 * @param fullscreen Whether fullscreen mode is enabled. If fullscreen mode is enabled, the dimensions of the window will be equal to the dimensions of the parent display.
	 * @param flags Window creation flags.
	 * @return Pointer to the created window, or nullptr if the window creation failed.
	 */
	virtual Window* createWindow(const char* title, int x, int y, int width, int height, bool fullscreen, unsigned int flags) = 0;

	/**
	 * Destroys a window.
	 *
	 * @param window Window to destroy.
	 */
	virtual void destroyWindow(Window* window) = 0;

	/// Returns the associated input manager.
	const InputManager* getInputManager() const;

	/// @copydoc WindowManager::getInputManager() const
	InputManager* getInputManager();

	/// Returns the number of registered displays
	std::size_t getDisplayCount() const;

	/// Returns the display at the specified index.
	const Display* getDisplay(std::size_t index) const;

protected:
	/**
	 * Registers a display with the window manager.
	 *
	 * @param display Pointer to the display to register.
	 */
	void registerDisplay(Display* display);

	/**
	 * Unregisters a display from the window manager.
	 *
	 * @param display Pointer to the display to unregister.
	 */
	void unregisterDisplay(Display* display);

	/**
	 * Unregisters all displays.
	 */
	void unregisterDisplays();

	/**
	 * Registers a window with the window manager.
	 *
	 * @param window Pointer to the window to register.
	 */
	void registerWindow(Window* window);

	/**
	 * Unregisters a window from the window manager.
	 *
	 * @param window Pointer to the window to unregister.
	 */
	void unregisterWindow(Window* window);

	/**
	 * Unregisters all windows.
	 */
	void unregisterWindows();


	InputManager* inputManager;
	std::vector<Display*> displays;
	std::vector<Window*> windows;

private:
	friend class Application;
	friend class SDLWindowManager;

	/**
	 * Creates a window manager.
	 */
	WindowManager();

	/**
	 * Destroys a window manager.
	 */
	virtual ~WindowManager();
};

inline const InputManager* WindowManager::getInputManager() const
{
	return inputManager;
}

inline InputManager* WindowManager::getInputManager()
{
	return inputManager;
}

inline std::size_t WindowManager::getDisplayCount() const
{
	return displays.size();
}

inline const Display* WindowManager::getDisplay(std::size_t index) const
{
	return displays[index];
}

} // namespace Emergent

#endif // EMERGENT_WINDOW_WINDOW_MANAGER_HPP

