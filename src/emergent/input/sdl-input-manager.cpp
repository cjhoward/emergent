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
#include <emergent/input/scancode.hpp>
#include <iostream>

namespace Emergent
{

const Scancode SDLInputManager::scancodeTable[285] =
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
	Scancode::UNKNOWN, // Unassigned = 49
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
	Scancode::UNKNOWN, // Unassigned = 130
	Scancode::UNKNOWN, // Unassigned = 131
	Scancode::UNKNOWN, // Unassigned = 132
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
};

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
					Scancode scancode = Scancode::UNKNOWN;
					if (event.key.keysym.scancode <= SDL_SCANCODE_APP2)
					{
						scancode = scancodeTable[event.key.keysym.scancode];
					}

					keyboard->press(scancode);
					break;
				}
			}
			
			case SDL_KEYUP:
			{
				if (event.key.repeat == 0)
				{
					Scancode scancode = Scancode::UNKNOWN;
					if (event.key.keysym.scancode <= SDL_SCANCODE_APP2)
					{
						scancode = scancodeTable[event.key.keysym.scancode];
					}

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
		Scancode scancode = Scancode::UNKNOWN;
		if (event.key.keysym.scancode <= SDL_SCANCODE_APP2)
		{
			scancode = scancodeTable[event.key.keysym.scancode];
		}

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
