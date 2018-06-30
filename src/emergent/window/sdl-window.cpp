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

#include <emergent/window/sdl-window.hpp>
#include <emergent/window/sdl-window-manager.hpp>
#include <iostream>

namespace Emergent
{

SDLWindow::SDLWindow(SDLWindowManager* windowManager, SDL_Window* window, SDL_GLContext context):
	windowManager(windowManager),
	window(window),
	context(context)
{
	Uint32 flags = SDL_GetWindowFlags(window);

	fullscreen = false;
	resizable = false;
	bordered = true;

	if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP)
	{
		windowedX = SDL_WINDOWPOS_CENTERED;
		windowedY = SDL_WINDOWPOS_CENTERED;
		fullscreen = true;
	}
	if (flags & SDL_WINDOW_RESIZABLE)
	{
		resizable = true;
	}
	if (flags & SDL_WINDOW_BORDERLESS)
	{
		bordered = false;
	}
}

SDLWindow::~SDLWindow()
{}

void SDLWindow::setTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

void SDLWindow::setPosition(int x, int y)
{
	SDL_SetWindowPosition(window, x, y);
}

void SDLWindow::setDimensions(int width, int height)
{
	if (!fullscreen)
	{
		SDL_SetWindowSize(window, width, height);
	}
	else
	{
		windowedWidth = width;
		windowedHeight = height;
	}
}

void SDLWindow::setInputGrab(bool grab)
{
	if (grab)
	{
		if (windowManager->getGrabbedWindow() != nullptr)
		{
			windowManager->getGrabbedWindow()->setInputGrab(false);
		}

		SDL_SetWindowGrab(window, SDL_TRUE);
		windowManager->setGrabbedWindow(this);
	}
	else
	{
		if (windowManager->getGrabbedWindow() == this)
		{
			windowManager->setGrabbedWindow(nullptr);
			SDL_SetWindowGrab(window, SDL_FALSE);
		}
	}
}

void SDLWindow::setResizable(bool resizable)
{
	this->resizable = resizable;
	if (!fullscreen)
	{
		SDL_SetWindowResizable(window, (resizable) ? SDL_TRUE : SDL_FALSE);
	}
}

void SDLWindow::setBordered(bool bordered)
{
	this->bordered = bordered;
	if (!fullscreen)
	{
		SDL_SetWindowBordered(window, (bordered) ? SDL_TRUE : SDL_FALSE);
	}
}

void SDLWindow::setFullscreen(bool fullscreen)
{
	this->fullscreen = fullscreen;

	if (!fullscreen)
	{
		SDL_HideWindow(window);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
		SDL_SetWindowSize(window, windowedWidth, windowedHeight);
		SDL_SetWindowResizable(window, (resizable) ? SDL_TRUE : SDL_FALSE);
		SDL_SetWindowBordered(window, (bordered) ? SDL_TRUE : SDL_FALSE);
		SDL_SetWindowPosition(window, windowedX, windowedY);
		SDL_RaiseWindow(window);

	}
	else
	{
		// Store windowed mode position and size
		SDL_GetWindowPosition(window, &windowedX, &windowedY);
		SDL_GetWindowSize(window, &windowedWidth, &windowedHeight);

		int display = SDL_GetWindowDisplayIndex(window);
		SDL_Rect bounds;
		SDL_GetDisplayBounds(display, &bounds);
		SDL_DisplayMode mode;
		SDL_GetCurrentDisplayMode(display, &mode);

		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP;

		SDL_HideWindow(window);
		SDL_SetWindowBordered(window, SDL_FALSE);
		SDL_SetWindowResizable(window, SDL_FALSE);
		SDL_SetWindowPosition(window, bounds.x, bounds.y);
		SDL_SetWindowSize(window, mode.w, mode.h);
		SDL_SetWindowFullscreen(window, flags);
		SDL_ShowWindow(window);
	}
}

void SDLWindow::setVSync(bool vsync)
{
	if (vsync)
	{
		if (SDL_GL_SetSwapInterval(-1) != 0)
		{
			SDL_GL_SetSwapInterval(1);
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}
}

void SDLWindow::makeCurrent()
{
	SDL_GL_MakeCurrent(window, context);
}

void SDLWindow::swapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void SDLWindow::close()
{
	SDL_DestroyWindow(window);
}

} // namespace Emergent

