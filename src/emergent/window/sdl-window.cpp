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

namespace Emergent
{

SDLWindow::SDLWindow(SDLWindowManager* windowManager, SDL_Window* window, SDL_GLContext context):
	windowManager(windowManager),
	window(window),
	context(context)
{}

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
	SDL_SetWindowSize(window, width, height);
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

void SDLWindow::setFullscreen(bool fullscreen)
{
	SDL_SetWindowFullscreen(window, (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0);
}

void SDLWindow::makeCurrent()
{
	SDL_GL_MakeCurrent(window, context);
}

void SDLWindow::swapBuffers()
{
	SDL_GL_SwapWindow(window);
}

} // namespace Emergent

