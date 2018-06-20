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

#ifndef EMERGENT_EXAMPLE_APPLICATION_HPP
#define EMERGENT_EXAMPLE_APPLICATION_HPP

#include <emergent/emergent.hpp>
using namespace Emergent;

/**
 * Abstract base class for framerate-independent real-time graphical applications.
 */
class ExampleApplication:
	public EventHandler<ApplicationClosedEvent>,
	public EventHandler<WindowClosedEvent>,
	public EventHandler<WindowResizedEvent>,
	public EventHandler<KeyPressedEvent>,
	public EventHandler<KeyReleasedEvent>,
	public EventHandler<MouseMovedEvent>,
	public EventHandler<MouseButtonPressedEvent>,
	public EventHandler<MouseButtonReleasedEvent>,
	public EventHandler<MouseWheelScrolledEvent>
{
public:
	/**
	 * Creates an application.
	 *
	 * @param argc Argument count
	 * @param argv Argument list
	 */
	ExampleApplication(int argc, char* argv[]);

	/// Destroys an application.
	virtual ~ExampleApplication();

	/**
	 * Executes the application.
	 *
	 * @return Exit status code.
	 */
	int execute();

protected:
	void close(int status);
	void setTitle(const char* title);
	void size(int width, int height);
	void toggleFullscreen();
	void setUpdateRate(double frequency);

	StepScheduler stepScheduler;
	StepInterpolator stepInterpolator;

private:
	/// Called once at the start of the application.
	virtual void setup();

	/**
	 * Called each time the input manager has been updated.
	 */
	virtual void input();

	/**
	 * Called with a frequency determined by the update rate.
	 *
	 * @param t Total elapsed time.
	 * @param dt Time elapsed since previous update.
	 */
	virtual void update(float t, float dt);

	/**
	 * Called as frequently as possible. If v-sync is enabled, this frequency will be limited to the refresh rate of the display.
	 */
	virtual void draw();

	/// Called once when the application is closing.
	virtual void exit();

	virtual void handleEvent(const ApplicationClosedEvent& event) final;
	virtual void handleEvent(const WindowClosedEvent& event) final;
	virtual void handleEvent(const WindowResizedEvent& event);
	virtual void handleEvent(const KeyPressedEvent& event);
	virtual void handleEvent(const KeyReleasedEvent& event);
	virtual void handleEvent(const MouseMovedEvent& event);
	virtual void handleEvent(const MouseButtonPressedEvent& event);
	virtual void handleEvent(const MouseButtonReleasedEvent& event);
	virtual void handleEvent(const MouseWheelScrolledEvent& event);

	bool closed;
	int status;
	WindowManager* windowManager;
	InputManager* inputManager;
	Window* window;
	bool fullscreen;
	Control fullscreenControl;
	Control closeControl;
	ControlProfile controlProfile;
};

#endif // EMERGENT_EXAMPLE_APPLICATION_HPP

