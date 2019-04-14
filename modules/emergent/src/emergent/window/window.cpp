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

#include <emergent/window/window.hpp>
#include <emergent/window/window-manager.hpp>

namespace Emergent
{

Window::Window(WindowManager* windowManager, unsigned int flags, void* data):
	windowManager(windowManager),
	graphicsContext(nullptr),
	data(data)
{
	resizable = (flags & WindowFlag::RESIZABLE);
	bordered = !(flags & WindowFlag::BORDERLESS);
}

Window::~Window()
{
	//delete graphicsContext;
}

void Window::setTitle(const char* title)
{
	windowManager->getOSInterface()->setWindowTitle(this, title);
}

void Window::setPosition(int x, int y)
{
	windowManager->getOSInterface()->setWindowPosition(this, x, y);
}

void Window::setDimensions(int width, int height)
{
	windowManager->getOSInterface()->setWindowDimensions(this, width, height);
}

void Window::setResizable(bool resizable)
{
	windowManager->getOSInterface()->setWindowResizable(this, resizable);
}

void Window::setBordered(bool bordered)
{
	windowManager->getOSInterface()->setWindowBordered(this, bordered);
}

void Window::setVSync(bool vsync)
{
	windowManager->getOSInterface()->setWindowVSync(this, vsync);
}

void Window::setInputGrabbed(bool grab)
{
	windowManager->getOSInterface()->setWindowInputGrabbed(this, grab);
}

void Window::makeCurrent()
{
	windowManager->getOSInterface()->makeWindowCurrent(this);
}

void Window::swapBuffers()
{
	windowManager->getOSInterface()->swapWindowBuffers(this);
}

} // namespace Emergent

