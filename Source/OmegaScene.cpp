//------------------------------------------------------------------------------
//
// File Name:	OmegaScene.cpp
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
#include "EntityFactory.h"
#include "EntityContainer.h"
#include "OmegaScene.h"
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

	OmegaScene::OmegaScene()
		: Scene("OmegaScene"), asteroidSpawnCount(asteroidSpawnInitial)
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

	void OmegaScene::Load()
	{
		ScoreSystem::Instance().NewGame();
		asteroidSpawnCount = asteroidSpawnInitial;
	}
	/// <summary>
	/// oOmegaScene::Initialize:
	/*Build a ¡°Spaceship¡± entity.
		If the entity was created successfully,
		Add the entity to the scene.
		OmegaScene::Initialize:
	Add a call to UpdateEntities.*/
	/// </summary>
	/// <returns></returns>
	bool OmegaScene::Initialize()
	{
		ScoreSystem& scoresys = ScoreSystem::Instance();
		Entity* arena = EntityFactory::Build("Arena");
		if (arena != nullptr)
		{
			AddEntity(arena);
		}
		/*scoresys.NewGame();*/
		Entity* spaceship = EntityFactory::Build("SpaceshipOmega");
		if (spaceship != nullptr)
		{
			AddEntity(spaceship);
		}
		scoresys.Reset();
		Entity* AsteroidsScore = EntityFactory::Build("OmegaScore");
		Entity* AsteroidsHighScore = EntityFactory::Build("OmegaHighScore");
		Entity* AsteroidsWave = EntityFactory::Build("OmegaWaveCount");

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

	void OmegaScene::Update(float dt)
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

	void OmegaScene::Render() const
	{
		RenderEntities();
	}

	void OmegaScene::Shutdown()
	{
		DeleteEntities();
		EntityFactory::DeleteAll();
	}

	void OmegaScene::Unload()
	{
		MeshLibrary::DeleteAll();
		SpriteSourceLibrary::DeleteAll();
	}

	void OmegaScene::SpawnAsteroid()
	{
		Entity* asteroid = EntityFactory::Build("Asteroid");
		if (asteroid)
		{
			AddEntity(asteroid);
		}
	}
	void OmegaScene::SpawnWave()
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