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

#ifndef EMERGENT_WINDOW_DISPLAY_HPP
#define EMERGENT_WINDOW_DISPLAY_HPP

#include <tuple>
#include <vector>

namespace Emergent
{

/**
 * Contains display mode data for a display.
 *
 * @ingroup window
 */
class DisplayMode
{
public:
	int width;
	int height;
	int refreshRate;
};

/**
 * Represents a monitor or other display device.
 *
 * @ingroup window
 */
class Display
{
public:
	/**
	 * Adds a display mode to the display.
	 *
	 * @param width Width of the display mode.
	 * @param height Height of the display mode.
	 * @param refreshRate Refresh rate of the display mode, in Hz.
	 */
	void addDisplayMode(int width, int height, int refreshRate);

	/// Removes all display modes from the display.
	void removeDisplayModes();

	/// Sets the index of the current display mode for this display.
	void setCurrentDisplayModeIndex(std::size_t index);

	/// Sets the index of the default display mode for this display.
	void setDefaultDisplayModeIndex(std::size_t index);

	/// Returns the number of available display modes.
	std::size_t getDisplayModeCount() const;

	/// Returns the display mode at the specified index.
	const DisplayMode* getDisplayMode(std::size_t index) const;

	/// Returns the index of the current display mode for this display.
	std::size_t getCurrentDisplayModeIndex() const;

	/// Returns the index of the default display mode for this display.
	std::size_t getDefaultDisplayModeIndex() const;

	/// Sets the name of the display.
	void setName(const std::string& name);

	/// Sets the DPI of the display.
	void setDPI(float dpi);

	/**
	 * Sets the position of the display.
	 *
	 * @param x X-coordinate of the upper-left corner of the display.
	 * @param y Y-coordinate of the upper-left corner of the display.
	 */
	void setPosition(int x, int y);

	/**
	 * Sets the dimensions of the display.
	 *
	 * @param width Width of the display.
	 * @param height Height of the display.
	 */
	void setDimensions(int width, int height);

	/// Returns the name of the display.
	const std::string& getName() const;

	/// Returns the DPI of the display.
	float getDPI() const;

	/// Returns the position of the upper-left corner of the display.
	const std::tuple<int, int>& getPosition() const;

	/// Returns the dimensions of the display.
	const std::tuple<int, int>& getDimensions() const;

private:
	std::string name;
	float dpi;
	std::vector<DisplayMode> displayModes;
	std::size_t currentDisplayModeIndex;
	std::size_t defaultDisplayModeIndex;
	std::tuple<int, int> position;
	std::tuple<int, int> dimensions;
};

inline std::size_t Display::getDisplayModeCount() const
{
	return displayModes.size();
}

inline const DisplayMode* Display::getDisplayMode(std::size_t index) const
{
	return &displayModes[index];
}

inline std::size_t Display::getCurrentDisplayModeIndex() const
{
	return currentDisplayModeIndex;
}

inline std::size_t Display::getDefaultDisplayModeIndex() const
{
	return defaultDisplayModeIndex;
}

inline const std::string& Display::getName() const
{
	return name;
}

inline float Display::getDPI() const
{
	return dpi;
}

inline const std::tuple<int, int>& Display::getPosition() const
{
	return position;
}

inline const std::tuple<int, int>& Display::getDimensions() const
{
	return dimensions;
}

} // namespace Emergent

#endif // EMERGENT_WINDOW_DISPLAY_HPP

