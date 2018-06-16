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
	int w = std::get<0>(display->getDimensions()) * (2.0f / 3.0f);
	int h = std::get<1>(display->getDimensions()) * (2.0f / 3.0f);
	int x = std::get<0>(display->getPosition()) + std::get<0>(display->getDimensions()) / 2 - w / 2;
	int y = std::get<1>(display->getPosition()) + std::get<1>(display->getDimensions()) / 2 - h / 2;
	unsigned int flags = WindowFlag::RESIZABLE;
	fullscreen = false;

	window = windowManager->createWindow("Emergent", x, y, w, h, fullscreen, flags);
	if (!window)
	{
		closed = true;
		return;
	}

	// Enable v-sync
	window->setVSync(true);

	// Set default frame rate
	setFrameRate(1.0f);

	InputManager* inputManager = windowManager->getInputManager();
	Keyboard* keyboard = (*inputManager->getKeyboards()).front();
	Mouse* mouse = (*inputManager->getMice()).front();

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
	if (!closed)
	{
		setup();
	}

	t = 0.0f;
	double accumulator = 0.0;
	double maxFrameTime = 0.25;
	Timer frameTimer;

	frameTimer.start();
	while (!closed)
	{
		// Calculate frame time (in milliseconds) then reset frame timer
		double frameTime = static_cast<double>(frameTimer.microseconds().count()) / 1000.0;
		t += static_cast<float>(frameTime / 1000.0);
		frameTimer.reset();

		// Add frame time to accumulator
		accumulator += std::min<double>(maxFrameTime, frameTime / 1000.0);

		// Input
		controlProfile.update();
		windowManager->getInputManager()->update();
		if (windowManager->getInputManager()->wasClosed())
		{
			close(EXIT_SUCCESS);
		}

		// Logic
		while (accumulator >= dt)
		{
			update(dt);
			accumulator -= dt;
		}

		// Draw
		draw();
		window->swapBuffers();
	}

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

void ExampleApplication::setFrameRate(float framesPerSecond)
{
	this->framesPerSecond = framesPerSecond;
	dt = 1.0f / framesPerSecond;
}

void ExampleApplication::toggleFullscreen()
{
	fullscreen = !fullscreen;
	window->setFullscreen(fullscreen);
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

void ExampleApplication::setup()
{}

void ExampleApplication::update(float dt)
{}

void ExampleApplication::draw()
{}

