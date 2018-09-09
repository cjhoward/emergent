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

#include <emergent/window/display.hpp>

namespace Emergent
{

void Display::addDisplayMode(int width, int height, int refreshRate)
{
	DisplayMode mode;
	mode.width = width;
	mode.height = height;
	mode.refreshRate = refreshRate;

	displayModes.push_back(mode);
}

void Display::removeDisplayModes()
{
	displayModes.clear();
}

void Display::setCurrentDisplayModeIndex(std::size_t index)
{
	currentDisplayModeIndex = index;
}

void Display::setDefaultDisplayModeIndex(std::size_t index)
{
	defaultDisplayModeIndex = index;
}

void Display::setName(const std::string& name)
{
	this->name = name;
}

void Display::setDPI(float dpi)
{
	this->dpi = dpi;
}

void Display::setPosition(int x, int y)
{
	std::get<0>(position) = x;
	std::get<1>(position) = y;
}

void Display::setDimensions(int width, int height)
{
	std::get<0>(dimensions) = width;
	std::get<1>(dimensions) = height;
}

} // namespace Emergent

