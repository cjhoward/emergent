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

#include <emergent/input/sdl-clipboard.hpp>
#include <SDL2/SDL.h>

namespace Emergent
{

SDLClipboard::SDLClipboard()
{}

SDLClipboard::~SDLClipboard()
{}

void SDLClipboard::setContents(const char* contents)
{
	SDL_SetClipboardText(contents);
}

const char* SDLClipboard::getContents() const
{
	if (SDL_HasClipboardText() == SDL_TRUE)
	{
		char* text = SDL_GetClipboardText();
		contents = text;
		SDL_free(text);

		return contents.c_str();
	}

	return nullptr;
}

} // namespace Emergent

