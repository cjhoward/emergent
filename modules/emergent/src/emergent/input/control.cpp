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

#include <emergent/input/control.hpp>

namespace Emergent
{

Control::Control():
	deadzone(0.0f),
	currentValue(0.0f),
	previousValue(0.0f),
	reset(false),
	activatedCallback(nullptr),
	deactivatedCallback(nullptr),
	valueChangedCallback(nullptr),
	callbacksEnabled(true)
{}

Control::~Control()
{}

void Control::update()
{
	// Perform callbacks, if enabled
	if (callbacksEnabled)
	{
		if (activatedCallback)
		{
			if (isActive() && !wasActive())
			{
				activatedCallback();
			}
		}

		if (deactivatedCallback)
		{
			if (!isActive() && wasActive())
			{
				deactivatedCallback();
			}
		}

		if (valueChangedCallback)
		{
			if (currentValue != previousValue)
			{
				if (isActive() || wasActive())
				{
					valueChangedCallback(currentValue);
				}
			}
		}
	}

	// Update previous value
	previousValue = currentValue;

	// Reset temporary values
	if (reset)
	{
		currentValue = 0.0f;
		reset = false;
	}
}

void Control::setCurrentValue(float value)
{
	currentValue = value;
	reset = false;
}

void Control::setTemporaryValue(float value)
{
	currentValue = value;
	reset = true;
}

void Control::setDeadzone(float value)
{
	deadzone = value;
}

void Control::setActivatedCallback(std::function<void()> callback)
{
	this->activatedCallback = callback;
}

void Control::setDeactivatedCallback(std::function<void()> callback)
{
	this->deactivatedCallback = callback;
}

void Control::setValueChangedCallback(std::function<void(float)> callback)
{
	this->valueChangedCallback = callback;
}

} // namespace Emergent

