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

#include <emergent/input/mouse.hpp>
#include <emergent/input/observers.hpp>

namespace Emergent
{

Mouse::Mouse(const std::string& name):
	InputDevice(name),
	notifyingMotionObservers(false),
	notifyingButtonObservers(false),
	notifyingWheelObservers(false)
{}

Mouse::~Mouse()
{}

void Mouse::addMouseMotionObserver(MouseMotionObserver* observer)
{
	if (notifyingMotionObservers)
	{
		additionFlaggedMotionObservers.push_back(observer);
	}
	else
	{
		motionObservers.push_back(observer);
	}
} 

void Mouse::addMouseButtonObserver(MouseButtonObserver* observer)
{
	if (notifyingButtonObservers)
	{
		additionFlaggedButtonObservers.push_back(observer);
	}
	else
	{
		buttonObservers.push_back(observer);
	}
}

void Mouse::addMouseWheelObserver(MouseWheelObserver* observer)
{
	if (notifyingWheelObservers)
	{
		additionFlaggedWheelObservers.push_back(observer);
	}
	else
	{
		wheelObservers.push_back(observer);
	}
}

void Mouse::removeMouseMotionObserver(MouseMotionObserver* observer)
{
	if (notifyingMotionObservers)
	{
		removalFlaggedMotionObservers.push_back(observer);
	}
	else
	{
		motionObservers.remove(observer);
	}
}

void Mouse::removeMouseButtonObserver(MouseButtonObserver* observer)
{
	if (notifyingButtonObservers)
	{
		removalFlaggedButtonObservers.push_back(observer);
	}
	else
	{
		buttonObservers.remove(observer);
	}
}

void Mouse::removeMouseWheelObserver(MouseWheelObserver* observer)
{
	if (notifyingWheelObservers)
	{
		removalFlaggedWheelObservers.push_back(observer);
	}
	else
	{
		wheelObservers.remove(observer);
	}
}

void Mouse::removeMouseMotionObservers()
{
	motionObservers.clear();
}

void Mouse::removeMouseButtonObservers()
{
	buttonObservers.clear();
}

void Mouse::removeMouseWheelObservers()
{
	wheelObservers.clear();
}

void Mouse::press(int button, int x, int y)
{
	// Notify observers
	notifyingButtonObservers = true;
	for (auto observer: buttonObservers)
	{
		observer->mouseButtonPressed(button, x, y);
	}
	notifyingButtonObservers = false;
	
	// Process flags
	processFlaggedButtonObservers();
}

void Mouse::release(int button, int x, int y)
{
	// Notify observers
	notifyingButtonObservers = true;
	for (auto observer: buttonObservers)
	{
		observer->mouseButtonReleased(button, x, y);
	}
	notifyingButtonObservers = false;
	
	// Process flags
	processFlaggedButtonObservers();
}

void Mouse::move(int x, int y)
{
	previousPosition = currentPosition;
	std::get<0>(currentPosition) = x;
	std::get<1>(currentPosition) = y;
	
	// Notify observers
	notifyingMotionObservers = true;
	for (auto observer: motionObservers)
	{
		observer->mouseMoved(x, y);
	}
	notifyingMotionObservers = false;
	
	// Process flags
	processFlaggedMotionObservers();
}

void Mouse::scroll(int x, int y)
{
	// Notify observers
	notifyingWheelObservers = true;
	for (auto observer: wheelObservers)
	{
		observer->mouseWheelScrolled(x, y);
	}
	notifyingWheelObservers = false;
	
	// Process flags
	processFlaggedWheelObservers();
}

void Mouse::processFlaggedMotionObservers()
{
	// Remove observers which are flagged for removal
	for (auto observer: removalFlaggedMotionObservers)
	{
		motionObservers.remove(observer);
	}
	removalFlaggedMotionObservers.clear();
	
	// Add observers which are flagged for addition
	for (auto observer: additionFlaggedMotionObservers)
	{
		motionObservers.push_back(observer);
	}
	additionFlaggedMotionObservers.clear();
}

void Mouse::processFlaggedButtonObservers()
{
	// Remove observers which are flagged for removal
	for (auto observer: removalFlaggedButtonObservers)
	{
		buttonObservers.remove(observer);
	}
	removalFlaggedButtonObservers.clear();
	
	// Add observers which are flagged for addition
	for (auto observer: additionFlaggedButtonObservers)
	{
		buttonObservers.push_back(observer);
	}
	additionFlaggedButtonObservers.clear();
}

void Mouse::processFlaggedWheelObservers()
{
	// Remove observers which are flagged for removal
	for (auto observer: removalFlaggedWheelObservers)
	{
		wheelObservers.remove(observer);
	}
	removalFlaggedWheelObservers.clear();
	
	// Add observers which are flagged for addition
	for (auto observer: additionFlaggedWheelObservers)
	{
		wheelObservers.push_back(observer);
	}
	additionFlaggedWheelObservers.clear();
}

} // namespace Emergent

