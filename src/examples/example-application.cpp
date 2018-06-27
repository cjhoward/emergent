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
#include <stdexcept>

ExampleApplication::ExampleApplication(int argc, char* argv[]):
	window(nullptr)
{
	// Initialize default parameters
	title = "Emergent";
	float windowSizeRatio = 2.0f / 3.0f;
	const Display* display = windowManager->getDisplay(0);
	int w = std::get<0>(display->getDimensions()) * windowSizeRatio;
	int h = std::get<1>(display->getDimensions()) * windowSizeRatio;
	int x = std::get<0>(display->getPosition()) + std::get<0>(display->getDimensions()) / 2 - w / 2;
	int y = std::get<1>(display->getPosition()) + std::get<1>(display->getDimensions()) / 2 - h / 2;
	unsigned int flags = WindowFlag::RESIZABLE;
	fullscreen = false;
	bool vsync = true;
	double maxFrameDuration = 0.25;
	double stepFrequency = 60.0;

	// Parse command line arguments

	// Create window
	window = windowManager->createWindow(title.c_str(), x, y, w, h, fullscreen, flags);
	if (!window)
	{
		throw std::runtime_error("ExampleApplication::ExampleApplication(): Failed to create window.");
	}

	// Set v-sync mode
	window->setVSync(vsync);

	// Setup step scheduler
	stepScheduler.setMaxFrameDuration(maxFrameDuration);
	stepScheduler.setStepFrequency(stepFrequency);

	// Setup performance sampling
	performanceSampler.setSampleSize(15);
	
	// Setup control profile
	Keyboard* keyboard = (*inputManager->getKeyboards()).front();
	Mouse* mouse = (*inputManager->getMice()).front();
	closeControl.bindKey(keyboard, Scancode::ESCAPE);
	closeControl.setActivatedCallback(std::bind(&Application::close, this, EXIT_SUCCESS));
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
}

void ExampleApplication::setTitle(const char* title)
{
	std::string fullTitle = std::string(title) + std::string(" - ") + this->title;
	window->setTitle(fullTitle.c_str());
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

void ExampleApplication::input()
{
	controlProfile.update();
}

