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
		close(EXIT_FAILURE);
		return;
	}

	// Center window
	const Display* display = windowManager->getDisplay(0);
	int w = std::get<0>(display->getDimensions()) * (2.0f / 3.0f);
	int h = std::get<1>(display->getDimensions()) * (2.0f / 3.0f);
	int x = std::get<0>(display->getPosition()) + std::get<0>(display->getDimensions()) / 2 - w / 2;
	int y = std::get<1>(display->getPosition()) + std::get<1>(display->getDimensions()) / 2 - h / 2;
	unsigned int flags = WindowFlag::RESIZABLE;
	fullscreen = false;

	window = windowManager->createWindow("Emergent", x, y, w, h, fullscreen, flags);
	if (!window)
	{
		close(EXIT_FAILURE);
		return;
	}

	// Enable v-sync
	window->setVSync(true);

	// Set default frame rate
	frameTimer.setTimestep(1.0 / 10.0);
	frameTimer.setMaxFrameDuration(0.25);

	inputManager = windowManager->getInputManager();
	Keyboard* keyboard = (*inputManager->getKeyboards()).front();
	Mouse* mouse = (*inputManager->getMice()).front();

	inputManager->addApplicationObserver(this);
	window->addWindowObserver(this);
	keyboard->addKeyObserver(this);
	mouse->addMouseMotionObserver(this);
	mouse->addMouseButtonObserver(this);
	mouse->addMouseWheelObserver(this);

	closeControl.bindKey(keyboard, Scancode::ESCAPE);
	closeControl.setActivatedCallback(std::bind(&ExampleApplication::close, this, EXIT_SUCCESS));

	fullscreenControl.bindKey(keyboard, Scancode::F11);
	fullscreenControl.setActivatedCallback(std::bind(&ExampleApplication::toggleFullscreen, this));

	controlProfile.registerControl("close", &closeControl);
	controlProfile.registerControl("fullscreen", &fullscreenControl);
}

ExampleApplication::~ExampleApplication()
{
	if (window)
	{
		windowManager->destroyWindow(window);
	}

	WindowManager::deallocate();
}

int ExampleApplication::execute()
{
	// If initialization failed
	if (closed)
	{
		// Close application
		return status;
	}

	setup();

	double t = 0.0;
	frameTimer.reset();
	while (!closed)
	{
		// Input
		controlProfile.update();
		inputManager->update();
		if (closed)
		{
			return status;
		}

		// Logic
		for (std::size_t step = 0; step < frameTimer.getSteps(); ++step)
		{
			stepInterpolator.update();

			update(t, frameTimer.getTimestep());

			t += frameTimer.getTimestep();
		}

		// Interpolate between previous step and current step
		stepInterpolator.interpolate(frameTimer.getSubsteps());

		// Draw
		draw();
		window->swapBuffers();

		frameTimer.nextFrame();
	}

	exit();

	return status;
}

void ExampleApplication::close(int status)
{
	closed = true;
	this->status = status;
}

void ExampleApplication::setTitle(const char* title)
{
	std::string fullTitle = std::string(title) + std::string(" - Emergent");
	window->setTitle(fullTitle.c_str());
}

void ExampleApplication::size(int width, int height)
{
	const Display* display = windowManager->getDisplay(0);
	int x = std::get<0>(display->getPosition()) + std::get<0>(display->getDimensions()) / 2 - width / 2;
	int y = std::get<1>(display->getPosition()) + std::get<1>(display->getDimensions()) / 2 - height / 2;

	window->setDimensions(width, height);
	window->setPosition(x, y);
}

void ExampleApplication::toggleFullscreen()
{
	fullscreen = !fullscreen;
	window->setFullscreen(fullscreen);
}

void ExampleApplication::setTimestep(double timestep)
{
	frameTimer.setTimestep(timestep);
}

void ExampleApplication::setup()
{}

void ExampleApplication::update(float t, float dt)
{}

void ExampleApplication::draw()
{}

void ExampleApplication::exit()
{}

void ExampleApplication::applicationClosed()
{
	closed = true;
}

void ExampleApplication::windowClosed()
{
	closed = true;
}

void ExampleApplication::windowResized(int width, int height)
{}

void ExampleApplication::keyPressed(Scancode scancode)
{}

void ExampleApplication::keyReleased(Scancode scancode)
{}

void ExampleApplication::mouseMoved(int x, int y)
{}

void ExampleApplication::mouseButtonPressed(int button, int x, int y)
{}

void ExampleApplication::mouseButtonReleased(int button, int x, int y)
{}

void ExampleApplication::mouseWheelScrolled(int x, int y)
{}

