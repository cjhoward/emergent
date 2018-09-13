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

#include <emergent/utility/sdl-interface.hpp>
#include <emergent/input/gamepad.hpp>
#include <emergent/input/input-event.hpp>
#include <emergent/input/keyboard.hpp>
#include <emergent/input/mouse.hpp>
#include <emergent/input/scancode.hpp>
#include <emergent/utility/device-manager.hpp>
#include <emergent/utility/event-dispatcher.hpp>
#include <emergent/window/display.hpp>
#include <emergent/window/window.hpp>
#include <emergent/window/window-manager.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <GL/gl3w.h>

namespace Emergent
{

SDLInterface::SDLInterface(EventDispatcher* eventDispatcher):
	OSInterface(eventDispatcher)
{
	// Check if SDL was already initialized
	if (SDL_WasInit(0) != 0)
	{
		throw std::runtime_error("SDLInterface::SDLInterface(): SDL already initialized.");
	}

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::string error = std::string("SDLInterface::SDLInterface(): Failed to initialize SDL: \"") + std::string(SDL_GetError()) + std::string("\"");
		throw std::runtime_error(error.c_str());
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// Register displays
	int displayCount = SDL_GetNumVideoDisplays();
	for (int i = 0; i < displayCount; ++i)
	{
		Display* display = new Display();

		// Determine display name
		const char* name = SDL_GetDisplayName(i);
		display->setName(name);

		// Determine display DPI
		float dpi = -1.0f;
		SDL_GetDisplayDPI(i, &dpi, nullptr, nullptr);
		display->setDPI(dpi);

		// Determine display bounds
		SDL_Rect bounds;
		SDL_GetDisplayBounds(i, &bounds);
		display->setPosition(bounds.x, bounds.y);
		display->setDimensions(bounds.w, bounds.h);

		// Get current display mode
		SDL_DisplayMode currentMode;
		SDL_GetCurrentDisplayMode(i, &currentMode);

		// Get desktop display mode
		SDL_DisplayMode desktopMode;
		SDL_GetDesktopDisplayMode(i, &desktopMode);

		// For each display mode
		int displayModeCount = SDL_GetNumDisplayModes(i);
		for (int j = 0; j < displayModeCount; ++j)
		{
    		SDL_DisplayMode mode = {SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0};
			SDL_GetDisplayMode(i, j, &mode);

			// Add display mode
			display->addDisplayMode(mode.w, mode.h, mode.refresh_rate);

			// Check if this display mode is the current display mode
			if (mode.format == currentMode.format &&
				mode.w == currentMode.w &&
				mode.h == currentMode.h &&
				mode.refresh_rate == currentMode.refresh_rate)
			{
				display->setCurrentDisplayModeIndex(j);
			}

			// Check if this display mode is the default display mode
			if (mode.format == desktopMode.format &&
				mode.w == desktopMode.w &&
				mode.h == desktopMode.h &&
				mode.refresh_rate == desktopMode.refresh_rate)
			{
				display->setDefaultDisplayModeIndex(j);
			}
		}

		allocatedDisplays.push_back(display);
		deviceManager->registerDisplay(display);
	}


	SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "0");
	
	// Register keyboard
	keyboard = new Keyboard(deviceManager, "SDL Default Keyboard");
	keyboard->setDisconnected(false);
	deviceManager->registerKeyboard(keyboard);

	// Register mouse
	mouse = new Mouse(deviceManager, "SDL Default Mouse");
	mouse->setDisconnected(false);
	deviceManager->registerMouse(mouse);
}

SDLInterface::~SDLInterface()
{
	// Unregister and delete keyboard
	deviceManager->unregisterKeyboard(keyboard);
	delete keyboard;
	
	// Unregister and delete mouse
	deviceManager->unregisterMouse(mouse);
	delete mouse;

	// Unregister and delete gamepads
	for (auto gamepad: allocatedGamepads)
	{
		deviceManager->unregisterGamepad(gamepad);
		delete gamepad;
	}

	// Unregister and delete displays
	for (Display* display: allocatedDisplays)
	{
		deviceManager->unregisterDisplay(display);
		delete display;
	}

	// Shutdown SDL
	SDL_Quit();
}

void SDLInterface::routeEvents()
{
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_KEYDOWN:
			{
				if (sdlEvent.key.repeat == 0)
				{
					KeyPressedEvent event;
					event.keyboard = keyboard;
					event.scancode = Scancode::UNKNOWN;
					if (sdlEvent.key.keysym.scancode <= SDL_SCANCODE_APP2)
					{
						event.scancode = scancodeTable[sdlEvent.key.keysym.scancode];
					}

					eventDispatcher->queue(event);
				}
				break;
			}
			
			case SDL_KEYUP:
			{
				if (sdlEvent.key.repeat == 0)
				{

					KeyReleasedEvent event;
					event.keyboard = keyboard;
					event.scancode = Scancode::UNKNOWN;
					if (sdlEvent.key.keysym.scancode <= SDL_SCANCODE_APP2)
					{
						event.scancode = scancodeTable[sdlEvent.key.keysym.scancode];
					}

					eventDispatcher->queue(event);
				}
				break;
			}
			
			case SDL_MOUSEMOTION:
			{
				MouseMovedEvent event;
				event.mouse = mouse;
				event.x = sdlEvent.motion.x;
				event.y = sdlEvent.motion.y;
				event.dx = sdlEvent.motion.xrel;
				event.dy = sdlEvent.motion.yrel;


				OSInterface::updateMousePosition(mouse, sdlEvent.motion.x, sdlEvent.motion.y);

				eventDispatcher->queue(event);
				break;
			}
			
			case SDL_MOUSEBUTTONDOWN:
			{
				MouseButtonPressedEvent event;
				event.mouse = mouse;
				event.button = sdlEvent.button.button;

				eventDispatcher->queue(event);
				break;
			}
			
			case SDL_MOUSEBUTTONUP:
			{
				MouseButtonReleasedEvent event;
				event.mouse = mouse;
				event.button = sdlEvent.button.button;

				eventDispatcher->queue(event);
				break;
			}
			
			case SDL_MOUSEWHEEL:
			{
				MouseWheelScrolledEvent event;
				event.mouse = mouse;
				int direction = (sdlEvent.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) ? -1 : 1;
				event.x = sdlEvent.wheel.x * direction;
				event.y = sdlEvent.wheel.y * direction;

				eventDispatcher->queue(event);
				break;
			}
			
			case SDL_CONTROLLERBUTTONDOWN:
			{
				int instanceID = sdlEvent.cbutton.which;
				auto it = gamepadMap.find(instanceID);
				if (it == gamepadMap.end())
				{
					std::cerr << std::string("Received sdlEvent from invalid gamepad") << std::endl;
					break;
				}

				GamepadButtonPressedEvent event;
				event.gamepad = it->second;
				event.button = sdlEvent.cbutton.button;

				eventDispatcher->queue(event);
				break;
			}
			
			case SDL_CONTROLLERBUTTONUP:
			{
				int instanceID = sdlEvent.cbutton.which;
				auto it = gamepadMap.find(instanceID);
				if (it == gamepadMap.end())
				{
					std::cerr << std::string("Received sdlEvent from invalid gamepad") << std::endl;
					break;
				}
				
				GamepadButtonReleasedEvent event;
				event.gamepad = it->second;
				event.button = sdlEvent.cbutton.button;

				eventDispatcher->queue(event);
				break;
			}
			
			case SDL_CONTROLLERAXISMOTION:
			{
				int instanceID = sdlEvent.caxis.which;
				auto it = gamepadMap.find(instanceID);
				if (it == gamepadMap.end())
				{
					std::cerr << std::string("Received sdlEvent from invalid gamepad") << std::endl;
					break;
				}

				GamepadAxisMovedEvent event;
				event.gamepad = it->second;			
				event.axis = sdlEvent.caxis.axis;
				if (sdlEvent.caxis.value < 0)
				{
					event.negative = true;
					event.value = (float)sdlEvent.caxis.value / -32768.0f;
				}
				else
				{
					event.negative = false;
					event.value = (float)sdlEvent.caxis.value / 32767.0f;
				}

				eventDispatcher->queue(event);
				break;
			}
			
			case SDL_CONTROLLERDEVICEADDED:
			{
				SDL_GameController* controller = SDL_GameControllerOpen(sdlEvent.cdevice.which);
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
					const std::list<Gamepad*>* gamepads = deviceManager->getGamepads();
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
						Gamepad* gamepad = new Gamepad(deviceManager, name);
						
						// Add to list of allocated gamepads
						allocatedGamepads.push_back(gamepad);
					
						// Register with the device manager
						deviceManager->registerGamepad(gamepad);
					
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
				int instanceID = sdlEvent.cdevice.which;
				
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
				const std::list<Window*>* windows = windowManager->getWindows();
				for (auto it = windows->begin(); it != windows->end(); ++it)
				{
					if (static_cast<const WindowData*>((*it)->getWindowData())->windowID == sdlEvent.window.windowID)
					{
						if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
						{
							WindowResizedEvent event;
							event.window = *it;
							event.width = sdlEvent.window.data1;
							event.height = sdlEvent.window.data2;

							eventDispatcher->queue(event);
						}
						else if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE)
						{
							WindowClosedEvent event;
							event.window = *it;

							eventDispatcher->queue(event);
						}

						break;
					}
				}

				break;
			}
			
			case SDL_QUIT:
			{
				ApplicationClosedEvent event;

				eventDispatcher->queue(event);
				break;
			}
			
			default:
				break;
		}
	}
}

void SDLInterface::startTextInput()
{
	SDL_StartTextInput();
}

void SDLInterface::stopTextInput()
{
	SDL_StopTextInput();
}

void SDLInterface::setClipboardText(const char* text)
{
	SDL_SetClipboardText(text);
}

const char* SDLInterface::getClipboardText() const
{
	if (SDL_HasClipboardText() == SDL_TRUE)
	{
		char* text = SDL_GetClipboardText();
		clipboardText = text;
		SDL_free(text);

		return clipboardText.c_str();
	}

	return nullptr;
}

void* SDLInterface::openWindow(const char* title, int x, int y, int width, int height, bool fullscreen, unsigned int flags)
{
	int display = 0;
	SDL_Rect bounds;
	SDL_GetDisplayBounds(display, &bounds);
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(display, &mode);

	int windowedX = x;
	int windowedY = y;
	int windowedWidth = width;
	int windowedHeight = height;
	int fullscreenX = bounds.x;
	int fullscreenY = bounds.y;
	int fullscreenWidth = mode.w;
	int fullscreenHeight = mode.h;

	// Determine window flags
	Uint32 sdlFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
	if (fullscreen)
	{
		sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS;
		x = fullscreenX;
		y = fullscreenY;
		width = fullscreenWidth;
		height = fullscreenHeight;
	}
	else
	{
		x = windowedX;
		y = windowedY;
		width = windowedWidth;
		height = windowedHeight;

		if (flags & WindowFlag::RESIZABLE)
		{
			sdlFlags |= SDL_WINDOW_RESIZABLE;
		}
		if (flags & WindowFlag::BORDERLESS)
		{
			sdlFlags |= SDL_WINDOW_BORDERLESS;
		}
		if (flags & WindowFlag::MINIMIZED)
		{
			sdlFlags |= SDL_WINDOW_MINIMIZED;
		}
		if (flags & WindowFlag::MAXIMIZED)
		{
			sdlFlags |= SDL_WINDOW_MAXIMIZED;
		}
	}

	// Create SDL window
	SDL_Window* sdlWindow = SDL_CreateWindow(title, x, y, width, height, sdlFlags);
	if (!sdlWindow)
	{
		return nullptr;
	}
	SDL_RaiseWindow(sdlWindow);

	// Select OpenGL version
	int openGLVersionMajor = 3;
	int openGLVersionMinor = 3;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, openGLVersionMajor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, openGLVersionMinor);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	// Set OpenGL buffer attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);


	// Create OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(sdlWindow);
	if (!context)
	{
		SDL_DestroyWindow(sdlWindow);
		return nullptr;
	}

	// Initialize OpenGL
	if (gl3wInit())
	{
		std::string error = std::string("SDLInterface::openWindow(): Failed to initialize OpenGL.");
		throw std::runtime_error(error.c_str());
	}
	
	// Check if OpenGL version is supported
	if (!gl3wIsSupported(openGLVersionMajor, openGLVersionMinor))
	{
		std::stringstream stream;
		stream << std::string("SDLInterface::openWindow(): OpenGL version ") << openGLVersionMajor << std::string(".") << openGLVersionMinor << std::string(" not supported.");

		throw std::runtime_error(stream.str().c_str());
	}

	// Disable v-sync
	SDL_GL_MakeCurrent(sdlWindow, context);
	SDL_GL_SetSwapInterval(0);

	// Create SDL window data structure
	WindowData* data = new WindowData();
	data->window = sdlWindow;
	data->context = context;
	data->x = x;
	data->y = y;
	data->width = width;
	data->height = height;
	data->windowID = SDL_GetWindowID(sdlWindow);

	return static_cast<void*>(data);
}

void SDLInterface::closeWindow(Window* window)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());

	SDL_DestroyWindow(data->window);
	SDL_GL_DeleteContext(data->context);

	delete data;
}

void SDLInterface::setWindowTitle(Window* window, const char* title)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());
	SDL_SetWindowTitle(data->window, title);
}

void SDLInterface::setWindowPosition(Window* window, int x, int y)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());
	SDL_SetWindowPosition(data->window, x, y);
}

void SDLInterface::setWindowDimensions(Window* window, int width, int height)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());
	SDL_SetWindowSize(data->window, width, height);
}

void SDLInterface::setWindowResizable(Window* window, bool resizable)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());
	SDL_SetWindowResizable(data->window, (resizable) ? SDL_TRUE : SDL_FALSE);
}

void SDLInterface::setWindowBordered(Window* window, bool bordered)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());
	SDL_SetWindowBordered(data->window, (bordered) ? SDL_TRUE : SDL_FALSE);
}

void SDLInterface::setWindowFullscreen(Window* window, bool fullscreen)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());

	if (!fullscreen)
	{
		SDL_HideWindow(data->window);
		SDL_SetWindowFullscreen(data->window, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
		SDL_SetWindowSize(data->window, data->width, data->height);
		SDL_SetWindowResizable(data->window, (window->isResizable()) ? SDL_TRUE : SDL_FALSE);
		SDL_SetWindowBordered(data->window, (window->hasBorder()) ? SDL_TRUE : SDL_FALSE);
		SDL_SetWindowPosition(data->window, data->x, data->y);
		SDL_RaiseWindow(data->window);
	}
	else
	{
		// Store windowed mode position and size
		SDL_GetWindowPosition(data->window, &data->x, &data->y);
		SDL_GetWindowSize(data->window, &data->width, &data->height);

		int display = SDL_GetWindowDisplayIndex(data->window);
		SDL_Rect bounds;
		SDL_GetDisplayBounds(display, &bounds);
		SDL_DisplayMode mode;
		SDL_GetCurrentDisplayMode(display, &mode);

		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP;

		SDL_HideWindow(data->window);
		SDL_SetWindowBordered(data->window, SDL_FALSE);
		SDL_SetWindowResizable(data->window, SDL_FALSE);
		SDL_SetWindowPosition(data->window, bounds.x, bounds.y);
		SDL_SetWindowSize(data->window, mode.w, mode.h);
		SDL_SetWindowFullscreen(data->window, flags);
		SDL_ShowWindow(data->window);
	}
}

void SDLInterface::setWindowVSync(Window* window, bool vsync)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());

	SDL_GL_MakeCurrent(data->window, data->context);
	if (vsync)
	{
		if (SDL_GL_SetSwapInterval(-1) != 0)
		{
			SDL_GL_SetSwapInterval(1);
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}
}

void SDLInterface::setWindowInputGrabbed(Window* window, bool grabbed)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());
	SDL_SetWindowGrab(data->window, (grabbed) ? SDL_TRUE : SDL_FALSE);
}

void SDLInterface::makeWindowCurrent(Window* window)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());
	SDL_GL_MakeCurrent(data->window, data->context);
}

void SDLInterface::swapWindowBuffers(Window* window)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());
	SDL_GL_SwapWindow(data->window);
}

void SDLInterface::warpMousePosition(Window* window, int x, int y)
{
	WindowData* data = static_cast<WindowData*>(window->getWindowData());
	SDL_WarpMouseInWindow(data->window, x, y);
}

void SDLInterface::setRelativeMouseMode(Mouse* mouse, bool enabled)
{
	SDL_SetRelativeMouseMode((enabled) ? SDL_TRUE : SDL_FALSE);
}

void SDLInterface::setMouseVisible(Mouse* mouse, bool visible)
{
	SDL_ShowCursor((visible) ? SDL_ENABLE : SDL_DISABLE);
}

const Scancode SDLInterface::scancodeTable[287] =
{
	Scancode::UNKNOWN, // SDL_SCANCODE_UNKNOWN = 0,
	Scancode::UNKNOWN, // Unassigned = 1
	Scancode::UNKNOWN, // Unassigned = 2
	Scancode::UNKNOWN, // Unassigned = 3
	Scancode::A, // SDL_SCANCODE_A = 4,
	Scancode::B, // SDL_SCANCODE_B = 5,
	Scancode::C, // SDL_SCANCODE_C = 6,
	Scancode::D, // SDL_SCANCODE_D = 7,
	Scancode::E, // SDL_SCANCODE_E = 8,
	Scancode::F, // SDL_SCANCODE_F = 9,
	Scancode::G, // SDL_SCANCODE_G = 10,
	Scancode::H, // SDL_SCANCODE_H = 11,
	Scancode::I, // SDL_SCANCODE_I = 12,
	Scancode::J, // SDL_SCANCODE_J = 13,
	Scancode::K, // SDL_SCANCODE_K = 14,
	Scancode::L, // SDL_SCANCODE_L = 15,
	Scancode::M, // SDL_SCANCODE_M = 16,
	Scancode::N, // SDL_SCANCODE_N = 17,
	Scancode::O, // SDL_SCANCODE_O = 18,
	Scancode::P, // SDL_SCANCODE_P = 19,
	Scancode::Q, // SDL_SCANCODE_Q = 20,
	Scancode::R, // SDL_SCANCODE_R = 21,
	Scancode::S, // SDL_SCANCODE_S = 22,
	Scancode::T, // SDL_SCANCODE_T = 23,
	Scancode::U, // SDL_SCANCODE_U = 24,
	Scancode::V, // SDL_SCANCODE_V = 25,
	Scancode::W, // SDL_SCANCODE_W = 26,
	Scancode::X, // SDL_SCANCODE_X = 27,
	Scancode::Y, // SDL_SCANCODE_Y = 28,
	Scancode::Z, // SDL_SCANCODE_Z = 29,
	Scancode::ONE, // SDL_SCANCODE_1 = 30,
	Scancode::TWO, // SDL_SCANCODE_2 = 31,
	Scancode::THREE, // SDL_SCANCODE_3 = 32,
	Scancode::FOUR, // SDL_SCANCODE_4 = 33,
	Scancode::FIVE, // SDL_SCANCODE_5 = 34,
	Scancode::SIX, // SDL_SCANCODE_6 = 35,
	Scancode::SEVEN, // SDL_SCANCODE_7 = 36,
	Scancode::EIGHT, // SDL_SCANCODE_8 = 37,
	Scancode::NINE, // SDL_SCANCODE_9 = 38,
	Scancode::ZERO, // SDL_SCANCODE_0 = 39,
	Scancode::RETURN, // SDL_SCANCODE_RETURN = 40,
	Scancode::ESCAPE, // SDL_SCANCODE_ESCAPE = 41,
	Scancode::BACKSPACE, // SDL_SCANCODE_BACKSPACE = 42,
	Scancode::TAB, // SDL_SCANCODE_TAB = 43,
	Scancode::SPACE, // SDL_SCANCODE_SPACE = 44,
	Scancode::MINUS, // SDL_SCANCODE_MINUS = 45,
	Scancode::EQUALS, // SDL_SCANCODE_EQUALS = 46,
	Scancode::LEFTBRACKET, // SDL_SCANCODE_LEFTBRACKET = 47,
	Scancode::RIGHTBRACKET, // SDL_SCANCODE_RIGHTBRACKET = 48,
	Scancode::BACKSLASH, // SDL_SCANCODE_BACKSLASH = 49,
	Scancode::NONUSHASH, // SDL_SCANCODE_NONUSHASH = 50,
	Scancode::SEMICOLON, // SDL_SCANCODE_SEMICOLON = 51,
	Scancode::APOSTROPHE, // SDL_SCANCODE_APOSTROPHE = 52,
	Scancode::GRAVE, // SDL_SCANCODE_GRAVE = 53,
	Scancode::COMMA, // SDL_SCANCODE_COMMA = 54,
	Scancode::PERIOD, // SDL_SCANCODE_PERIOD = 55,
	Scancode::SLASH, // SDL_SCANCODE_SLASH = 56,
	Scancode::CAPSLOCK, // SDL_SCANCODE_CAPSLOCK = 57,
	Scancode::F1, // SDL_SCANCODE_F1 = 58,
	Scancode::F2, // SDL_SCANCODE_F2 = 59,
	Scancode::F3, // SDL_SCANCODE_F3 = 60,
	Scancode::F4, // SDL_SCANCODE_F4 = 61,
	Scancode::F5, // SDL_SCANCODE_F5 = 62,
	Scancode::F6, // SDL_SCANCODE_F6 = 63,
	Scancode::F7, // SDL_SCANCODE_F7 = 64,
	Scancode::F8, // SDL_SCANCODE_F8 = 65,
	Scancode::F9, // SDL_SCANCODE_F9 = 66,
	Scancode::F10, // SDL_SCANCODE_F10 = 67,
	Scancode::F11, // SDL_SCANCODE_F11 = 68,
	Scancode::F12, // SDL_SCANCODE_F12 = 69,
	Scancode::PRINTSCREEN, // SDL_SCANCODE_PRINTSCREEN = 70,
	Scancode::SCROLLLOCK, // SDL_SCANCODE_SCROLLLOCK = 71,
	Scancode::PAUSE, // SDL_SCANCODE_PAUSE = 72,
	Scancode::INSERT, // SDL_SCANCODE_INSERT = 73,
	Scancode::HOME, // SDL_SCANCODE_HOME = 74,
	Scancode::PAGEUP, // SDL_SCANCODE_PAGEUP = 75,
	Scancode::DELETE, // SDL_SCANCODE_DELETE = 76,
	Scancode::END, // SDL_SCANCODE_END = 77,
	Scancode::PAGEDOWN, // SDL_SCANCODE_PAGEDOWN = 78,
	Scancode::RIGHT, // SDL_SCANCODE_RIGHT = 79,
	Scancode::LEFT, // SDL_SCANCODE_LEFT = 80,
	Scancode::DOWN, // SDL_SCANCODE_DOWN = 81,
	Scancode::UP, // SDL_SCANCODE_UP = 82,
	Scancode::NUMLOCKCLEAR, // SDL_SCANCODE_NUMLOCKCLEAR = 83,
	Scancode::KP_DIVIDE, // SDL_SCANCODE_KP_DIVIDE = 84,
	Scancode::KP_MULTIPLY, // SDL_SCANCODE_KP_MULTIPLY = 85,
	Scancode::KP_MINUS, // SDL_SCANCODE_KP_MINUS = 86,
	Scancode::KP_PLUS, // SDL_SCANCODE_KP_PLUS = 87,
	Scancode::KP_ENTER, // SDL_SCANCODE_KP_ENTER = 88,
	Scancode::KP_1, // SDL_SCANCODE_KP_1 = 89,
	Scancode::KP_2, // SDL_SCANCODE_KP_2 = 90,
	Scancode::KP_3, // SDL_SCANCODE_KP_3 = 91,
	Scancode::KP_4, // SDL_SCANCODE_KP_4 = 92,
	Scancode::KP_5, // SDL_SCANCODE_KP_5 = 93,
	Scancode::KP_6, // SDL_SCANCODE_KP_6 = 94,
	Scancode::KP_7, // SDL_SCANCODE_KP_7 = 95,
	Scancode::KP_8, // SDL_SCANCODE_KP_8 = 96,
	Scancode::KP_9, // SDL_SCANCODE_KP_9 = 97,
	Scancode::KP_0, // SDL_SCANCODE_KP_0 = 98,
	Scancode::KP_PERIOD, // SDL_SCANCODE_KP_PERIOD = 99,
	Scancode::NONUSBACKSLASH, // SDL_SCANCODE_NONUSBACKSLASH = 100,
	Scancode::APPLICATION, // SDL_SCANCODE_APPLICATION = 101,
	Scancode::POWER, // SDL_SCANCODE_POWER = 102,
	Scancode::KP_EQUALS, // SDL_SCANCODE_KP_EQUALS = 103,
	Scancode::F13, // SDL_SCANCODE_F13 = 104,
	Scancode::F14, // SDL_SCANCODE_F14 = 105,
	Scancode::F15, // SDL_SCANCODE_F15 = 106,
	Scancode::F16, // SDL_SCANCODE_F16 = 107,
	Scancode::F17, // SDL_SCANCODE_F17 = 108,
	Scancode::F18, // SDL_SCANCODE_F18 = 109,
	Scancode::F19, // SDL_SCANCODE_F19 = 110,
	Scancode::F20, // SDL_SCANCODE_F20 = 111,
	Scancode::F21, // SDL_SCANCODE_F21 = 112,
	Scancode::F22, // SDL_SCANCODE_F22 = 113,
	Scancode::F23, // SDL_SCANCODE_F23 = 114,
	Scancode::F24, // SDL_SCANCODE_F24 = 115,
	Scancode::EXECUTE, // SDL_SCANCODE_EXECUTE = 116,
	Scancode::HELP, // SDL_SCANCODE_HELP = 117,
	Scancode::MENU, // SDL_SCANCODE_MENU = 118,
	Scancode::SELECT, // SDL_SCANCODE_SELECT = 119,
	Scancode::STOP, // SDL_SCANCODE_STOP = 120,
	Scancode::AGAIN, // SDL_SCANCODE_AGAIN = 121,
	Scancode::UNDO, // SDL_SCANCODE_UNDO = 122,
	Scancode::CUT, // SDL_SCANCODE_CUT = 123,
	Scancode::COPY, // SDL_SCANCODE_COPY = 124,
	Scancode::PASTE, // SDL_SCANCODE_PASTE = 125,
	Scancode::FIND, // SDL_SCANCODE_FIND = 126,
	Scancode::MUTE, // SDL_SCANCODE_MUTE = 127,
	Scancode::VOLUMEUP, // SDL_SCANCODE_VOLUMEUP = 128,
	Scancode::VOLUMEDOWN, // SDL_SCANCODE_VOLUMEDOWN = 129,
	Scancode::LOCKINGCAPSLOCK, // Unassigned = 130
	Scancode::LOCKINGNUMLOCK, // Unassigned = 131
	Scancode::LOCKINGSCROLLLOCK, // Unassigned = 132
	Scancode::KP_COMMA, // SDL_SCANCODE_KP_COMMA = 133,
	Scancode::KP_EQUALSAS400, // SDL_SCANCODE_KP_EQUALSAS400 = 134,
	Scancode::INTERNATIONAL1, // SDL_SCANCODE_INTERNATIONAL1 = 135,
	Scancode::INTERNATIONAL2, // SDL_SCANCODE_INTERNATIONAL2 = 136,
	Scancode::INTERNATIONAL3, // SDL_SCANCODE_INTERNATIONAL3 = 137,
	Scancode::INTERNATIONAL4, // SDL_SCANCODE_INTERNATIONAL4 = 138,
	Scancode::INTERNATIONAL5, // SDL_SCANCODE_INTERNATIONAL5 = 139,
	Scancode::INTERNATIONAL6, // SDL_SCANCODE_INTERNATIONAL6 = 140,
	Scancode::INTERNATIONAL7, // SDL_SCANCODE_INTERNATIONAL7 = 141,
	Scancode::INTERNATIONAL8, // SDL_SCANCODE_INTERNATIONAL8 = 142,
	Scancode::INTERNATIONAL9, // SDL_SCANCODE_INTERNATIONAL9 = 143,
	Scancode::LANG1, // SDL_SCANCODE_LANG1 = 144,
	Scancode::LANG2, // SDL_SCANCODE_LANG2 = 145,
	Scancode::LANG3, // SDL_SCANCODE_LANG3 = 146,
	Scancode::LANG4, // SDL_SCANCODE_LANG4 = 147,
	Scancode::LANG5, // SDL_SCANCODE_LANG5 = 148,
	Scancode::LANG6, // SDL_SCANCODE_LANG6 = 149,
	Scancode::LANG7, // SDL_SCANCODE_LANG7 = 150,
	Scancode::LANG8, // SDL_SCANCODE_LANG8 = 151,
	Scancode::LANG9, // SDL_SCANCODE_LANG9 = 152,
	Scancode::ALTERASE, // SDL_SCANCODE_ALTERASE = 153,
	Scancode::SYSREQ, // SDL_SCANCODE_SYSREQ = 154,
	Scancode::CANCEL, // SDL_SCANCODE_CANCEL = 155,
	Scancode::CLEAR, // SDL_SCANCODE_CLEAR = 156,
	Scancode::PRIOR, // SDL_SCANCODE_PRIOR = 157,
	Scancode::RETURN2, // SDL_SCANCODE_RETURN2 = 158,
	Scancode::SEPARATOR, // SDL_SCANCODE_SEPARATOR = 159,
	Scancode::OUT, // SDL_SCANCODE_OUT = 160,
	Scancode::OPER, // SDL_SCANCODE_OPER = 161,
	Scancode::CLEARAGAIN, // SDL_SCANCODE_CLEARAGAIN = 162,
	Scancode::CRSEL, // SDL_SCANCODE_CRSEL = 163,
	Scancode::EXSEL, // SDL_SCANCODE_EXSEL = 164,
	Scancode::UNKNOWN, // Unassigned = 165
	Scancode::UNKNOWN, // Unassigned = 166
	Scancode::UNKNOWN, // Unassigned = 167
	Scancode::UNKNOWN, // Unassigned = 168
	Scancode::UNKNOWN, // Unassigned = 169
	Scancode::UNKNOWN, // Unassigned = 170
	Scancode::UNKNOWN, // Unassigned = 171
	Scancode::UNKNOWN, // Unassigned = 172
	Scancode::UNKNOWN, // Unassigned = 173
	Scancode::UNKNOWN, // Unassigned = 174
	Scancode::UNKNOWN, // Unassigned = 175
	Scancode::KP_00, // SDL_SCANCODE_KP_00 = 176,
	Scancode::KP_000, // SDL_SCANCODE_KP_000 = 177,
	Scancode::THOUSANDSSEPARATOR, // SDL_SCANCODE_THOUSANDSSEPARATOR = 178,
	Scancode::DECIMALSEPARATOR, // SDL_SCANCODE_DECIMALSEPARATOR = 179,
	Scancode::CURRENCYUNIT, // SDL_SCANCODE_CURRENCYUNIT = 180,
	Scancode::CURRENCYSUBUNIT, // SDL_SCANCODE_CURRENCYSUBUNIT = 181,
	Scancode::KP_LEFTPAREN, // SDL_SCANCODE_KP_LEFTPAREN = 182,
	Scancode::KP_RIGHTPAREN, // SDL_SCANCODE_KP_RIGHTPAREN = 183,
	Scancode::KP_LEFTBRACE, // SDL_SCANCODE_KP_LEFTBRACE = 184,
	Scancode::KP_RIGHTBRACE, // SDL_SCANCODE_KP_RIGHTBRACE = 185,
	Scancode::KP_TAB, // SDL_SCANCODE_KP_TAB = 186,
	Scancode::KP_BACKSPACE, // SDL_SCANCODE_KP_BACKSPACE = 187,
	Scancode::KP_A, // SDL_SCANCODE_KP_A = 188,
	Scancode::KP_B, // SDL_SCANCODE_KP_B = 189,
	Scancode::KP_C, // SDL_SCANCODE_KP_C = 190,
	Scancode::KP_D, // SDL_SCANCODE_KP_D = 191,
	Scancode::KP_E, // SDL_SCANCODE_KP_E = 192,
	Scancode::KP_F, // SDL_SCANCODE_KP_F = 193,
	Scancode::KP_XOR, // SDL_SCANCODE_KP_XOR = 194,
	Scancode::KP_POWER, // SDL_SCANCODE_KP_POWER = 195,
	Scancode::KP_PERCENT, // SDL_SCANCODE_KP_PERCENT = 196,
	Scancode::KP_LESS, // SDL_SCANCODE_KP_LESS = 197,
	Scancode::KP_GREATER, // SDL_SCANCODE_KP_GREATER = 198,
	Scancode::KP_AMPERSAND, // SDL_SCANCODE_KP_AMPERSAND = 199,
	Scancode::KP_DBLAMPERSAND, // SDL_SCANCODE_KP_DBLAMPERSAND = 200,
	Scancode::KP_VERTICALBAR, // SDL_SCANCODE_KP_VERTICALBAR = 201,
	Scancode::KP_DBLVERTICALBAR, // SDL_SCANCODE_KP_DBLVERTICALBAR = 202,
	Scancode::KP_COLON, // SDL_SCANCODE_KP_COLON = 203,
	Scancode::KP_HASH, // SDL_SCANCODE_KP_HASH = 204,
	Scancode::KP_SPACE, // SDL_SCANCODE_KP_SPACE = 205,
	Scancode::KP_AT, // SDL_SCANCODE_KP_AT = 206,
	Scancode::KP_EXCLAM, // SDL_SCANCODE_KP_EXCLAM = 207,
	Scancode::KP_MEMSTORE, // SDL_SCANCODE_KP_MEMSTORE = 208,
	Scancode::KP_MEMRECALL, // SDL_SCANCODE_KP_MEMRECALL = 209,
	Scancode::KP_MEMCLEAR, // SDL_SCANCODE_KP_MEMCLEAR = 210,
	Scancode::KP_MEMADD, // SDL_SCANCODE_KP_MEMADD = 211,
	Scancode::KP_MEMSUBTRACT, // SDL_SCANCODE_KP_MEMSUBTRACT = 212,
	Scancode::KP_MEMMULTIPLY, // SDL_SCANCODE_KP_MEMMULTIPLY = 213,
	Scancode::KP_MEMDIVIDE, // SDL_SCANCODE_KP_MEMDIVIDE = 214,
	Scancode::KP_PLUSMINUS, // SDL_SCANCODE_KP_PLUSMINUS = 215,
	Scancode::KP_CLEAR, // SDL_SCANCODE_KP_CLEAR = 216,
	Scancode::KP_CLEARENTRY, // SDL_SCANCODE_KP_CLEARENTRY = 217,
	Scancode::KP_BINARY, // SDL_SCANCODE_KP_BINARY = 218,
	Scancode::KP_OCTAL, // SDL_SCANCODE_KP_OCTAL = 219,
	Scancode::KP_DECIMAL, // SDL_SCANCODE_KP_DECIMAL = 220,
	Scancode::KP_HEXADECIMAL, // SDL_SCANCODE_KP_HEXADECIMAL = 221,
	Scancode::UNKNOWN, // Unassigned = 222
	Scancode::UNKNOWN, // Unassigned = 223
	Scancode::LCTRL, // SDL_SCANCODE_LCTRL = 224,
	Scancode::LSHIFT, // SDL_SCANCODE_LSHIFT = 225,
	Scancode::LALT, // SDL_SCANCODE_LALT = 226,
	Scancode::LGUI, // SDL_SCANCODE_LGUI = 227,
	Scancode::RCTRL, // SDL_SCANCODE_RCTRL = 228,
	Scancode::RSHIFT, // SDL_SCANCODE_RSHIFT = 229,
	Scancode::RALT, // SDL_SCANCODE_RALT = 230,
	Scancode::RGUI, // SDL_SCANCODE_RGUI = 231,
	Scancode::UNKNOWN, // Unassigned = 232
	Scancode::UNKNOWN, // Unassigned = 233
	Scancode::UNKNOWN, // Unassigned = 234
	Scancode::UNKNOWN, // Unassigned = 235
	Scancode::UNKNOWN, // Unassigned = 236
	Scancode::UNKNOWN, // Unassigned = 237
	Scancode::UNKNOWN, // Unassigned = 238
	Scancode::UNKNOWN, // Unassigned = 239
	Scancode::UNKNOWN, // Unassigned = 240
	Scancode::UNKNOWN, // Unassigned = 241
	Scancode::UNKNOWN, // Unassigned = 242
	Scancode::UNKNOWN, // Unassigned = 243
	Scancode::UNKNOWN, // Unassigned = 244
	Scancode::UNKNOWN, // Unassigned = 245
	Scancode::UNKNOWN, // Unassigned = 246
	Scancode::UNKNOWN, // Unassigned = 247
	Scancode::UNKNOWN, // Unassigned = 248
	Scancode::UNKNOWN, // Unassigned = 249
	Scancode::UNKNOWN, // Unassigned = 250
	Scancode::UNKNOWN, // Unassigned = 251
	Scancode::UNKNOWN, // Unassigned = 252
	Scancode::UNKNOWN, // Unassigned = 253
	Scancode::UNKNOWN, // Unassigned = 254
	Scancode::UNKNOWN, // Unassigned = 255
	Scancode::UNKNOWN, // Unassigned = 256
	Scancode::MODE, // SDL_SCANCODE_MODE = 257,
	Scancode::AUDIONEXT, // SDL_SCANCODE_AUDIONEXT = 258,
	Scancode::AUDIOPREV, // SDL_SCANCODE_AUDIOPREV = 259,
	Scancode::AUDIOSTOP, // SDL_SCANCODE_AUDIOSTOP = 260,
	Scancode::AUDIOPLAY, // SDL_SCANCODE_AUDIOPLAY = 261,
	Scancode::AUDIOMUTE, // SDL_SCANCODE_AUDIOMUTE = 262,
	Scancode::MEDIASELECT, // SDL_SCANCODE_MEDIASELECT = 263,
	Scancode::WWW, // SDL_SCANCODE_WWW = 264,
	Scancode::MAIL, // SDL_SCANCODE_MAIL = 265,
	Scancode::CALCULATOR, // SDL_SCANCODE_CALCULATOR = 266,
	Scancode::COMPUTER, // SDL_SCANCODE_COMPUTER = 267,
	Scancode::AC_SEARCH, // SDL_SCANCODE_AC_SEARCH = 268,
	Scancode::AC_HOME, // SDL_SCANCODE_AC_HOME = 269,
	Scancode::AC_BACK, // SDL_SCANCODE_AC_BACK = 270,
	Scancode::AC_FORWARD, // SDL_SCANCODE_AC_FORWARD = 271,
	Scancode::AC_STOP, // SDL_SCANCODE_AC_STOP = 272,
	Scancode::AC_REFRESH, // SDL_SCANCODE_AC_REFRESH = 273,
	Scancode::AC_BOOKMARKS, // SDL_SCANCODE_AC_BOOKMARKS = 274,
	Scancode::BRIGHTNESSDOWN, // SDL_SCANCODE_BRIGHTNESSDOWN = 275,
	Scancode::BRIGHTNESSUP, // SDL_SCANCODE_BRIGHTNESSUP = 276,
	Scancode::DISPLAYSWITCH, // SDL_SCANCODE_DISPLAYSWITCH = 277,
	Scancode::KBDILLUMTOGGLE, // SDL_SCANCODE_KBDILLUMTOGGLE = 278,
	Scancode::KBDILLUMDOWN, // SDL_SCANCODE_KBDILLUMDOWN = 279,
	Scancode::KBDILLUMUP, // SDL_SCANCODE_KBDILLUMUP = 280,
	Scancode::EJECT, // SDL_SCANCODE_EJECT = 281,
	Scancode::SLEEP, // SDL_SCANCODE_SLEEP = 282,
	Scancode::APP1, // SDL_SCANCODE_APP1 = 283,
	Scancode::APP2, // SDL_SCANCODE_APP2 = 284,
	Scancode::AUDIOREWIND, // SDL_SCANCODE_AUDIOREWIND = 285,
	Scancode::AUDIOFASTFORWARD, // SDL_SCANCODE_AUDIOFASTFORWARD = 286,
};

} // namespace Emergent

