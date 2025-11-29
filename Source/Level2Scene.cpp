//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template class for a new scene.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <Windows.h>
#include "Stream.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "DemoScene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Physics.h"
#include "Sprite.h"

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

	Level2Scene::Level2Scene()
		: Scene("Level2Scene")
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

	void Level2Scene::Load()
	{
		//Stream jsonstream = Stream("Data/Level2.json");
		//if (jsonstream.IsValid())
		//{
		//	jsonstream.Read("NumLives", numLives);
		//	LoggingSystem::Verbose("{}: Lives: {}", Name(), numLives);
		//	// Load the JSON data
		//}
		meshSpaceship = new Mesh();
		meshSpaceship->BuildSpaceship();
	
	}

	bool Level2Scene::Initialize()
	{
		//Stream jsonstream = Stream("Data/Level2.json");
		//if (jsonstream.IsValid())
		//{
		//	jsonstream.Read("NumHealth", numHealth);
		//	LoggingSystem::Verbose("{}: Health: {}", Name(), numHealth);
		//	// Load the JSON data
		//}
		entitySpaceship = EntityFactory::Build("SpaceshipHoming");
		if (entitySpaceship)
		{	
			
			Sprite* spaceshipSprite = entitySpaceship->Get<Sprite>();
			if(spaceshipSprite)
			{
				spaceshipSprite->SetMesh(meshSpaceship);
			}
			const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
			DGL_Graphics_SetBackgroundColor(&DGL_Color_Black);
			DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
		}
	/*	if (!meshSpaceship)
		{
			LoggingSystem::Error("{}: Failed to create spaceship mesh", Name());
			return false;
		}
		if (!entitySpaceship)
		{
			LoggingSystem::Error("{}: Failed to create spaceship entity", Name());
			return false;
		}*/
		return true;
	}

	void Level2Scene::Update(float dt)
	{
		// Tell the compiler that the 'dt' variable is unused.
		//UNREFERENCED_PARAMETER(dt);
		//numHealth -= 1;
		//LoggingSystem::Verbose("{}: Health: {}", Name(), numHealth);
		//if (numHealth <= 0)
		//{
		//	numLives -= 1;
		//	LoggingSystem::Verbose("{}: Lives: {}", Name(), numLives);
		//	if (numLives > 0)
		//	{
		//		Restart();
		//	}
		//	else {
		//		SceneSystem::SetPendingScene<SandboxScene>();
		//		SceneSystem::EndScene();
		//	}


		//	// NOTE: This call causes the engine to exit immediately.
		//	//   Make sure to remove it when you are ready to test out a new scene.
		//	
		//}
		if (entitySpaceship)
		{
			MovementController(entitySpaceship);

			entitySpaceship->Update(dt);
		}
	}

	void Level2Scene::MovementController(Entity* entity)
	{
		Transform* transform = entitySpaceship->Get<Transform>();
		const Vector2D& position = transform->Translation();
		Physics* physics = entitySpaceship->Get<Physics>();

		if (transform && physics)
		{
			DGL_Vec2 mousePos = DGL_Input_GetMousePosition();
			DGL_Vec2 worldPos = DGL_Camera_ScreenCoordToWorld(&mousePos);
			Vector2D direction = { worldPos.x - position.x, worldPos.y - position.y };
			direction.Normalize();
			float rad = direction.ToAngleRad();
			transform->Rotation(rad);
			direction.Scale(spaceshipSpeed);
			physics->Velocity(direction);
		}
		Sprite* spaceshipSprite = entitySpaceship->Get<Sprite>();
		if (spaceshipSprite)
		{
			if (DGL_Input_KeyTriggered('Z'))
			{
				spaceshipSprite->Alpha(0.5f);
			}
			else if (DGL_Input_KeyTriggered('X'))
			{
				spaceshipSprite->Alpha(1.0f);
			}
		}
		//if (DGL_Input_KeyTriggered('1'))
		//{
		//	SceneSystem::SetPendingScene<Level1Scene>();
		//}
		//else if (DGL_Input_KeyTriggered('2'))
		//{
		//	Restart();			
		//}
		//else if (DGL_Input_KeyTriggered('9'))
		//{
		//	SceneSystem::SetPendingScene<SandboxScene>();
		//}
		//// Add code to restart the level when the ??key is triggered (when the key changes state from not pressed to pressed).
		//if (DGL_Input_KeyTriggered('0'))
		//{
		//	SceneSystem::SetPendingScene<DemoScene>();
		//}
	}

	void Level2Scene::Render() const
	{
		if (entitySpaceship)
			entitySpaceship->Render();
	}

	void Level2Scene::Shutdown()
	{
		delete entitySpaceship;
		entitySpaceship = nullptr;
		
	}

	void Level2Scene::Unload()
	{
		delete meshSpaceship;
		meshSpaceship = nullptr;
	}

#pragma endregion Private Functions

}	// namespace