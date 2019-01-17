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

#ifndef EMERGENT_UTILITY_APPLICATION_HPP
#define EMERGENT_UTILITY_APPLICATION_HPP

#include <emergent/animation/step-interpolator.hpp>
#include <emergent/input/input-event.hpp>
#include <emergent/utility/event-dispatcher.hpp>
#include <emergent/utility/event-handler.hpp>
#include <emergent/utility/step-scheduler.hpp>
#include <emergent/utility/performance-sampler.hpp>

namespace Emergent
{

class DeviceManager;
class OSInterface;
class InputManager;
class WindowManager;

/**
 * Base class for framerate-independent real-time graphical applications.
 *
 * @ingroup utility
 */
class Application:
	private EventHandler<ApplicationClosedEvent>,
	private EventHandler<WindowClosedEvent>,
	private EventHandler<WindowResizedEvent>,
	private EventHandler<KeyPressedEvent>,
	private EventHandler<KeyReleasedEvent>,
	private EventHandler<MouseMovedEvent>,
	private EventHandler<MouseButtonPressedEvent>,
	private EventHandler<MouseButtonReleasedEvent>,
	private EventHandler<MouseWheelScrolledEvent>
{
public:
	/**
	 * Creates an application.
	 *
	 * @throw std::runtime_error Failed to initialize OS interface.
	 */
	Application();

	/// Destroys an application.
	virtual ~Application();

	/**
	 * Executes the application.
	 *
	 * @return Exit status code.
	 */
	int execute();

	/**
	 * Closes the application.
	 *
	 * @param status Exit status code.
	 */
	void close(int status);

protected:
	EventDispatcher eventDispatcher;
	OSInterface* osInterface;
	DeviceManager* deviceManager;
	WindowManager* windowManager;
	StepScheduler stepScheduler;
	StepInterpolator stepInterpolator;
	PerformanceSampler performanceSampler;

private:
	/// Called once at the start of the application.
	virtual void setup();

	/**
	 * Called each time the input manager has been updated.
	 */
	virtual void input();

	/**
	 * Called with a frequency determined by the step frequency of the step scheduler.
	 *
	 * @param t Total elapsed time. This value will be a multiple of dt.
	 * @param dt Time elapsed since previous update. This value is determined by the step period of the step scheduler and should be constant.
	 */
	virtual void update(float t, float dt);

	/**
	 * Called when a frame should be rendered. Frames are rendered as frequently as possible. If v-sync is enabled, this frequency will be limited to the refresh rate of the display. Variables registered with the step interpolator will be interpolated right before this function is called.
	 */
	virtual void render();

	/// Called once when the application is closing.
	virtual void exit();

	virtual void handleEvent(const ApplicationClosedEvent& event) final;
	virtual void handleEvent(const WindowClosedEvent& event);
	virtual void handleEvent(const WindowResizedEvent& event);
	virtual void handleEvent(const KeyPressedEvent& event);
	virtual void handleEvent(const KeyReleasedEvent& event);
	virtual void handleEvent(const MouseMovedEvent& event);
	virtual void handleEvent(const MouseButtonPressedEvent& event);
	virtual void handleEvent(const MouseButtonReleasedEvent& event);
	virtual void handleEvent(const MouseWheelScrolledEvent& event);

	bool closed;
	int status;
};

} // namespace Emergent

#endif // EMERGENT_UTILITY_APPLICATION_HPP

