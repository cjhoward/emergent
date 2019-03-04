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

#ifndef EMERGENT_INPUT_CONTROL_SET_HPP
#define EMERGENT_INPUT_CONTROL_SET_HPP

#include <list>

namespace Emergent
{

class Control;

/**
 * A set of controls which can be managed simultaneously.
 *
 * @ingroup input
 */
class ControlSet
{
public:
	/**
	 * Adds a control to the control set.
	 *
	 * @param control Pointer to the control to add.
	 */
	void addControl(Control* control);

	/**
	 * Removes a control from the control set.
	 *
	 * @param control Pointer to the control to remove.
	 */
	void removeControl(Control* control);

	/**
	 * Removes all controls from the control set.
	 */
	void removeControls();
	
	/**
	 * Calls Control::update() on each control in this control set.
	 */
	void update();

	/**
	 * Enables or disables callbacks for all controls in the control set.
	 *
	 * @param enabled Whether to enable or disable callbacks for all controls in the control set.
	 */
	void setCallbacksEnabled(bool enabled);

	/**
	 * Returns the list of controls in the control set.
	 */
	const std::list<Control*>* getControls() const;
	
private:
	std::list<Control*> controls;
};

inline const std::list<Control*>* ControlSet::getControls() const
{
	return &controls;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_CONTROL_SET_HPP

