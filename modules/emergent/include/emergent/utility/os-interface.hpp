/*
 * Copyright (C) 2017-2019  Christopher J. Howard
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

#ifndef EMERGENT_UTILITY_OS_INTERFACE_HPP
#define EMERGENT_UTILITY_OS_INTERFACE_HPP

namespace Emergent
{

class DeviceManager;
class EventDispatcher;
class Mouse;
class Window;
class WindowManager;

/**
 * Abstract base class for abstraction layers which interface with the OS.
 *
 * @ingroup utility
 */
class OSInterface
{
public:
	/**
	 * Creates an OS interface.
	 *
	 * @param eventDispatcher Event dispatcher through which OS events will be routed.
	 */
	OSInterface(EventDispatcher* eventDispatcher);

	/// Destroys an OS interface.
	virtual ~OSInterface();

	/**
	 * Routes OS events through the event dispatcher.
	 */
	virtual void routeEvents() = 0;

	/**
	 * Starts generating text input events when the keys are pressed.
	 */
	virtual void startTextInput() = 0;
	
	/**
	 * Stops generating text input events.
	 */
	virtual void stopTextInput() = 0;

	/**
	 * Sets the clipboard text.
	 *
	 * @param contents UTF-8 encoded text.
	 */
	virtual void setClipboardText(const char* text) = 0;

	/**
	 * Returns the UTF-8 encoded clipboard text, or nullptr if the clipboard is empty.
	 */
	virtual const char* getClipboardText() const = 0;

	/// Returns the event dispatcher through which OS events are routed.
	const EventDispatcher* getEventDispatcher() const;

	/// @copydoc OSInterface::getEventDispatcher() const
	EventDispatcher* getEventDispatcher();

	/// Returns the device manager for this OS interface.
	const DeviceManager* getDeviceManager() const;

	/// @copydoc OSInterface::getDeviceManager() const
	DeviceManager* getDeviceManager();

	/// Returns the window manager for this OS interface.
	const WindowManager* getWindowManager() const;

	/// @copydoc OSInterface::getWindowManager() const
	WindowManager* getWindowManager();

protected:
	EventDispatcher* eventDispatcher;
	DeviceManager* deviceManager;
	WindowManager* windowManager;

	void updateMousePosition(Mouse* mouse, int x, int y);

private:
	friend class Mouse;
	friend class Window;
	friend class WindowManager;

	/**
	 * Opens a window.
	 *
	 * @param title UTF-8 encoded title string.
	 * @param x X-coordinate of the window position, when in windowed mode.
	 * @param y Y-coordinate of the window position, when in windowed mode.
	 * @param width Width of the window, when in windowed mode.
	 * @param height Height of the window, when in windowed mode.
	 * @param fullscreen Whether fullscreen mode is enabled. If fullscreen mode is enabled, the dimensions of the window will be equal to the dimensions of the parent display.
	 * @param flags Window creation flags.
	 * @return OS interface-specific window data.
	 */
	virtual void* openWindow(const char* title, int x, int y, int width, int height, bool fullscreen, unsigned int flags) = 0;
	virtual void closeWindow(Window* window) = 0;
	virtual void setWindowTitle(Window* window, const char* title) = 0;
	virtual void setWindowPosition(Window* window, int x, int y) = 0;
	virtual void setWindowDimensions(Window* window, int width, int height) = 0;
	virtual void setWindowResizable(Window* window, bool resizable) = 0;
	virtual void setWindowBordered(Window* window, bool bordered) = 0;
	virtual void setWindowFullscreen(Window* window, bool fullscreen) = 0;
	virtual void setWindowVSync(Window* window, bool vsync) = 0;
	virtual void setWindowInputGrabbed(Window* window, bool grabbed) = 0;
	virtual void makeWindowCurrent(Window* window) = 0;
	virtual void swapWindowBuffers(Window* window) = 0;
	virtual void warpMousePosition(Window* window, int x, int y) = 0;
	virtual void setRelativeMouseMode(Mouse* mouse, bool enabled) = 0;
	virtual void setMouseVisible(Mouse* mouse, bool visible) = 0;
};

inline const EventDispatcher* OSInterface::getEventDispatcher() const
{
	return eventDispatcher;
}

inline EventDispatcher* OSInterface::getEventDispatcher()
{
	return eventDispatcher;
}

inline const DeviceManager* OSInterface::getDeviceManager() const
{
	return deviceManager;
}

inline DeviceManager* OSInterface::getDeviceManager()
{
	return deviceManager;
}

inline const WindowManager* OSInterface::getWindowManager() const
{
	return windowManager;
}

inline WindowManager* OSInterface::getWindowManager()
{
	return windowManager;
}

} // namespace Emergent

#endif // EMERGENT_UTILITY_OS_INTERFACE_HPP

