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

#include <emergent/input/control-profile.hpp>
#include <emergent/input/control.hpp>
#include <emergent/input/keyboard.hpp>
#include <emergent/input/mouse.hpp>
#include <emergent/input/gamepad.hpp>
#include <emergent/utility/device-manager.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace Emergent
{

ControlProfile::ControlProfile()
{}

void ControlProfile::registerControl(const std::string& name, Control* control)
{
	controls[name] = control;
}

bool ControlProfile::save(const std::string& filename)
{
	// Open control profile
	std::ofstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << std::string("Failed to open control profile \"") << filename << std::string("\"") << std::endl;
		return false;
	}
	
	for (auto it = controls.begin(); it != controls.end(); ++it)
	{
		Control* control = it->second;
		const std::list<std::pair<Keyboard*, Scancode>>* boundKeys = control->getBoundKeys();
		const std::list<std::pair<Mouse*, int>>* boundMouseButtons = control->getBoundMouseButtons();
		const std::list<std::pair<Mouse*, MouseWheelAxis>>* boundMouseWheelAxes = control->getBoundMouseWheelAxes();
		const std::list<std::pair<Gamepad*, int>>* boundGamepadButtons = control->getBoundGamepadButtons();
		const std::list<std::tuple<Gamepad*, int, bool>>* boundGamepadAxes = control->getBoundGamepadAxes();
		
		for (auto boundKey: *boundKeys)
		{
			int key = static_cast<int>(boundKey.second);
			file << std::string("control\t") << it->first << std::string("\tkeyboard\tkey\t") << key << '\n';
		}
		
		for (auto boundMouseButton: *boundMouseButtons)
		{
			int button = boundMouseButton.second;
			file << std::string("control\t") << it->first << std::string("\tmouse\tbutton\t") << button << '\n';
		}
		
		for (auto boundMouseWheelAxis: *boundMouseWheelAxes)
		{
			MouseWheelAxis axis = boundMouseWheelAxis.second;
			
			file << std::string("control\t") << it->first << std::string("\tmouse\twheel\t");
			if (axis == MouseWheelAxis::POSITIVE_X)
				file << std::string("+x");
			else if (axis == MouseWheelAxis::NEGATIVE_X)
				file << std::string("-x");
			else if (axis == MouseWheelAxis::POSITIVE_Y)
				file << std::string("+y");
			else if (axis == MouseWheelAxis::NEGATIVE_Y)
				file << std::string("-y");
			else
				file << std::string("unknown");
			file << '\n';
		}
		
		for (auto boundGamepadButton: *boundGamepadButtons)
		{
			const std::string& gamepadName = boundGamepadButton.first->getName();
			int button = boundGamepadButton.second;
			file << std::string("control\t") << it->first << std::string("\tgamepad\t") << gamepadName << std::string("\tbutton\t") << button << '\n';
		}
		
		for (auto boundGamepadAxis: *boundGamepadAxes)
		{
			const std::string& gamepadName = std::get<0>(boundGamepadAxis)->getName();
			int axis = std::get<1>(boundGamepadAxis);
			bool negative = std::get<2>(boundGamepadAxis);
			
			std::stringstream axisstream;
			if (negative)
				axisstream << std::string("-");
			else
				axisstream << std::string("+");
			axisstream << axis;
			
			file << std::string("control\t") << it->first << std::string("\tgamepad\t") << gamepadName << std::string("\taxis\t") << axisstream.str() << '\n';
		}
	}
	
	file.close();
	
	return true;
}

bool ControlProfile::load(const std::string& filename, DeviceManager* deviceManager)
{
	// Open control profile
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << std::string("Failed to open control profile \"") << filename << std::string("\"") << std::endl;
		return false;
	}
	
	// Read profile
	std::string line;
	while (file.good() && std::getline(file, line))
	{
		// Tokenize line (tab-delimeted)
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream linestream(line);
		while (std::getline(linestream, token, '\t'))
			tokens.push_back(token);
		
		if (tokens.empty() || tokens[0][0] == '#')
			continue;
		
		if (tokens[0] == "control" && tokens.size() >= 5)
		{
			// Use control name to get control pointer
			auto it = controls.find(tokens[1]);
			if (it == controls.end())
			{
				std::cerr << std::string("Attempted to load unregistered control \"") << tokens[1] << std::string("\" from control profile \"") << filename << std::string("\"") << std::endl;
				continue;
			}
			Control* control = it->second;
			
			// Find input device
			if (tokens[2] == "keyboard")
			{
				Keyboard* keyboard = deviceManager->getKeyboards()->front();
				
				if (tokens[3] == "key")
				{
					std::stringstream keystream(tokens[4]);
					int scancode = 0;
					keystream >> scancode;
					
					control->bindKey(keyboard, static_cast<Scancode>(scancode));
				}
				else
				{
					std::cerr << std::string("Invalid line \"") << line << std::string("\" in control profile \"") << filename << std::string("\"") << std::endl;
				}
			}
			else if (tokens[2] == "mouse")
			{
				Mouse* mouse = deviceManager->getMice()->front();
				
				if (tokens[3] == "button")
				{
					std::stringstream buttonstream(tokens[4]);
					int button = -1;
					buttonstream >> button;
					
					control->bindMouseButton(mouse, button);
				}
				else if (tokens[3] == "wheel")
				{
					MouseWheelAxis axis;
					if (tokens[4] == "+x")
						axis = MouseWheelAxis::POSITIVE_X;
					else if (tokens[4] == "-x")
						axis = MouseWheelAxis::NEGATIVE_X;
					else if (tokens[4] == "+y")
						axis = MouseWheelAxis::POSITIVE_Y;
					else if (tokens[4] == "-y")
						axis = MouseWheelAxis::NEGATIVE_Y;
					else
					{
						std::cerr << std::string("Invalid line \"") << line << std::string("\" in control profile \"") << filename << std::string("\"") << std::endl;
						continue;
					}
					
					control->bindMouseWheelAxis(mouse, axis);
				}
				else
				{
					std::cerr << std::string("Invalid line \"") << line << std::string("\" in control profile \"") << filename << std::string("\"") << std::endl;
					continue;
				}
			}
			else if (tokens[2] == "gamepad")
			{
				if (tokens.size() != 6)
				{
					std::cerr << std::string("Invalid line \"") << line << std::string("\" in control profile \"") << filename << std::string("\"") << std::endl;
					continue;
				}
				
				Gamepad* gamepad = deviceManager->getGamepad(tokens[3]);
				if (!gamepad)
				{
					gamepad = new Gamepad(deviceManager, tokens[3]);
					gamepad->setDisconnected(true);
					deviceManager->registerGamepad(gamepad);
				}
				
				if (tokens[4] == "button")
				{
					std::stringstream buttonstream(tokens[5]);
					int button = -1;
					buttonstream >> button;
					
					control->bindGamepadButton(gamepad, button);
				}
				else if (tokens[4] == "axis")
				{
					bool negative = (tokens[5][0] == '-');
					
					std::stringstream axisstream(tokens[5].substr(1, tokens[5].length() - 1));
					int axis = -1;
					axisstream >> axis;
					
					control->bindGamepadAxis(gamepad, axis, negative);
				}
				else
				{
					std::cerr << std::string("Invalid line \"") << line << std::string("\" in control profile \"") << filename << std::string("\"") << std::endl;
					continue;
				}
			}
			else
			{
				std::cerr << std::string("Unsupported input device \"") << tokens[3] << std::string("\" in control profile \"") << filename << std::string("\"") << std::endl;
				continue;
			}
		}
	}
	
	file.close();
	
	return true;
}

void ControlProfile::update()
{
	for (auto it = controls.begin(); it != controls.end(); ++it)
	{
		it->second->update();
	}
}

void ControlProfile::setCallbacksEnabled(bool enabled)
{
	for (auto it = controls.begin(); it != controls.end(); ++it)
	{
		it->second->setCallbacksEnabled(enabled);
	}
}

} // namespace Emergent

