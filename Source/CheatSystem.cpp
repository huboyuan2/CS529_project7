//------------------------------------------------------------------------------
//
// File Name:	CheatSystem.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template for a new .cpp file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "CheatSystem.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "DemoScene.h"
#include "Scene.h"
#include "SceneSystem.h"
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

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	CheatSystem::CheatSystem(void) : System("CheatSystem")
	{
	}

	//--------------------------------------------------------------------------

	CheatSystem::~CheatSystem(void)
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
	void CheatSystem::Update(float dt)
	{
		if (DGL_Input_KeyTriggered('1'))
		{
			SceneSystem::SetPendingScene<Level1Scene>();
		}
		else if (DGL_Input_KeyTriggered('2'))
		{
			SceneSystem::SetPendingScene<Level2Scene>();
		}
		else if (DGL_Input_KeyTriggered('3'))
		{
			SceneSystem::SetPendingScene<AsteroidsScene>();
		}
		else if (DGL_Input_KeyTriggered('4'))
		{
			SceneSystem::SetPendingScene<OmegaScene>();
		}
		else if (DGL_Input_KeyTriggered('9'))
		{
			SceneSystem::SetPendingScene<SandboxScene>();
		}
		// Add code to restart the level when the ??key is triggered (when the key changes state from not pressed to pressed).
		if (DGL_Input_KeyTriggered('0'))
		{
			SceneSystem::SetPendingScene<DemoScene>();
		}
	}
#pragma endregion Private Functions

}	// namespace