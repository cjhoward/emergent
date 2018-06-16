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

#ifndef EMERGENT_HELLO_WORLD_EXAMPLE_HPP
#define EMERGENT_HELLO_WORLD_EXAMPLE_HPP

#include "example-application.hpp"

class HelloWorldExample: public ExampleApplication
{
public:
	HelloWorldExample(int argc, char* argv[]);
	virtual ~HelloWorldExample();

	virtual void windowResized(int width, int height);

private:
	virtual void setup();
	virtual void update(float dt);
};

#endif // EMERGENT_HELLO_WORLD_EXAMPLE_HPP

