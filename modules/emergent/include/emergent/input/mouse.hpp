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

#ifndef EMERGENT_INPUT_MOUSE_HPP
#define EMERGENT_INPUT_MOUSE_HPP

#include <emergent/input/input-device.hpp>
#include <tuple>

namespace Emergent
{

class OSInterface;
class Window;

/**
 * Enumerates the mouse wheel axes.
 *
 * @ingroup input
 */
enum class MouseWheelAxis
{
	/// Indicates the positive X-axis.
	POSITIVE_X,

	/// Indicates the negative X-axis.
	NEGATIVE_X,

	/// Indicates the positive Y-axis.
	POSITIVE_Y,

	/// Indicates the negative Y-axis.
	NEGATIVE_Y
};

/**
 * Mouse input device.
 *
 * @ingroup input
 */
class Mouse: public InputDevice
{
public:
	/**
	 * Creates a mouse input device.
	 *
	 * @param DeviceManager The parent device manager.
	 * @param name Name of the mouse.
	 */
	Mouse(DeviceManager* DeviceManager, const std::string& name);

	/// Destroys a mouse input device.
	virtual ~Mouse();
	
	/// Returns InputDevice::Type::MOUSE.
	InputDevice::Type getType() const;
	
	/**
	 * Simulates a mouse button press. Notifies all mouse button observers via MouseButtonObserver::mouseButtonPressed().
	 *
	 * @param button Index of the pressed button.
	 * @param x X-coordinate of the mouse position.
	 * @param y Y-coordinate of the mouse position.
	 */
	void press(int button, int x, int y);

	/**
	 * Simulates a mouse button release. Notifies all mouse button observers via MouseButtonObserver::mouseButtonReleased().
	 *
	 * @param button Index of the released button.
	 * @param x X-coordinate of the mouse position.
	 * @param y Y-coordinate of the mouse position.
	 */
	void release(int button, int x, int y);

	/**
	 * Simulates mouse movement. Notifies all mouse motion observers via MouseMotionObserver::mouseMoved().
	 *
	 * @param x X-coordinate of the mouse position.
	 * @param y Y-coordinate of the mouse position.
	 */
	void move(int x, int y);

	/**
	 * Simulates mouse wheel scrolling. Notifies all mouse wheel observers via MouseWheelObserver::mouseWheelScrolled().
	 */
	void scroll(int x, int y);

	/**
	 * Warps the mouse to the specified position in a window.
	 *
	 * @param window Window to which the mouse should warp.
	 * @param x X-coordinate of the new mouse position.
	 * @param y Y-coordinate of the new mouse position.
	 */
	void warp(Window* window, int x, int y);

	/**
	 * Enables or disables relative mouse mode.
	 *
	 * @param enabled Whether to enable relative mouse mode.
	 */
	void setRelativeMode(bool enabled);

	/**
	 * Shows or hides the mouse cursor.
	 *
	 * @param visible Whether the mouse cursor should be visible.
	 */
	void setVisible(bool visible);
	
	/// Returns the current mouse position.
	const std::tuple<int, int>& getCurrentPosition() const;

	/// Returns the previous mouse position.
	const std::tuple<int, int>& getPreviousPosition() const;
	
private:
	friend class OSInterface;
	std::tuple<int, int> currentPosition;
	std::tuple<int, int> previousPosition;
};

inline InputDevice::Type Mouse::getType() const
{
	return InputDevice::Type::MOUSE;
}

inline const std::tuple<int, int>& Mouse::getCurrentPosition() const
{
	return currentPosition;
}

inline const std::tuple<int, int>& Mouse::getPreviousPosition() const
{
	return previousPosition;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_MOUSE_HPP

