//------------------------------------------------------------------------------
//
// File Name:	PlatformSystem.h
// Author(s):	Doug Schilling (dschilling)
// Course:		CS529F25
// Project:		Project 0
// Purpose:		System for implementing Windows platform-specific functionality.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <sal.h>
#include <Windows.h>

#include "System.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:

	// Typedefs:

	// Class Definition:
	class PlatformSystem : public System
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		PlatformSystem(HINSTANCE appInstance, int show);

		~PlatformSystem(void) override;

		// Public Static Functions:
	public:
		// Check if the glfw window is closing.
		static bool IsWindowClosing();

		// Make the window handle accessible to other systems.
		static HWND WindowHandle() { return instance->windowHandle; }

		// Public Functions:
	public:

		// Public Event Handlers
	public:
		// Message event handler.
		//bool HandleMessage(const Message& message) override;

		// Private Static Functions:
	private:
		// @brief This callback function is called every time the application receives a message from the OS.
		// @brief [NOTE: Callback functions are typically class methods (i.e. static), to avoid the implicit "this" parameter,
		//    when the caller doesn't know, or care, which object will handle the event. ]
		static LRESULT WindowsCallback(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);

		// Private Functions:
	private:
		// @brief Initialize the system.
		//
		// @return bool = true if initialization successful, otherwise false.
		bool Initialize() override;

		// @brief Update the system each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// Private Static Constants:
	private:
		static unsigned const MAX_LOADSTRING = 32;

		// Private Static Variables:
	private:
		static PlatformSystem* instance;

		static wchar_t appTitle[MAX_LOADSTRING];

		// Private Variables:
	private:
		// Handle to the current instance of the application.
		HINSTANCE	appInstance;

		// Specifies how the application's main window should be displayed (e.g., minimized, maximized, or normal).
		bool		showWindow;

		// Handle to the application's window.
		HWND windowHandle{};
	};

}	// namespace