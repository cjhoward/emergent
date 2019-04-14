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

#ifndef EMERGENT_UTILITY_SDL_INTERFACE_HPP
#define EMERGENT_UTILITY_SDL_INTERFACE_HPP

#include <emergent/utility/os-interface.hpp>
#include <list>
#include <map>
#include <string>
#include <SDL.h>

namespace Emergent
{

enum class Scancode;
class Display;
class Gamepad;
class Keyboard;
class Mouse;

/**
 * Abstraction layer which interfaces with the OS via SDL.
 *
 * @ingroup utility
 */
class SDLInterface: public OSInterface
{
public:
	/**
	 * Creates an SDL interface and initializes SDL.
	 *
	 * @param eventDispatcher Event dispatcher through which OS events will be routed.
	 *
	 * @throw std::runtime_error SDL already initialized.
	 * @throw std::runtime_error Failed to initialize SDL.
	 */
	SDLInterface(EventDispatcher* eventDispatcher);
	
	/**
	 * Destroys an SDL interface and shuts down SDL.
	 */
	virtual ~SDLInterface();

	/**
	 * Routes SDL events through the event dispatcher.
	 */
	virtual void routeEvents();

	virtual void startTextInput();
	virtual void stopTextInput();
	virtual void setClipboardText(const char* text);
	virtual const char* getClipboardText() const;

private:
	struct WindowData
	{
		SDL_Window* window;
		SDL_GLContext context;
		int x;
		int y;
		int width;
		int height;
		int windowID;
	};

	/**
	 * @copydoc OSInterface::openWindow()
	 *
	 * @throw std::runtime_error Failed to initialize OpenGL.
	 * @throw std::runtime_error OpenGL version X.Y not supported.
	 */
	virtual void* openWindow(const char* title, int x, int y, int width, int height, unsigned int flags);

	virtual void closeWindow(Window* window);
	virtual void setWindowTitle(Window* window, const char* title);
	virtual void setWindowPosition(Window* window, int x, int y);
	virtual void setWindowDimensions(Window* window, int width, int height);
	virtual void setWindowResizable(Window* window, bool resizable);
	virtual void setWindowBordered(Window* window, bool bordered);
	virtual void setWindowVSync(Window* window, bool vsync);
	virtual void setWindowInputGrabbed(Window* window, bool grabbed);
	virtual void makeWindowCurrent(Window* window);
	virtual void swapWindowBuffers(Window* window);
	virtual void warpMousePosition(Window* window, int x, int y);
	virtual void setRelativeMouseMode(Mouse* mouse, bool enabled);
	virtual void setMouseVisible(Mouse* mouse, bool visible);

	static const Scancode scancodeTable[287];

	int openGLVersionMajor;
	int openGLVersionMinor;
	SDL_Event sdlEvent;
	mutable std::string clipboardText;
	Keyboard* keyboard;
	Mouse* mouse;
	std::list<Display*> allocatedDisplays;
	std::list<Gamepad*> allocatedGamepads;
	std::map<int, Gamepad*> gamepadMap;
};

} // namespace Emergent

#endif // EMERGENT_UTILITY_SDL_INTERFACE_HPP

