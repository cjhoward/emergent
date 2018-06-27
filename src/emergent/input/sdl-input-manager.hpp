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

#ifndef EMERGENT_INPUT_SDL_INPUT_MANAGER_HPP
#define EMERGENT_INPUT_SDL_INPUT_MANAGER_HPP

#include <emergent/input/input-manager.hpp>
#include <list>
#include <map>
#include <SDL.h>

namespace Emergent
{

enum class Scancode;
class SDLWindowManager;
class SDLClipboard;

/**
 * Input manager implementation using SDL.
 *
 * @ingroup input
 */
class SDLInputManager: public InputManager
{
public:
	/**
	 * Creates an SDL input manager.
	 *
	 * @param windowManager Parent SDL window manager.
	 */
	SDLInputManager(SDLWindowManager* windowManager);

	/// Destroys an SDL input manager.
	~SDLInputManager();
	
	/// @copydoc InputManager::update()
	virtual void update();

	/// Returns the clipboard.
	virtual const Clipboard* getClipboard() const;

	/// @copydoc InputManager::getClipboard() const
	virtual Clipboard* getClipboard();
	
private:
	static const Scancode scancodeTable[287];

	SDLWindowManager* windowManager;
	SDLClipboard* clipboard;
	Keyboard* keyboard;
	Mouse* mouse;
	std::map<int, Gamepad*> gamepadMap;
	std::list<Gamepad*> allocatedGamepads;
	SDL_Event sdlEvent;
};

} // namespace Emergent

#endif // EMERGENT_INPUT_SDL_INPUT_MANAGER_HPP

