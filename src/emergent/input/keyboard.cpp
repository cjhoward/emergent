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

#include <emergent/input/keyboard.hpp>
#include <emergent/input/input-event.hpp>
#include <emergent/input/input-manager.hpp>
#include <emergent/utility/event-dispatcher.hpp>

namespace Emergent
{

const char* Keyboard::getScancodeName(Scancode scancode)
{
	static const char* names[] =
	{
		NULL, // UNKNOWN
		"A", // A
		"B", // B
		"C", // C
		"D", // D
		"E", // E
		"F", // F
		"G", // G
		"H", // H
		"I", // I
		"J", // J
		"K", // K
		"L", // L
		"M", // M
		"N", // N
		"O", // O
		"P", // P
		"Q", // Q
		"R", // R
		"S", // S
		"T", // T
		"U", // U
		"V", // V
		"W", // W
		"X", // X
		"Y", // Y
		"Z", // Z
		"1", // ONE
		"2", // TWO
		"3", // THREE
		"4", // FOUR
		"5", // FIVE
		"6", // SIX
		"7", // SEVEN
		"8", // EIGHT
		"9", // NINE
		"0", // ZERO
		"Return", // RETURN
		"Escape", // ESCAPE
		"Backspace", // BACKSPACE
		"Tab", // TAB
		"Space", // SPACE
		"-", // MINUS
		"=", // EQUALS
		"[", // LEFTBRACKET
		"]", // RIGHTBRACKET
		"\\", // BACKSLASH
		"#", // NONUSHASH
		";", // SEMICOLON
		"'", // APOSTROPHE
		"`", // GRAVE
		",", // COMMA
		".", // PERIOD
		"/", // SLASH
		"CapsLock", // CAPSLOCK
		"F1", // F1
		"F2", // F2
		"F3", // F3
		"F4", // F4
		"F5", // F5
		"F6", // F6
		"F7", // F7
		"F8", // F8
		"F9", // F9
		"F10", // F10
		"F11", // F11
		"F12", // F12
		"PrintScreen", // PRINTSCREEN
		"ScrollLock", // SCROLLLOCK
		"Pause", // PAUSE
		"Insert", // INSERT
		"Home", // HOME
		"PageUp", // PAGEUP
		"Delete", // DELETE
		"End", // END
		"PageDown", // PAGEDOWN
		"Right", // RIGHT
		"Left", // LEFT
		"Down", // DOWN
		"Up", // UP
		"Numlock", // NUMLOCKCLEAR
		"Keypad /", // KP_DIVIDE
		"Keypad *", // KP_MULTIPLY
		"Keypad -", // KP_MINUS
		"Keypad +", // KP_PLUS
		"Keypad Enter", // KP_ENTER
		"Keypad 1", // KP_1
		"Keypad 2", // KP_2
		"Keypad 3", // KP_3
		"Keypad 4", // KP_4
		"Keypad 5", // KP_5
		"Keypad 6", // KP_6
		"Keypad 7", // KP_7
		"Keypad 8", // KP_8
		"Keypad 9", // KP_9
		"Keypad 0", // KP_0
		"Keypad .", // KP_PERIOD
		NULL, // NONUSBACKSLASH
		"Application", // APPLICATION
		"Power", // POWER
		"Keypad =", // KP_EQUALS
		"F13", // F13
		"F14", // F14
		"F15", // F15
		"F16", // F16
		"F17", // F17
		"F18", // F18
		"F19", // F19
		"F20", // F20
		"F21", // F21
		"F22", // F22
		"F23", // F23
		"F24", // F24
		"Execute", // EXECUTE
		"Help", // HELP
		"Menu", // MENU
		"Select", // SELECT
		"Stop", // STOP
		"Again", // AGAIN
		"Undo", // UNDO
		"Cut", // CUT
		"Copy", // COPY
		"Paste", // PASTE
		"Find", // FIND
		"Mute", // MUTE
		"VolumeUp", // VOLUMEUP
		"VolumeDown", // VOLUMEDOWN
		NULL, // KP_COMMA
		NULL, // KP_EQUALSAS400
		NULL, // LOCKINGCAPSLOCK
		"Keypad ,", // LOCKINGNUMLOCK
		"Keypad = (AS400)", // LOCKINGSCROLLLOCK
		NULL, // INTERNATIONAL1
		NULL, // INTERNATIONAL2
		NULL, // INTERNATIONAL3
		NULL, // INTERNATIONAL4
		NULL, // INTERNATIONAL5
		NULL, // INTERNATIONAL6
		NULL, // INTERNATIONAL7
		NULL, // INTERNATIONAL8
		NULL, // INTERNATIONAL9
		NULL, // LANG1
		NULL, // LANG2
		NULL, // LANG3
		NULL, // LANG4
		NULL, // LANG5
		NULL, // LANG6
		NULL, // LANG7
		NULL, // LANG8
		NULL, // LANG9
		"AltErase", // ALTERASE
		"SysReq", // SYSREQ
		"Cancel", // CANCEL
		"Clear", // CLEAR
		"Prior", // PRIOR
		"Return", // RETURN2
		"Separator", // SEPARATOR
		"Out", // OUT
		"Oper", // OPER
		"Clear / Again", // CLEARAGAIN
		"CrSel", // CRSEL
		"ExSel", // EXSEL
		"Keypad 00", // KP_00
		"Keypad 000", // KP_000
		"ThousandsSeparator", // THOUSANDSSEPARATOR
		"DecimalSeparator", // DECIMALSEPARATOR
		"CurrencyUnit", // CURRENCYUNIT
		"CurrencySubUnit", // CURRENCYSUBUNIT
		"Keypad (", // KP_LEFTPAREN
		"Keypad )", // KP_RIGHTPAREN
		"Keypad {", // KP_LEFTBRACE
		"Keypad }", // KP_RIGHTBRACE
		"Keypad Tab", // KP_TAB
		"Keypad Backspace", // KP_BACKSPACE
		"Keypad A", // KP_A
		"Keypad B", // KP_B
		"Keypad C", // KP_C
		"Keypad D", // KP_D
		"Keypad E", // KP_E
		"Keypad F", // KP_F
		"Keypad XOR", // KP_XOR
		"Keypad ^", // KP_POWER
		"Keypad %", // KP_PERCENT
		"Keypad <", // KP_LESS
		"Keypad >", // KP_GREATER
		"Keypad &", // KP_AMPERSAND
		"Keypad &&", // KP_DBLAMPERSAND
		"Keypad |", // KP_VERTICALBAR
		"Keypad ||", // KP_DBLVERTICALBAR
		"Keypad :", // KP_COLON
		"Keypad #", // KP_HASH
		"Keypad Space", // KP_SPACE
		"Keypad @", // KP_AT
		"Keypad !", // KP_EXCLAM
		"Keypad MemStore", // KP_MEMSTORE
		"Keypad MemRecall", // KP_MEMRECALL
		"Keypad MemClear", // KP_MEMCLEAR
		"Keypad MemAdd", // KP_MEMADD
		"Keypad MemSubtract", // KP_MEMSUBTRACT
		"Keypad MemMultiply", // KP_MEMMULTIPLY
		"Keypad MemDivide", // KP_MEMDIVIDE
		"Keypad +/-", // KP_PLUSMINUS
		"Keypad Clear", // KP_CLEAR
		"Keypad ClearEntry", // KP_CLEARENTRY
		"Keypad Binary", // KP_BINARY
		"Keypad Octal", // KP_OCTAL
		"Keypad Decimal", // KP_DECIMAL
		"Keypad Hexadecimal", // KP_HEXADECIMAL
		"Left Ctrl", // LCTRL
		"Left Shift", // LSHIFT
		"Left Alt", // LALT
		"Left GUI", // LGUI
		"Right Ctrl", // RCTRL
		"Right Shift", // RSHIFT
		"Right Alt", // RALT
		"Right GUI", // RGUI
		"ModeSwitch", // MODE
		"AudioNext", // AUDIONEXT
		"AudioPrev", // AUDIOPREV
		"AudioStop", // AUDIOSTOP
		"AudioPlay", // AUDIOPLAY
		"AudioMute", // AUDIOMUTE
		"MediaSelect", // MEDIASELECT
		"WWW", // WWW
		"Mail", // MAIL
		"Calculator", // CALCULATOR
		"Computer", // COMPUTER
		"AC Search", // AC_SEARCH
		"AC Home", // AC_HOME
		"AC Back", // AC_BACK
		"AC Forward", // AC_FORWARD
		"AC Stop", // AC_STOP
		"AC Refresh", // AC_REFRESH
		"AC Bookmarks", // AC_BOOKMARKS
		"BrightnessDown", // BRIGHTNESSDOWN
		"BrightnessUp", // BRIGHTNESSUP
		"DisplaySwitch", // DISPLAYSWITCH
		"KBDIllumToggle", // KBDILLUMTOGGLE
		"KBDIllumDown", // KBDILLUMDOWN
		"KBDIllumUp", // KBDILLUMUP
		"Eject", // EJECT
		"Sleep", // SLEEP
		"App1", // APP1
		"App2", // APP2
		"AudioRewind", // AUDIOREWIND
		"AudioFastForward", // AUDIOFASTFORWARD
	};

	return names[static_cast<std::size_t>(scancode)];
};

Keyboard::Keyboard(InputManager* inputManager, const std::string& name):
	InputDevice(inputManager, name)
{}

Keyboard::~Keyboard()
{}

void Keyboard::press(Scancode scancode)
{
	KeyPressedEvent event;
	event.keyboard = this;
	event.scancode = scancode;

	getInputManager()->getEventDispatcher()->queue(event);
}

void Keyboard::release(Scancode scancode)
{
	KeyReleasedEvent event;
	event.keyboard = this;
	event.scancode = scancode;

	getInputManager()->getEventDispatcher()->queue(event);
}

} // namespace Emergent

