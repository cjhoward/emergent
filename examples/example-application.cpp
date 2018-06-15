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

#include "example-application.hpp"

ExampleApplication::ExampleApplication(int argc, char* argv[]):
	closed(false),
	status(EXIT_SUCCESS)
{
	WindowManager::allocate();

	windowManager = WindowManager::instance();
	if (!windowManager)
	{
		closed = true;
		return;
	}

	// Center window
	const Display* display = windowManager->getDisplay(0);
	int w = 1280;
	int h = 720;
	int x = std::get<0>(display->getPosition()) + std::get<0>(display->getDimensions()) / 2 - w / 2;
	int y = std::get<1>(display->getPosition()) + std::get<1>(display->getDimensions()) / 2 - h / 2;
	unsigned int flags = WindowFlag::RESIZABLE;

	window = windowManager->createWindow("Emergent", x, y, w, h, false, flags);
	if (!window)
	{
		closed = true;
		return;
	}

	window->addWindowObserver(this);
}

ExampleApplication::~ExampleApplication()
{
	WindowManager::deallocate();
}

int ExampleApplication::execute()
{
	while (!closed)
	{
		window->swapBuffers();

		windowManager->getInputManager()->update();
		if (windowManager->getInputManager()->wasClosed())
		{
			closed = true;
			break;
		}
	}

	return status;
}

void ExampleApplication::close(int status)
{
	closed = true;
	this->status = status;
}

void ExampleApplication::windowClosed()
{
	closed = true;
}

void ExampleApplication::windowResized(int width, int height)
{
	glClearColor((float)width / 1920.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

