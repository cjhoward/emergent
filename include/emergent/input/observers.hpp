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

#ifndef EMERGENT_INPUT_OBSERVERS_HPP
#define EMERGENT_INPUT_OBSERVERS_HPP

namespace Emergent
{

enum class Scancode;

/**
 * Abstract base class for keyboard event observers.
 * 
 * @ingroup input
 */
class KeyObserver
{
public:
	/**
	 * Called when a keyboard key has been pressed.
	 *
	 * @param scancode Scancode of the pressed key.
	 */
	virtual void keyPressed(Scancode scancode) = 0;

	/**
	 * Called when a keyboard key has been released.
	 *
	 * @param scancode Scancode of the released key.
	 */
	virtual void keyReleased(Scancode scancode) = 0;
};

/**
 * Abstract base class for mouse motion event observers.
 *
 * @ingroup input
 */
class MouseMotionObserver
{
public:
	/**
	 * Called when a mouse has been moved.
	 *
	 * @param x X-coordinate of the mouse position.
	 * @param y Y-coordinate of the mouse position.
	 */
	virtual void mouseMoved(int x, int y) = 0;
};

/**
 * Abstract base class for mouse button event observers.
 *
 * @ingroup input
 */
class MouseButtonObserver
{
public:
	virtual void mouseButtonPressed(int button, int x, int y) = 0;
	virtual void mouseButtonReleased(int button, int x, int y) = 0;
};

/**
 * Abstract base class for mouse wheel event observers.
 *
 * @ingroup input
 */
class MouseWheelObserver
{
public:
	/**
	 * Called when a mouse wheel has been scrolled.
	 *
	 * @param x Amount scrolled on the x-axis.
	 * @param y Amount scrolled on the y-axis.
	 */
	virtual void mouseWheelScrolled(int x, int y) = 0;
};

/**
 * Abstract base class for gamepad button event observers.
 *
 * @ingroup input
 */
class GamepadButtonObserver
{
public:
	/**
	 * Called when a gamepad button has been pressed.
	 *
	 * @param button Index of the pressed button.
	 */
	virtual void gamepadButtonPressed(int button) = 0;

	/**
	 * Called when a gamepad button has been released.
	 *
	 * @param button Index of the released button.
	 */
	virtual void gamepadButtonReleased(int button) = 0;
};

/**
 * Abstract base class for gamepad axis event observers.
 *
 * @ingroup input
 */
class GamepadAxisObserver
{
public:
	virtual void gamepadAxisMoved(int axis, bool negative, float value) = 0;
};

/**
 * Abstract base class for window event observers.
 *
 * @ingroup input
 */
class WindowObserver
{
public:
	/**
	 * Called when a window has been closed.
	 */
	virtual void windowClosed() = 0;

	/**
	 * Called when a window has been resized.
	 *
	 * @param width New width of the window.
	 * @param height New height of the window.
	 */
	virtual void windowResized(int width, int height) = 0;
};

} // namespace Emergent

#endif // EMERGENT_INPUT_OBSERVERS_HPP

