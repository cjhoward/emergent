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

#ifndef EMERGENT_INPUT_MOUSE_HPP
#define EMERGENT_INPUT_MOUSE_HPP

#include <emergent/input/input-device.hpp>
#include <list>
#include <tuple>

namespace Emergent
{

class MouseMotionObserver;
class MouseButtonObserver;
class MouseWheelObserver;

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
	 * @param name Name of the mouse.
	 */
	Mouse(const std::string& name);

	/// Destroys a mouse input device.
	virtual ~Mouse();
	
	/// Returns InputDevice::Type::MOUSE.
	InputDevice::Type getType() const;
	
	/// Adds a mouse motion observer to this mouse.
	void addMouseMotionObserver(MouseMotionObserver* observer);

	/// Adds a mouse button observer to this mouse.
	void addMouseButtonObserver(MouseButtonObserver* observer);

	/// Adds a mouse wheel observer to this mouse.
	void addMouseWheelObserver(MouseWheelObserver* observer);

	/// Removes a mouse motion observer from this mouse.
	void removeMouseMotionObserver(MouseMotionObserver* observer);

	/// Removes a mouse button observer from this mouse.
	void removeMouseButtonObserver(MouseButtonObserver* observer);

	/// Removes a mouse wheel observer from this mouse.
	void removeMouseWheelObserver(MouseWheelObserver* observer);

	/// Removes all mouse motion observers from this mouse.
	void removeMouseMotionObservers();

	/// Removes all mouse button observers from this mouse.
	void removeMouseButtonObservers();

	/// Removes all mouse wheel observers from this mouse.
	void removeMouseWheelObservers();
	
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
	
	/// Returns the current mouse position.
	const std::tuple<int, int>& getCurrentPosition() const;

	/// Returns the previous mouse position.
	const std::tuple<int, int>& getPreviousPosition() const;
	
private:
	void processFlaggedMotionObservers();
	void processFlaggedButtonObservers();
	void processFlaggedWheelObservers();

	std::tuple<int, int> currentPosition;
	std::tuple<int, int> previousPosition;
	std::list<MouseMotionObserver*> motionObservers;
	std::list<MouseButtonObserver*> buttonObservers;
	std::list<MouseWheelObserver*> wheelObservers;
	bool notifyingMotionObservers;
	bool notifyingButtonObservers;
	bool notifyingWheelObservers;
	std::list<MouseMotionObserver*> additionFlaggedMotionObservers;
	std::list<MouseButtonObserver*> additionFlaggedButtonObservers;
	std::list<MouseWheelObserver*> additionFlaggedWheelObservers;
	std::list<MouseMotionObserver*> removalFlaggedMotionObservers;
	std::list<MouseButtonObserver*> removalFlaggedButtonObservers;
	std::list<MouseWheelObserver*> removalFlaggedWheelObservers;
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

