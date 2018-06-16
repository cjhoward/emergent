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

#ifndef EMERGENT_WINDOW_SDL_WINDOW_HPP
#define EMERGENT_WINDOW_SDL_WINDOW_HPP

#include <emergent/window/window.hpp>
#include <SDL2/SDL.h>

namespace Emergent
{

class SDLWindowManager;

/**
 * A window created by an SDL window manager.
 *
 * @ingroup window
 */
class SDLWindow: public Window
{
public:
	/// @copydoc Window::setTitle
	virtual void setTitle(const char* title);

	/// @copydoc Window::setPosition
	virtual void setPosition(int x, int y);

	/// @copydoc Window::setDimensions
	virtual void setDimensions(int width, int height);

	/// @copydoc Window::setInputGrab
	virtual void setInputGrab(bool grab);

	/// @copydoc Window::setResizable
	virtual void setResizable(bool resizable);

	/// @copydoc Window::setBordered
	virtual void setBordered(bool bordered);

	/// @copydoc Window::setFullscreen
	virtual void setFullscreen(bool fullscreen);

	/// @copydoc Window::setVSync
	virtual void setVSync(bool vsync);

	/// @copydoc Window::makeCurrent
	virtual void makeCurrent();

	/// @copydoc Window::swapBuffers
	virtual void swapBuffers();

private:
	friend class SDLWindowManager;

	/**
	 * Creates an SDL window.
	 *
	 * @param windowManager Pointer to the parent window manager.
	 * @param window SDL window
	 * @param context SDL OpenGL context
	 */
	SDLWindow(SDLWindowManager* windowManager, SDL_Window* window, SDL_GLContext context);

	/// Destroys an SDL window.
	virtual ~SDLWindow();

	SDLWindowManager* windowManager;
	SDL_Window* window;
	SDL_GLContext context;

	int windowedX;
	int windowedY;
	int windowedWidth;
	int windowedHeight;
	bool windowMaximized;
	bool resizable;
	bool bordered;
	bool fullscreen;
};

} // namespace Emergent

#endif // EMERGENT_WINDOW_SDL_WINDOW_HPP

