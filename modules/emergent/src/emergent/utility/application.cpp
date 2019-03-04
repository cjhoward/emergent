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

#include <emergent/configuration.hpp>
#include <emergent/input/input-mapper.hpp>
#include <emergent/utility/application.hpp>
#include <stdexcept>
#include <chrono>

// Include OS inteface header
#if defined(EMERGENT_SDL)
	#include <emergent/utility/sdl-interface.hpp>
#else
	#error "No OS interface defined."
#endif

namespace Emergent
{

Application::Application():
	osInterface(nullptr),
	deviceManager(nullptr),
	windowManager(nullptr),
	inputMapper(nullptr),
	closed(false),
	status(EXIT_SUCCESS)
{
	// Initialize OS interface
	try
	{
		#if defined(EMERGENT_SDL)
			osInterface = new SDLInterface(&eventDispatcher);
		#endif
	}
	catch (const std::exception& e)
	{
		std::string error = std::string("Application::Application(): Failed to initialize OS interface: \"") + std::string(e.what()) + std::string("\"");
		throw std::runtime_error(error.c_str());
	}

	// Get the device manager
	deviceManager = osInterface->getDeviceManager();

	// Get the window manager
	windowManager = osInterface->getWindowManager();

	// Create the input mapper
	inputMapper = new InputMapper(&eventDispatcher);

	// Setup step scheduling
	stepScheduler.setMaxFrameDuration(0.25);
	stepScheduler.setStepFrequency(60.0);
	
	// Setup performance sampling
	performanceSampler.setSampleSize(1);

	// Setup event handling
	eventDispatcher.subscribe<ApplicationClosedEvent>(this);
	eventDispatcher.subscribe<WindowClosedEvent>(this);
	eventDispatcher.subscribe<WindowResizedEvent>(this);
	eventDispatcher.subscribe<KeyPressedEvent>(this);
	eventDispatcher.subscribe<KeyReleasedEvent>(this);
	eventDispatcher.subscribe<MouseMovedEvent>(this);
	eventDispatcher.subscribe<MouseButtonPressedEvent>(this);
	eventDispatcher.subscribe<MouseButtonReleasedEvent>(this);
	eventDispatcher.subscribe<MouseWheelScrolledEvent>(this);
}

Application::~Application()
{
	// Delete the input mapper
	delete inputMapper;

	// Shutdown OS interface
	delete osInterface;
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

	// Initialize the step timer
	double elapsedTime = 0.0;

	// Start frame timer
	std::chrono::high_resolution_clock::time_point t0;
	std::chrono::high_resolution_clock::time_point t1;
	t0 = std::chrono::high_resolution_clock::now();

	// Enter main loop
	while (!closed)
	{
		// Route OS events through the event dispatcher
		osInterface->routeEvents();

		// Perform scheduled update steps
		for (std::size_t step = 0; step < stepScheduler.getScheduledSteps(); ++step)
		{
			// Reset step interpolation
			stepInterpolator.reset();

			// Dispatch due events
			eventDispatcher.update(elapsedTime);
			
			// Perform update
			update(elapsedTime, stepScheduler.getStepPeriod());

			// Handle input
			input();

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

