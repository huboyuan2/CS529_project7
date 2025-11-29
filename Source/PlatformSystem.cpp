//------------------------------------------------------------------------------
//
// File Name:	PlatformSystem.cpp
// Author(s):	Doug Schilling (dschilling)
// Course:		CS529F25
// Project:		Project 6
// Purpose:		System for implementing Windows platform-specific functionality.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <cassert>
#include <sal.h>
#include <Windows.h>

#include "DGL.h"

#include "LoggingSystem.h"
#include "PlatformSystem.h"
#include "SceneSystem.h"
#include "System.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// External Libraries
//------------------------------------------------------------------------------

#ifdef _DEBUG
#pragma comment (lib, "DGL_d.lib")
#else
#pragma comment (lib, "DGL.lib")
#endif

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	//--------------------------------------------------------------------------
	// Public Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Variables:
	//--------------------------------------------------------------------------

	PlatformSystem* PlatformSystem::instance = nullptr;

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	constexpr auto MAX_LOADSTRING = 32;

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	PlatformSystem::PlatformSystem(HINSTANCE appInstance, int showWindow)
		: System("PlatformSystem")
		, appInstance(appInstance)
		, showWindow(showWindow)
	{
		// Raise an assert if this system has already been created.
		assert(instance == nullptr);

		// Store this system's instance for use by static functions.
		instance = this;
	}

	//--------------------------------------------------------------------------

	PlatformSystem::~PlatformSystem(void)
	{
		// Shutdown the DigiPen Graphics Library (DGL).
		DGL_System_Exit();
	}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions

	// Check if the glfw window is closing.
	bool PlatformSystem::IsWindowClosing()
	{
		return !DGL_System_DoesWindowExist();
	}

#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Static Functions:
	//--------------------------------------------------------------------------

#pragma region Private Static Functions

	LRESULT CALLBACK PlatformSystem::WindowsCallback(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
	{
		// The DGL has custom handling for certain Windows events.
		int result;
		if (DGL_System_HandleWindowsMessage(message, wParam, lParam, &result))
			return result;

		// If the DGL did not handle the event, then invoke the default implementation.
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

#pragma endregion Private Static Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

	bool PlatformSystem::Initialize()
	{
		//----------------------------------------------------------------------
		// Initialize the DigiPen Graphics Library.
		//----------------------------------------------------------------------
		DGL_SysInitInfo initInfo = {};
		initInfo.mAppInstance = appInstance;
		initInfo.mShow = showWindow;
		initInfo.mWindowTitle = "CS529F25 Project 6 - Omega";
		initInfo.mWindowWidth = 1024;
		initInfo.mWindowHeight = 768;
		initInfo.mMaxFrameRate = 60;
		initInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
		initInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;
#ifdef _DEBUG
		initInfo.mCreateConsole = true;
#else
		initInfo.mCreateConsole = false;
#endif
		initInfo.pWindowsCallback = WindowsCallback;
		initInfo.mWindowIcon = 0; // IDI_DGLTEMPLATE;

		windowHandle = DGL_System_Init(&initInfo);
		if (windowHandle == NULL)
		{
			// Return false if the system was NOT initialized successfully.
			LoggingSystem::Error("PlatformSystem::Initialize Error: The DigiPen Graphics Library could not be initialized!");
			return false;
		}

#ifdef _DEBUG
		// Write a message to the console window.
		//LoggingSystem::Info("Starting %s\n", initInfo.mWindowTitle);
#endif

		// Set the default background color to bright green.
		// [NOTE: This is done intentionally to catch missing initialization steps.
		//    If you see a bright green screen, then you've probably missed a step.]
		const DGL_Color DGL_Color_Green = { 0.0f, 1.0f, 0.0f, 1.0f };
		DGL_Graphics_SetBackgroundColor(&DGL_Color_Green);

		return true;
	}

	void PlatformSystem::Update(float dt)
	{
		// Tell the compiler that the 'dt' variable is unused.
		UNREFERENCED_PARAMETER(dt);

		// Wait for the next frame.
		DGL_System_FrameControl();

		// Update the DGL system (Input, Windows events, etc.).
		DGL_System_Update();

		// Check if forcing the application to quit.
		if (DGL_Input_KeyTriggered(VK_ESCAPE) || !DGL_System_DoesWindowExist())
		{
			// The engine will automatically shutdown when there are no more active or pending scenes.
			LoggingSystem::Info("PlatformSystem::Update: Forced shutdown of the application");
			SceneSystem::EndScene();
		}
	}

#pragma endregion Private Functions

}	// namespace