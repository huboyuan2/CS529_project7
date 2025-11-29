//------------------------------------------------------------------------------
//
// File Name:	Main.cpp
// Author(s):	Doug Schilling (dschilling)
// Course:		CS529F25
// Project:		Project 0
// Purpose:		Main entry point for the Windows application.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Windows.h"
#include <sal.h>

#include "DGL.h"

#include "Engine.h"
#include "LoggingSystem.h"
#include "PlatformSystem.h"
#include "CheatSystem.h"
#include "SceneSystem.h"
#include "ScoreSystem.h"

using namespace CS529;

//------------------------------------------------------------------------------
// Main Entry:
//------------------------------------------------------------------------------

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    Engine engine;

    // Construct all of the systems and add them to the engine.
    engine.AddSystem(new LoggingSystem("CS529", "Trace.log"));
    engine.AddSystem(new PlatformSystem(hInstance, nCmdShow));
#ifdef _DEBUG
	engine.AddSystem(new CheatSystem());
#endif
    engine.AddSystem(new SceneSystem());
    engine.AddSystem(new ScoreSystem());
    // Initialize the systems once they have all been constructed.
    bool isRunning = engine.Initialize();

    // Change in time (in seconds) since the last frame.
    float dt = 0.0f;

    // MAIN LOOP:
    while (isRunning)
    {
        // Update the current frame.
        engine.Update(dt);

        // Render the current frame.
        engine.Render();

        if (!DGL_System_DoesWindowExist() || !SceneSystem::IsRunning())
        {
            isRunning = false;
        }

        dt = (float)DGL_System_GetDeltaTime();
    }

    // Shutdown the engine.
    engine.Shutdown();

    return 0;
}




