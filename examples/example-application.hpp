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

class ExampleApplication:
	public WindowObserver,
	public KeyObserver,
	public MouseMotionObserver,
	public MouseButtonObserver,
	public MouseWheelObserver
{
public:
	ExampleApplication(int argc, char* argv[]);
	virtual ~ExampleApplication();
	int execute();

protected:
	void close(int status);
	void setTitle(const char* title);
	void toggleFullscreen();

	FrameTimer frameTimer;
	StateInterpolator stateInterpolator;

private:
	virtual void windowClosed() final;
	virtual void windowResized(int width, int height);
	virtual void keyPressed(Scancode scancode);
	virtual void keyReleased(Scancode scancode);
	virtual void mouseMoved(int x, int y);
	virtual void mouseButtonPressed(int button, int x, int y);
	virtual void mouseButtonReleased(int button, int x, int y);
	virtual void mouseWheelScrolled(int x, int y);

	/// Called once at the start of the application.
	virtual void setup();

	/**
	 * Called continuously until the application is closed.
	 *
	 * @param dt Delta-time
	 */
	virtual void update(float t, float dt);

	virtual void draw();

	bool closed;
	int status;
	WindowManager* windowManager;
	Window* window;
	bool fullscreen;
	Control fullscreenControl;
	Control closeControl;
	ControlProfile controlProfile;
};

#endif // EMERGENT_EXAMPLE_APPLICATION_HPP

