
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

#include <emergent/utility/application.hpp>
#include <emergent/window/sdl-window-manager.hpp>
#include <emergent/input/input-manager.hpp>
#include <stdexcept>
#include <chrono>

namespace Emergent
{

Application::Application():
	windowManager(nullptr),
	inputManager(nullptr),
	closed(false),
	status(EXIT_SUCCESS)
{
	// Allocate window manager
	windowManager = new SDLWindowManager();
	if (!windowManager)
	{
		throw std::runtime_error("Application::Application(): Failed to initialize SDL window manager.");
	}

	// Setup step scheduling
	stepScheduler.setMaxFrameDuration(0.25);
	stepScheduler.setStepFrequency(60.0);
	
	// Setup performance sampling
	performanceSampler.setSampleSize(1);

	// Setup input event handling
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
}

Application::~Application()
{
	// Free window manager
	delete windowManager;
}

int Application::execute()
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

		// Render the frame
		render();

		// Determine duration of the frame
		t1 = std::chrono::high_resolution_clock::now();
		double frameDuration = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count()) / 1000000.0;

		// Reset frame timer
		t0 = t1;

		// Use frame duration to sample performance
		performanceSampler.sample(frameDuration);

		// Schedule steps for the next frame according to the duration of this frame
		stepScheduler.schedule(frameDuration);
	}

	exit();

	return status;
}

void Application::close(int status)
{
	closed = true;
	this->status = status;
}

void Application::setup()
{}

void Application::input()
{}

void Application::update(float t, float dt)
{}

void Application::render()
{}

void Application::exit()
{}

void Application::handleEvent(const ApplicationClosedEvent& event)
{
	closed = true;
}

void Application::handleEvent(const WindowClosedEvent& event)
{
	closed = true;
}

void Application::handleEvent(const WindowResizedEvent& event)
{}

void Application::handleEvent(const KeyPressedEvent& event)
{}

void Application::handleEvent(const KeyReleasedEvent& event)
{}

void Application::handleEvent(const MouseMovedEvent& event)
{}

void Application::handleEvent(const MouseButtonPressedEvent& event)
{}

void Application::handleEvent(const MouseButtonReleasedEvent& event)
{}

void Application::handleEvent(const MouseWheelScrolledEvent& event)
{}

} // namespace Emergent

