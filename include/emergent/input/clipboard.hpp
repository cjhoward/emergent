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

#ifndef EMERGENT_INPUT_CLIPBOARD_HPP
#define EMERGENT_INPUT_CLIPBOARD_HPP

namespace Emergent
{

/**
 * Abstract base class for clipboards.
 *
 * @ingroup input
 */
class Clipboard
{
public:
	/// Creates a clipboard
	Clipboard();

	/// Destroys a clipboard
	virtual ~Clipboard();

	/**
	 * Sets the clipboard contents.
	 *
	 * @param contents UTF-8 encoded text.
	 */
	virtual void setContents(const char* contents) = 0;

	/**
	 * Returns the UTF-8 encoded clipboard contents, or nullptr if the clipboard is empty.
	 */
	virtual const char* getContents() const = 0;
};

} // namespace Emergent

#endif // EMERGENT_INPUT_CLIPBOARD_HPP

