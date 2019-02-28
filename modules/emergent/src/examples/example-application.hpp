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

#ifndef EMERGENT_EXAMPLE_APPLICATION_HPP
#define EMERGENT_EXAMPLE_APPLICATION_HPP

#include <emergent/emergent.hpp>
#include <string>

using namespace Emergent;

/**
 * Base class for example applications.
 */
class ExampleApplication: public Application
{
public:
	/**
	 * Creates an example application.
	 *
	 * @param argc Argument count
	 * @param argv Argument list
	 */
	ExampleApplication(int argc, char* argv[]);

	/// Destroys an example application.
	virtual ~ExampleApplication();

protected:
	void setTitle(const char* title);
	void toggleFullscreen();
	void setUpdateRate(double frequency);
	
	Window* window;
	ControlProfile controlProfile;

private:
	virtual void input();

	bool fullscreen;
	Control fullscreenControl;
	Control closeControl;
	std::string title;
};

#endif // EMERGENT_EXAMPLE_APPLICATION_HPP

