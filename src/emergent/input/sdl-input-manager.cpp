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

#include <emergent/input/sdl-input-manager.hpp>
#include <emergent/window/sdl-window-manager.hpp>
#include <emergent/window/sdl-window.hpp>
#include <emergent/input/keyboard.hpp>
#include <emergent/input/mouse.hpp>
#include <emergent/input/gamepad.hpp>
#include <emergent/input/observers.hpp>
#include <emergent/input/input-event.hpp>
#include <iostream>

namespace Emergent
{

SDLInputManager::SDLInputManager(SDLWindowManager* windowManager):
	windowManager(windowManager)
{
	keyboard = new Keyboard("SDL Default Keyboard");
	mouse = new Mouse("SDL Default Mouse");
	
	registerKeyboard(keyboard);
	registerMouse(mouse);
	
	keyboard->setDisconnected(false);
	mouse->setDisconnected(false);
}

SDLInputManager::~SDLInputManager()
{
	unregisterKeyboard(keyboard);
	unregisterMouse(mouse);
	
	for (auto gamepad: allocatedGamepads)
	{
		unregisterGamepad(gamepad);
		delete gamepad;
	}
	
	delete keyboard;
	delete mouse;
}

void SDLInputManager::update()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
			{
				if (event.key.repeat == 0)
				{
					int scancode = event.key.keysym.scancode;
					keyboard->press(scancode);
					break;
				}
			}
			
			case SDL_KEYUP:
			{
				if (event.key.repeat == 0)
				{
					int scancode = event.key.keysym.scancode;
					keyboard->release(scancode);
				}
				break;
			}
			
			case SDL_MOUSEMOTION:
			{
				int x = event.motion.x;
				int y = event.motion.y;
				mouse->move(x, y);
				break;
			}
			
			case SDL_MOUSEBUTTONDOWN:
			{
				int button = event.button.button;
				mouse->press(button, event.button.x, event.button.y);
				break;
			}
			
			case SDL_MOUSEBUTTONUP:
			{
				int button = event.button.button;
				mouse->release(button, event.button.x, event.button.y);
				break;
			}
			
			case SDL_MOUSEWHEEL:
			{
				int direction = (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) ? -1 : 1;
				int x = event.wheel.x * direction;
				int y = event.wheel.y * direction;
				mouse->scroll(x, y);
				break;
			}
			
			case SDL_CONTROLLERBUTTONDOWN:
			{
				int instanceID = event.cbutton.which;
				auto it = gamepadMap.find(instanceID);
				if (it == gamepadMap.end())
				{
					std::cerr << std::string("Received event from invalid gamepad") << std::endl;
					break;
				}
				
				Gamepad* gamepad = it->second;
				int button = event.cbutton.button;
				gamepad->press(button);
				break;
			}
			
			case SDL_CONTROLLERBUTTONUP:
			{
				int instanceID = event.cbutton.which;
				auto it = gamepadMap.find(instanceID);
				if (it == gamepadMap.end())
				{
					std::cerr << std::string("Received event from invalid gamepad") << std::endl;
					break;
				}
				
				Gamepad* gamepad = it->second;
				int button = event.cbutton.button;
				gamepad->release(button);
				break;
			}
			
			case SDL_CONTROLLERAXISMOTION:
			{
				int instanceID = event.caxis.which;
				auto it = gamepadMap.find(instanceID);
				if (it == gamepadMap.end())
				{
					std::cerr << std::string("Received event from invalid gamepad") << std::endl;
					break;
				}
				
				Gamepad* gamepad = it->second;
				int axis = event.caxis.axis;
				bool negative;
				float value;
				if (event.caxis.value < 0)
				{
					negative = true;
					value = (float)event.caxis.value / -32768.0f;
				}
				else
				{
					negative = false;
					value = (float)event.caxis.value / 32767.0f;
				}
				
				gamepad->move(axis, negative, value);
				break;
			}
			
			case SDL_CONTROLLERDEVICEADDED:
			{
				SDL_GameController* controller = SDL_GameControllerOpen(event.cdevice.which);
				if (controller != nullptr)
				{
					// Find controller's joystick instance ID
					SDL_Joystick* joystick = SDL_GameControllerGetJoystick(controller);
                	int instanceID = SDL_JoystickInstanceID(joystick);
                	
					// Determine gamepad name
					std::string name = SDL_GameControllerName(controller);
					if (name.empty())
					{
						name = "Unknown Gamepad";
					}
					
					bool reconnected = false;
					const std::list<Gamepad*>* gamepads = getGamepads();
					for (auto it = gamepads->begin(); it != gamepads->end(); ++it)
					{
						// Check if this gamepad was previously connected
						if ((*it)->isDisconnected() && (*it)->getName() == name)
						{
							// Map to new instance ID
							Gamepad* gamepad = *it;
							gamepadMap[instanceID] = gamepad;
							gamepad->setDisconnected(false);
							reconnected = true;
							
							std::cout << std::string("Reconnected gamepad \"") << name << std::string("\" with ID ") << instanceID << std::endl;
							break;
						}
					}
					
					if (!reconnected)
					{
						// Create new gamepad
						Gamepad* gamepad = new Gamepad(name);
						
						// Add to list of allocated gamepads
						allocatedGamepads.push_back(gamepad);
					
						// Register with the input manager
						registerGamepad(gamepad);
					
						// Map instance ID to gamepad pointer
						gamepadMap[instanceID] = gamepad;
						
						// Connect gamepad
						gamepad->setDisconnected(false);
						
						std::cout << std::string("Connected gamepad \"") << name << std::string("\" with ID ") << instanceID << std::endl;
					}
				}
				break;
			}
			
			case SDL_CONTROLLERDEVICEREMOVED:
			{
				int instanceID = event.cdevice.which;
				
				// Find gamepad
				auto mapIt = gamepadMap.find(instanceID);
				if (mapIt == gamepadMap.end())
				{
					std::cerr << std::string("Attempted to remove nonexistent gamepad with ID ") << instanceID << std::endl;
					break;
				}
				Gamepad* gamepad = mapIt->second;
				
				// Remove from gamepad map
				gamepadMap.erase(mapIt);
				
				// Set disconnected flag
				gamepad->setDisconnected(true);
				
				std::cout << std::string("Disconnected gamepad \"") << gamepad->getName() << std::string("\" with ID ") << instanceID << std::endl;
				break;
			}
			
			case SDL_WINDOWEVENT:
			{
				auto it = windowManager->windowMap.find(event.window.windowID);
				if (it == windowManager->windowMap.end())
				{
					break;
				}
				SDLWindow* window = it->second;


				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					window->resize(event.window.data1, event.window.data2);
				}
				else if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					window->close();
				}
				break;
			}
			
			case SDL_QUIT:
			{
				closed = true;
				break;
			}
			
			default:
				break;
		}
	}
}

void SDLInputManager::listen(InputEvent* inputEvent)
{
	int eventCount;
	
	// Gather events
	SDL_PumpEvents();
	
	// Check for key events
	eventCount = SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_KEYDOWN, SDL_KEYDOWN);
	if (eventCount)
	{
		int scancode = event.key.keysym.scancode;
		inputEvent->type = InputEvent::Type::KEY;
		inputEvent->key.first = keyboard;
		inputEvent->key.second = scancode;
		return;
	}
	
	// Check for mouse button events
	eventCount = SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONDOWN);
	if (eventCount)
	{
		int button = event.button.button;
		inputEvent->type = InputEvent::Type::MOUSE_BUTTON;
		inputEvent->mouseButton.first = mouse;
		inputEvent->mouseButton.second = button;
		return;
	}
	
	// Check for mouse wheel events
	eventCount = SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_MOUSEWHEEL, SDL_MOUSEWHEEL);
	if (eventCount)
	{
		int direction = (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) ? -1 : 1;
		int x = event.wheel.x * direction;
		int y = event.wheel.y * direction;
		inputEvent->type = InputEvent::Type::MOUSE_WHEEL;
		std::get<0>(inputEvent->mouseWheel) = mouse;
		std::get<1>(inputEvent->mouseWheel) = x;
		std::get<2>(inputEvent->mouseWheel) = y;
		return;
	}
	
	// Check for gamepad button events
	eventCount = SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLERBUTTONDOWN);
	if (eventCount)
	{
		int instanceID = event.cbutton.which;
		auto it = gamepadMap.find(instanceID);
		if (it == gamepadMap.end())
		{
			std::cerr << std::string("Received event from invalid gamepad") << std::endl;
			return;
		}
		
		Gamepad* gamepad = it->second;
		int button = event.cbutton.button;
		inputEvent->type = InputEvent::Type::GAMEPAD_BUTTON;
		inputEvent->gamepadButton.first = gamepad;
		inputEvent->gamepadButton.second = button;
		return;
	}
	
	// Check for gamepad axis events
	eventCount = SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_CONTROLLERAXISMOTION, SDL_CONTROLLERAXISMOTION);
	if (eventCount)
	{
		int instanceID = event.caxis.which;
		auto it = gamepadMap.find(instanceID);
		if (it == gamepadMap.end())
		{
			std::cerr << std::string("Received event from invalid gamepad") << std::endl;
			return;
		}
		
		Gamepad* gamepad = it->second;
		int axis = event.caxis.axis;
		bool negative = event.caxis.value < 0;
		inputEvent->type = InputEvent::Type::GAMEPAD_AXIS;
		std::get<0>(inputEvent->gamepadAxis) = gamepad;
		std::get<1>(inputEvent->gamepadAxis) = axis;
		std::get<2>(inputEvent->gamepadAxis) = negative;
		return;
	}
}

} // namespace Emergent

