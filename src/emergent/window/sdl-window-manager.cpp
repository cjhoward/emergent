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

#include <emergent/window/sdl-window-manager.hpp>
#include <emergent/window/sdl-window.hpp>
#include <emergent/window/display.hpp>
#include <emergent/input/sdl-input-manager.hpp>
#include <GL/gl3w.h>
#include <iostream>

namespace Emergent
{

SDLWindowManager::SDLWindowManager():
	grabbedWindow(nullptr)
{
	std::cout << std::string("Initializing SDL... ");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cout << std::string("failed: \"") << SDL_GetError() << std::string("\"") << std::endl;
		return;
	}
	
	// Register displays
	int displayCount = SDL_GetNumVideoDisplays();
	for (int i = 0; i < displayCount; ++i)
	{
		Display* display = new Display();

		// Determine display name
		const char* name = SDL_GetDisplayName(i);
		display->setName(name);

		// Determine display DPI
		float dpi = -1.0f;
		SDL_GetDisplayDPI(i, &dpi, nullptr, nullptr);
		display->setDPI(dpi);

		// Determine display bounds
		SDL_Rect bounds;
		SDL_GetDisplayBounds(i, &bounds);
		display->setPosition(bounds.x, bounds.y);
		display->setDimensions(bounds.w, bounds.h);

		// Get current display mode
		SDL_DisplayMode currentMode;
		SDL_GetCurrentDisplayMode(i, &currentMode);

		// Get desktop display mode
		SDL_DisplayMode desktopMode;
		SDL_GetDesktopDisplayMode(i, &desktopMode);

		// For each display mode
		int displayModeCount = SDL_GetNumDisplayModes(i);
		for (int j = 0; j < displayModeCount; ++j)
		{
    		SDL_DisplayMode mode = {SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0};
			SDL_GetDisplayMode(i, j, &mode);

			// Add display mode
			display->addDisplayMode(mode.w, mode.h, mode.refresh_rate);

			// Check if this display mode is the current display mode
			if (mode.format == currentMode.format &&
				mode.w == currentMode.w &&
				mode.h == currentMode.h &&
				mode.refresh_rate == currentMode.refresh_rate)
			{
				display->setCurrentDisplayModeIndex(j);
			}

			// Check if this display mode is the default display mode
			if (mode.format == desktopMode.format &&
				mode.w == desktopMode.w &&
				mode.h == desktopMode.h &&
				mode.refresh_rate == desktopMode.refresh_rate)
			{
				display->setDefaultDisplayModeIndex(j);
			}
		}

		registerDisplay(display);
	}

	// Allocate input manager
	inputManager = new SDLInputManager(this);
}

SDLWindowManager::~SDLWindowManager()
{
	delete inputManager;

	for (Display* display: displays)
	{
		delete display;
	}

	SDL_Quit();
}


Window* SDLWindowManager::createWindow(const char* title, int x, int y, int width, int height, bool fullscreen, unsigned int flags)
{
	// Determine window flags
	Uint32 sdlFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
	if (fullscreen)
	{
		sdlFlags |= SDL_WINDOW_FULLSCREEN;
	}
	if (flags & WindowFlag::RESIZABLE)
	{
		sdlFlags |= SDL_WINDOW_RESIZABLE;
	}
	if (flags & WindowFlag::MINIMIZED)
	{
		sdlFlags |= SDL_WINDOW_MINIMIZED;
	}
	if (flags & WindowFlag::MAXIMIZED)
	{
		sdlFlags |= SDL_WINDOW_MAXIMIZED;
	}

	// Create SDL window
	SDL_Window* sdlWindow = SDL_CreateWindow(title, x, y, width, height, sdlFlags);
	if (!sdlWindow)
	{
		return nullptr;
	}

	// Select OpenGL version
	int OPENGL_VERSION_MAJOR = 3;
	int OPENGL_VERSION_MINOR = 3;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_VERSION_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_VERSION_MINOR);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	// Set OpenGL buffer attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);


	// Create OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(sdlWindow);
	if (!context)
	{
		SDL_DestroyWindow(sdlWindow);
		return nullptr;
	}

	// Disable v-sync
	SDL_GL_SetSwapInterval(0);

	// Initialize GL3W
	std::cout << std::string("Initializing GL3W... ");
	if (gl3wInit())
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(sdlWindow);
		return nullptr;
	}
	
	// Check if OpenGL version is supported
	if (!gl3wIsSupported(OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR))
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(sdlWindow);
		return nullptr;
	}

	SDLWindow* window = new SDLWindow(this, sdlWindow, context);
	registerWindow(window);

	// Add window to window map
	Uint32 windowID = SDL_GetWindowID(sdlWindow);
	windowMap[windowID] = window;

	return window;
}

void SDLWindowManager::destroyWindow(Window* window)
{
	SDLWindow* sdlWindow = static_cast<SDLWindow*>(window);

	// Remove from window map
	Uint32 windowID = SDL_GetWindowID(sdlWindow->window);
	auto it = windowMap.find(windowID);
	if (it != windowMap.end())
	{
		windowMap.erase(it);
	}
	
	// Unregister
	unregisterWindow(window);

	// Delete
	SDL_GL_DeleteContext(sdlWindow->context);
	SDL_DestroyWindow(sdlWindow->window);
	delete sdlWindow;
}

void SDLWindowManager::setGrabbedWindow(SDLWindow* window)
{
	this->grabbedWindow = window;
}

SDLWindow* SDLWindowManager::getGrabbedWindow()
{
	return grabbedWindow;
}

} // namespace Emergent

