//------------------------------------------------------------------------------
//
// File Name:	SceneSystem.cpp
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 0
// Purpose:		System for managing scenes.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <cassert>

#include "LoggingSystem.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "StubScene.h"
#include "DemoScene.h"
#include "Level1Scene.h"
#include "System.h"
#include "AsteroidsScene.h"
#include "OmegaScene.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

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

	//------------------------------------------------------------------------------
	// Private Static Variables:
	//------------------------------------------------------------------------------

	SceneSystem* SceneSystem::instance = nullptr;

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	SceneSystem::SceneSystem(void)
		: System("SceneSystem")
	{
		// Raise an assert if this system has already been created.
		assert(instance == nullptr);

		// Store this system's instance for use by static functions.
		instance = this;
	}

	//--------------------------------------------------------------------------

	SceneSystem::~SceneSystem(void)
	{
	}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions

#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

	bool SceneSystem::Initialize()
	{
		// Set the starting (Default) scene.
		//SetPendingScene<StubScene>();
		//SetPendingScene<DemoScene>();
		SetPendingScene<Level1Scene>();
		//SetPendingScene<AsteroidsScene>();
		//SetPendingScene<OmegaScene>();
		// Return true if the initialization completed successfully.
		return true;
	}

	void SceneSystem::Update(float dt)
	{
		// Check for a scene change.
		if (IsSceneChanging())
		{
			// Shutdown the active scene.
			CallShutdown();


			if (IsSceneRestarting())
			{
				ClearRestartFlag();
			}
			else
			{
				// Unload(Old)ActiveScene
				CallUnload();
				// Change the active scene.
			// [NOTE: Any existing active scene is automatically deleted.]
				activeScene = std::move(pendingScene);
			//Load(New)ActiveScene
				CallLoad();
			}
			//// Change the active scene.
			//// [NOTE: Any existing active scene is automatically deleted.]
			//activeScene = std::move(pendingScene);

			// Initialize the new active scene.
			CallInitialize();
		}

		// Update the active scene.
		CallUpdate(dt);
	}

	void SceneSystem::Render() const
	{
		CallRender();
	}

	// Avoid throwing a null-reference exception when there is no active scene.
	inline void SceneSystem::CallLoad() const
	{
		if (activeScene)
		{
			// TODO: Call LoggingSystem::Verbose, passing the format string "{}: Load" and the name of the active scene.
			LoggingSystem::Verbose("{0}: Load", activeScene->Name());
			activeScene->Load();
		}
	}

	inline void SceneSystem::CallInitialize() const
	{
		if (activeScene)
		{
			// TODO: Call LoggingSystem::Verbose, passing the format string "{}: Initialize" and the name of the active scene.
			LoggingSystem::Verbose("{0}: Initialize", activeScene->Name());
			activeScene->Initialize();
		}
	}

	inline void SceneSystem::CallUpdate(float dt) const
	{
		if (activeScene)
		{
			// TODO: Call LoggingSystem::Verbose, passing the format string "{}: Update" and the name of the active scene.
			LoggingSystem::Verbose("{0}: Update", activeScene->Name());
			activeScene->Update(dt);
		}
	}

	inline void SceneSystem::CallRender() const
	{
		if (activeScene)
		{
			// TODO: Call LoggingSystem::Verbose, passing the format string "{}: Render" and the name of the active scene.
			LoggingSystem::Verbose("{0}: Render", activeScene->Name());
			activeScene->Render();
		}
	}

	inline void SceneSystem::CallShutdown() const
	{
		if (activeScene)
		{
			// TODO: Call LoggingSystem::Verbose, passing the format string "{}: Shutdown" and the name of the active scene.
			LoggingSystem::Verbose("{0}: Shutdown",activeScene->Name());
			activeScene->Shutdown();
		}
	}

	inline void SceneSystem::CallUnload() const
	{
		if (activeScene)
		{
			// TODO: Call LoggingSystem::Verbose, passing the format string "{}: Unload" and the name of the active scene.
			LoggingSystem::Verbose("{0}: Unload", activeScene->Name());
			activeScene->Unload();
		}
	}

#pragma endregion Private Functions

}	// namespace