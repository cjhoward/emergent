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

#ifndef EMERGENT_WINDOW_WINDOW_HPP
#define EMERGENT_WINDOW_WINDOW_HPP

#include <emergent/utility/os-interface.hpp>

namespace Emergent
{

class WindowManager;
class GraphicsContext;

/**
 * Represents a window.
 *
 * @ingroup window
 */
class Window
{
public:
	/**
	 * Sets the window title.
	 *
	 * @param title UTF-8 encoded title string.
	 */
	void setTitle(const char* title);

	/**
	 * Sets the window position.
	 *
	 * @param x X-coordinate of the upper-left corner of the window.
	 * @param y Y-coordinate of the upper-left corner of the window.
	 */
	void setPosition(int x, int y);

	/**
	 * Sets the window dimensions.
	 *
	 * @param width Width of the window, in pixels.
	 * @param height Height of the window, in pixels.
	 */
	void setDimensions(int width, int height);

	/**
	 * Enables or disables manual resizing of the window.
	 *
	 * @param resizable Whether the window will be resizable.
	 */
	void setResizable(bool resizable);

	/**
	 * Adds or removes the border from the window.
	 *
	 * @param bordered Whether the window is to be bordered.
	 */
	void setBordered(bool bordered);

	/**
	 * Enables or disables fullscreen mode.
	 *
	 * @param fullscreen Whether to enable fullscreen mode.
	 */
	void setFullscreen(bool fullscreen);

	/**
	 * Enables or disables v-sync.
	 *
	 * @param vsync Whether to enable v-sync.
	 */
	void setVSync(bool vsync);

	/**
	 * Enables or disables input grabbing, where the mouse is confined to the window.
	 *
	 * @param grabbed Whether to grab input.
	 */
	void setInputGrabbed(bool grabbed);

	/**
	 * Activates the window's OpenGL context.
	 */
	void makeCurrent();

	/**
	 * Swaps the front and back buffers, effectively updating the window.
	 */
	void swapBuffers();

	/// Returns the parent window manager.
	const WindowManager* getWindowManager() const;

	/// @copydoc Window::getWindowManager() const
	WindowManager* getWindowManager();

	/// Returns the graphics context associated with this window.
	const GraphicsContext* getGraphicsContext() const;

	/// @copydoc Window::getGraphicsContext() const
	GraphicsContext* getGraphicsContext();

	/// Returns true if the window is resizable
	bool isResizable() const;

	/// Returns true if the window has a border
	bool hasBorder() const;

	/// Returns a pointer to the OS interface-specific window data.
	const void* getWindowData() const;

	/// @copydoc Window::getWindowData() const
	void* getWindowData();
	
private:
	friend class WindowManager;
	friend class OSInterface;

	/**
	 * Creates a window.
	 *
	 * @param windowManager Window manager which owns this window.
	 * @param flags Window creation flags.
	 * @param data OS interface-specific window data for this window.
	 */
	Window(WindowManager* windowManager, unsigned int flags, void* data);

	/// Destroys a window.
	~Window();

	WindowManager* windowManager;
	GraphicsContext* graphicsContext;
	bool resizable;
	bool bordered;
	void* data;
};

inline const WindowManager* Window::getWindowManager() const
{
	return windowManager;
}

inline WindowManager* Window::getWindowManager()
{
	return windowManager;
}

inline const GraphicsContext* Window::getGraphicsContext() const
{
	return graphicsContext;
}

inline GraphicsContext* Window::getGraphicsContext()
{
	return graphicsContext;
}

inline bool Window::isResizable() const
{
	return resizable;
}

inline bool Window::hasBorder() const
{
	return bordered;
}

inline const void* Window::getWindowData() const
{
	return data;
}

inline void* Window::getWindowData()
{
	return data;
}

} // namespace Emergent

#endif // EMERGENT_WINDOW_WINDOW_HPP

