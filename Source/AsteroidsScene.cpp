//------------------------------------------------------------------------------
//
// File Name:	AsteroidsScene.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 2
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
#include "EntityFactory.h"
#include "EntityContainer.h"
#include "AsteroidsScene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "MeshLibrary.h"
#include "SpriteSourceLibrary.h"
#include "ScoreSystem.h"
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

	AsteroidsScene::AsteroidsScene()
		: Scene("AsteroidsScene"), asteroidSpawnCount(asteroidSpawnInitial)
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

	void AsteroidsScene::Load()
	{
		ScoreSystem::Instance().NewGame();
		asteroidSpawnCount = asteroidSpawnInitial;
	}
	/// <summary>
	/// oAsteroidsScene::Initialize:
	/*Build a ¡°Spaceship¡± entity.
		If the entity was created successfully,
		Add the entity to the scene.
		AsteroidsScene::Initialize:
	Add a call to UpdateEntities.*/
	/// </summary>
	/// <returns></returns>
	bool AsteroidsScene::Initialize()
	{
		ScoreSystem& scoresys = ScoreSystem::Instance();

		/*scoresys.NewGame();*/
		Entity* spaceship = EntityFactory::Build("Spaceship");
		if (spaceship != nullptr)
		{
			AddEntity(spaceship);
		}
		scoresys.Reset();
		Entity* AsteroidsScore = EntityFactory::Build("AsteroidsScore");
		Entity* AsteroidsHighScore = EntityFactory::Build("AsteroidsHighScore");
		Entity* AsteroidsWave = EntityFactory::Build("AsteroidsWaveCount");

		if (AsteroidsScore != nullptr)
		{
			AddEntity(AsteroidsScore);
		}
		if (AsteroidsHighScore != nullptr)
		{
			AddEntity(AsteroidsHighScore);
		}
		if (AsteroidsWave != nullptr)
		{
			AddEntity(AsteroidsWave);
		}
		//scoresys.IncreaseWave();
		const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
		DGL_Graphics_SetBackgroundColor(&DGL_Color_Black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
		return true;
	}

	void AsteroidsScene::Update(float dt)
	{
		Entity* asteroid = FindEntity("Asteroid");
		if (!asteroid)
		{
			//SpawnAsteroid();
			SpawnWave();
		}
		UpdateEntities(dt);
		CheckCollisions();
		// Tell the compiler that the 'dt' variable is unused.
		//UNREFERENCED_PARAMETER(dt);

		// NOTE: This call causes the engine to exit immediately.
		//   Make sure to remove it when you are ready to test out a new scene.
		// SceneSystem::EndScene();
	}

	void AsteroidsScene::Render() const
	{
		RenderEntities();
	}

	void AsteroidsScene::Shutdown()
	{
		DeleteEntities();
		EntityFactory::DeleteAll();
	}

	void AsteroidsScene::Unload()
	{
		MeshLibrary::DeleteAll();
		SpriteSourceLibrary::DeleteAll();
	}

	void AsteroidsScene::SpawnAsteroid()
	{
		Entity* asteroid = EntityFactory::Build("Asteroid");
		if (asteroid)
		{
			AddEntity(asteroid);
		}
	}
	void AsteroidsScene::SpawnWave()
	{
		for (unsigned i = 0; i < asteroidSpawnCount; ++i)
		{
			SpawnAsteroid();
		}
		if (asteroidSpawnCount < asteroidSpawnMaximum)
		{
			++asteroidSpawnCount;
		}
		ScoreSystem::Instance().IncreaseWave();
	}
#pragma endregion Private Functions

}	// namespace