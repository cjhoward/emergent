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

#ifndef EMERGENT_INPUT_CONTROL_PROFILE_HPP
#define EMERGENT_INPUT_CONTROL_PROFILE_HPP

#include <map>
#include <string>

namespace Emergent
{

class Control;
class InputManager;

/**
 * Manages a set of controls.
 *
 * @ingroup input
 */
class ControlProfile
{
public:
	/// Creates a control profile.
	ControlProfile();
	
	/**
	 * Registers a control with the control profile.
	 *
	 * @param name Name of the control.
	 * @param control Pointer to the control to register.
	 */
	void registerControl(const std::string& name, Control* control);
	
	/**
	 * Saves the control profile to a file.
	 *
	 * @param filename File to which the control profile will be written.
	 */
	bool save(const std::string& filename);

	/**
	 * Loads the control profile from a file.
	 *
	 * @param filename File from which the control profile will be loaded.
	 * @param inputManager Input manager from which to retrieve input devices.
	 */
	bool load(const std::string& filename, InputManager* inputManager);
	
	/**
	 * Calls Control::update() on each control registered with this profile.
	 */
	void update();

	/**
	 * Enables or disables callbacks for all controls in the profile.
	 *
	 * @param enabled Whether to enable or disable callbacks for all controls in the profile.
	 */
	void setCallbacksEnabled(bool enabled);
	
	/// Returns the control map.
	const std::map<std::string, Control*>* getControlMap() const;
	
private:
	std::map<std::string, Control*> controls;
};

inline const std::map<std::string, Control*>* ControlProfile::getControlMap() const
{
	return &controls;
}

} // namespace Emergent

#endif // EMERGENT_INPUT_CONTROL_PROFILE_HPP

