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

#ifndef EMERGENT_WINDOW_WINDOW_HPP
#define EMERGENT_WINDOW_WINDOW_HPP

namespace Emergent
{

/**
 * Abstract base class for windows.
 *
 * @ingroup window
 */
class Window
{
public:
	/// Creates a window.
	Window();

	/// Destroys a window.
	virtual ~Window();

	/**
	 * Sets the window title.
	 *
	 * @param title UTF-8 encoded title string.
	 */
	virtual void setTitle(const char* title) = 0;

	/**
	 * Sets the window position.
	 *
	 * @param x X-coordinate of the upper-left corner of the window.
	 * @param y Y-coordinate of the upper-left corner of the window.
	 */
	virtual void setPosition(int x, int y) = 0;

	/**
	 * Sets the window dimensions.
	 *
	 * @param width Width of the window, in pixels.
	 * @param height Height of the window, in pixels.
	 */
	virtual void setDimensions(int width, int height) = 0;

	/**
	 * Enables or disables input grabbing, where the mouse is confined to the window.
	 *
	 * @param grab Whether to grab input.
	 */
	virtual void setInputGrab(bool grab) = 0;

	/**
	 * Enables or disables manual resizing of the window.
	 *
	 * @param resizable Whether the window will be resizable.
	 */
	virtual void setResizable(bool resizable) = 0;

	/**
	 * Adds or removes the border from the window.
	 *
	 * @param bordered Whether the window is to be bordered.
	 */
	virtual void setBordered(bool bordered) = 0;

	/**
	 * Enables or disables fullscreen mode.
	 *
	 * @param fullscreen Whether to enable fullscreen mode.
	 */
	virtual void setFullscreen(bool fullscreen) = 0;

	/**
	 * Enables or disables v-sync.
	 *
	 * @param vsync Whether to enable v-sync.
	 */
	virtual void setVSync(bool vsync) = 0;

	/**
	 * Activates the window's OpenGL context.
	 */
	virtual void makeCurrent() = 0;

	/**
	 * Swaps the front and back buffers, effectively updating the window.
	 */
	virtual void swapBuffers() = 0;

	/**
	 * Closes the window.
	 */
	virtual void close() = 0;
};

} // namespace Emergent

#endif // EMERGENT_WINDOW_WINDOW_HPP

