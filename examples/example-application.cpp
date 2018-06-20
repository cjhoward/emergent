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
#include <chrono>

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
	stepScheduler.setMaxFrameDuration(0.25);
	stepScheduler.setStepFrequency(60.0);

	// Setup application event handling
	inputManager = windowManager->getInputManager();
	inputManager->subscribe<ApplicationClosedEvent>(this);
	inputManager->subscribe<WindowClosedEvent>(this);
	inputManager->subscribe<WindowResizedEvent>(this);
	inputManager->subscribe<KeyPressedEvent>(this);
	inputManager->subscribe<KeyReleasedEvent>(this);
	inputManager->subscribe<MouseMovedEvent>(this);
	inputManager->subscribe<MouseButtonPressedEvent>(this);
	inputManager->subscribe<MouseButtonReleasedEvent>(this);
	inputManager->subscribe<MouseWheelScrolledEvent>(this);

	Keyboard* keyboard = (*inputManager->getKeyboards()).front();
	Mouse* mouse = (*inputManager->getMice()).front();

	// Setup control profile
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

	// Ensure state0 and state1 are equal
	stepInterpolator.update();

	// Start frame timer
	double elapsedTime = 0.0;
	std::chrono::high_resolution_clock::time_point t0;
	std::chrono::high_resolution_clock::time_point t1;
	t0 = std::chrono::high_resolution_clock::now();

	// Enter main loop
	while (!closed)
	{
		// Process input
		inputManager->update();
		if (closed)
		{
			break;
		}
		input();
		controlProfile.update();

		// Perform scheduled update steps
		for (std::size_t step = 0; step < stepScheduler.getScheduledSteps(); ++step)
		{
			// Set state0 equal to state1
			stepInterpolator.update();

			// Perform update
			update(elapsedTime, stepScheduler.getStepPeriod());

			// Add step period to total elapsed time
			elapsedTime += stepScheduler.getStepPeriod();
		}

		// Interpolate between previous step and current step
		double interpolatioRatio = stepScheduler.getScheduledSubsteps();
		stepInterpolator.interpolate(interpolatioRatio);

		// Draw
		draw();
		window->swapBuffers();

		// Determine duration of the frame
		t1 = std::chrono::high_resolution_clock::now();
		double frameDuration = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count()) / 1000000.0;

		// Reset frame timer
		t0 = t1;

		// Schedule steps for the next frame
		stepScheduler.schedule(frameDuration);
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

void ExampleApplication::setUpdateRate(double frequency)
{
	stepScheduler.setStepFrequency(frequency);
}

void ExampleApplication::setup()
{}

void ExampleApplication::input()
{}

void ExampleApplication::update(float t, float dt)
{}

void ExampleApplication::draw()
{}

void ExampleApplication::exit()
{}

void ExampleApplication::handleEvent(const ApplicationClosedEvent& event)
{
	closed = true;
}

void ExampleApplication::handleEvent(const WindowClosedEvent& event)
{
	closed = true;
}

void ExampleApplication::handleEvent(const WindowResizedEvent& event)
{}

void ExampleApplication::handleEvent(const KeyPressedEvent& event)
{}

void ExampleApplication::handleEvent(const KeyReleasedEvent& event)
{}

void ExampleApplication::handleEvent(const MouseMovedEvent& event)
{}

void ExampleApplication::handleEvent(const MouseButtonPressedEvent& event)
{}

void ExampleApplication::handleEvent(const MouseButtonReleasedEvent& event)
{}

void ExampleApplication::handleEvent(const MouseWheelScrolledEvent& event)
{}

