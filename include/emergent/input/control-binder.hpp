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

#ifndef EMERGENT_INPUT_CONTROL_BINDER_HPP
#define EMERGENT_INPUT_CONTROL_BINDER_HPP

#include <emergent/input/input-event.hpp>
#include <emergent/utility/event-handler.hpp>

namespace Emergent
{

class Control;

/**
 * Binds controls to input events.
 *
 * @ingroup input
 */
class ControlBinder:
	public EventHandler<KeyPressedEvent>,
	public EventHandler<MouseButtonPressedEvent>,
	public EventHandler<MouseWheelScrolledEvent>,
	public EventHandler<GamepadButtonPressedEvent>,
	public EventHandler<GamepadAxisMovedEvent>
{
public:
	/// Creates a control binder.
	ControlBinder();

	/// Destroys a control binder.
	~ControlBinder();

	/**
	 * Binds a control to an input event.
	 *
	 * @param control Control to bind.
	 */
	void bind(Control* control);

	/**
	 * Returns true if the control binder is still binding a control.
	 */
	bool isBinding() const;

private:
	virtual void handleEvent(const KeyPressedEvent& event);
	virtual void handleEvent(const MouseButtonPressedEvent& event);
	virtual void handleEvent(const MouseWheelScrolledEvent& event);
	virtual void handleEvent(const GamepadButtonPressedEvent& event);
	virtual void handleEvent(const GamepadAxisMovedEvent& event);

	Control* control;
};

inline bool ControlBinder::isBinding() const
{
	return (control != nullptr);
}

} // namespace Emergent

#endif // EMERGENT_INPUT_CONTROL_BINDER_HPP

