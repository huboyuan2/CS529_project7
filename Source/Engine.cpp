//------------------------------------------------------------------------------
//
// File Name:	Engine.cpp
// Author(s):	Doug Schilling (dschilling)
// Course:		CS529F25
// Project:		Project 0
// Purpose:		The core engine is a container of systems.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <cassert>

#include "DGL.h"
#include "Random.h"
#include "Engine.h"
#include "LoggingSystem.h"
#include "Object.h"
#include "System.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	//------------------------------------------------------------------------------
	// Public Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Static Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Private Static Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Private Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Private Static Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Constructors/Destructors:
	//------------------------------------------------------------------------------

#pragma region Constructors

	Engine::Engine(void)
		: Object()
		, systems()
	{
	}

	//------------------------------------------------------------------------------

	Engine::~Engine(void)
	{
	}

#pragma endregion Constructors

	//------------------------------------------------------------------------------
	// Public Static Functions:
	//------------------------------------------------------------------------------

#pragma region Public Static Functions

#pragma endregion Public Static Functions

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

#pragma region Public Functions

	void Engine::AddSystem(System* system)
	{
		LoggingSystem::Verbose("Engine: Add System: {}", system->Name());

		// Verify that a valid system was specified.
		assert(system && "AddSystem Error: Invalid system specified.");

		// Add the new system to the systems container.
		systems.push_back(system);
	}

	bool Engine::Initialize()
	{
		LoggingSystem::Verbose("Engine: Initialize");
		Random::Initialize();
		bool success = true;
		for (auto system : systems)
		{
			LoggingSystem::Verbose("Engine: Initialize {}", system->Name());
			success &= system->Initialize();
		}
		return success;
	}

	void Engine::Update(float dt)
	{
		LoggingSystem::Verbose("Engine: Update");

		for (auto system : systems)
		{
			// This message has been deliberately set to debug level, instead of verbose,
			//   as these messages are a bit too "noisy" for the purposes of the course.
			LoggingSystem::Debug("Engine: Update {}", system->Name());
			system->Update(dt);
		}
	}

	void Engine::Render() const
	{
		LoggingSystem::Verbose("Engine: Render");

		// Start the draw process for the current frame.
		DGL_Graphics_StartDrawing();

		// Render all systems.
		for (auto system : systems)
		{
			// This message has been deliberately set to debug level, instead of verbose,
			//   as these messages are a bit too "noisy" for the purposes of the course.
			LoggingSystem::Debug("Engine: Render {}", system->Name());
			system->Render();
		}

		// Complete the draw process for the current frame.
		DGL_Graphics_FinishDrawing();
	}

	void Engine::Shutdown()
	{
		LoggingSystem::Verbose("Engine: Shutdown");

		// Delete all of the systems in the systems container.
		while (!systems.empty())
		{
			// Delete the last system in the systems container.
			System* system = systems.back();
			LoggingSystem::Verbose("Engine: Shutdown {}", system->Name());
			systems.pop_back();
			delete system;
		}
	}

#pragma endregion Public Functions

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace