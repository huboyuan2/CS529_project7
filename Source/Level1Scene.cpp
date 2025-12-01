//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.cpp
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
//#include "SandboxScene.h"
//#include "DemoScene.h"
//#include "Scene.h"
#include "SceneSystem.h"
#include "CheatSystem.h"
#include "Vector2D.h"
#include "Scene.h"
#include "Entity.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Animation.h"
#include "Physics.h"
#include "SpriteSource.h"
#include "EntityFactory.h"
#include "Transform.h"
#include "MeshLibrary.h"
#include "SpriteSourceLibrary.h"
#include "TileSetLibrary.h"
#include "TileMap.h"
#include "TileSet.h"
#include "TileMapData.h"

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
	const float Level1Scene::groundHeight = -250.0f;
	const float Level1Scene::moveVelocity = 500.0f;
	const float Level1Scene::jumpVelocity = 1000.0f;
	const Vector2D Level1Scene::gravityNormal = { 0.0f, -1500.0f };
	const Vector2D Level1Scene::gravityNone = { 0.0f, 0.0f };
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	Level1Scene::Level1Scene()
		: Scene("Level1Scene")
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

	void Level1Scene::Load()
	{
		Stream jsonstream= Stream("Data/Level1.json");
		if(jsonstream.IsValid())
		{
			jsonstream.Read("NumLives", numLives);
			LoggingSystem::Verbose("{}: Lives: {}",Name(), numLives);
			mesh1x1 = new Mesh();
			mesh1x1->BuildQuad(1.0f, 1.0f, "1x1");
			spriteSourcePlanet = new SpriteSource();
			spriteSourcePlanet->LoadTexture(1, 1, "Assets/PlanetTexture.png");
			mesh3x3 = new Mesh();
			mesh3x3->BuildQuad(1.0f / 3.0f, 1.0f / 3.0f, "Mesh3x3");
			mesh16x8 = new Mesh();
			mesh16x8->BuildQuad(1.0f / 16.0f, 1.0f / 8.0f, "Mesh16x8");
			spriteSourceMonkeyIdle = new SpriteSource();
			spriteSourceMonkeyIdle->LoadTexture(1, 1, "Assets/MonkeyIdle.png");
			spriteSourceMonkeyJump = new SpriteSource();
			spriteSourceMonkeyJump->LoadTexture(1, 1, "Assets/MonkeyJump.png");
			spriteSourceMonkeyWalk = new SpriteSource();
			spriteSourceMonkeyWalk->LoadTexture(3, 3, "Assets/MonkeyWalk.png");
			spriteSourceFontSheet = new SpriteSource();
			spriteSourceFontSheet->LoadTexture(16, 8, "Assets/Roboto_Mono_black.png");
		}
			
	}


	bool Level1Scene::Initialize()
	{
		entityPlanet = EntityFactory::Build("PlanetBounce");
		entityTileMap = EntityFactory::Build("Level1Entity");
		if(entityTileMap!=nullptr)
		{
			AddEntity(entityTileMap);
		}
		entityMonkey = EntityFactory::Build("Monkey");
		if (entityMonkey)
		{	
			monkeyState = Invalid;
			SetMonkeyState(entityMonkey, Idle);
		}
		entityLives = EntityFactory::Build("MonkeyLivesText");
		if (entityLives)
		{	
			Sprite* livesSprite = entityLives->Get<Sprite>();
			if (livesSprite)
			{
				livesSprite->SetSpriteSource(spriteSourceFontSheet);
				livesSprite->SetMesh(mesh16x8);
				livesSprite->SetText("Lives: " + std::to_string(numLives));
			}
		}
		if (!entityPlanet)
			return false;
		else
		{
			Sprite* planetSprite = entityPlanet->Get<Sprite>();
			if (planetSprite)
			{
				planetSprite->SetSpriteSource(spriteSourcePlanet);
				planetSprite->SetMesh(mesh1x1);
			}
			const DGL_Color DGL_Color_White = { 1.0f, 1.0f, 1.0f, 1.0f };
			DGL_Graphics_SetBackgroundColor(&DGL_Color_White);
			DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
		}
		return true;
	}

	void Level1Scene::Update(float dt)
	{

		//MovementController();
		//if (!isActive)
		//{
			//LoggingSystem::Verbose("{}: Failed to create planet entity", Name());
			//return;
		//}
			MovementController();
			//entityPlanet->Update(dt);
			entityMonkey->Update(dt);

			TileMap* tilemap = entityTileMap->Get<TileMap>();
			if (tilemap)
			{
				// 使用新的碰撞响应方法
				int collisionFlags = tilemap->CheckAndResolveCollision(entityMonkey, 30.0f, 45.0f);

				// 视觉反馈（可选）
				if (TileMapData::HasCollision(collisionFlags))
				{
					//entityMonkey->Get<Sprite>()->Alpha(0.5f);
					//SetMonkeyState(entityMonkey, Idle); 
					if (TileMapData::IsStanding(collisionFlags))
					{
						if (monkeyState == Jump)
						SetMonkeyState(entityMonkey, Idle);
					}
					if (TileMapData::IsTouchingCeiling(collisionFlags))
					{
						if (monkeyState == Jump)
						SetMonkeyState(entityMonkey, Idle);
					}
				}
				/*else
				{
					entityMonkey->Get<Sprite>()->Alpha(1.0f);
				}*/
			}

			BounceController(entityPlanet);
			entityPlanet->Update(dt);
			if (IsColliding(entityMonkey, entityPlanet))
			{
				entityLives->Get<Sprite>()->SetText("Lives: " + std::to_string(numLives));
				numLives -= 1;
				if (numLives <= 0)
				{
					//Shutdown();
					//Unload();
					SceneSystem::SetPendingScene<Level2Scene>();
				}
				else {
					Restart();
				}
			}
			entityLives->Update(dt);
		
	}

	void Level1Scene::Render() const
	{
		if (entityTileMap)
			entityTileMap->Render();
		if(entityPlanet)
			entityPlanet->Render();
		if(entityMonkey)
			entityMonkey->Render();
		if(entityLives)
			entityLives->Render();

	}

	void Level1Scene::Shutdown()
	{
		//isActive = false;
		delete entityPlanet;
		entityPlanet = nullptr;
		delete entityMonkey;
		entityMonkey = nullptr;
		delete entityLives;
		entityLives = nullptr;
		//DGL_Graphics_FreeMesh(const_cast<DGL_Mesh*>(mesh1x1->GetMeshResource()));
	}

	void Level1Scene::Unload()
	{
		delete mesh1x1;
		mesh1x1 = nullptr;
		delete spriteSourcePlanet;
		spriteSourcePlanet = nullptr;
		delete mesh3x3;
		mesh3x3 = nullptr;
		delete mesh16x8;
		mesh16x8 = nullptr;
		delete spriteSourceMonkeyIdle;
		spriteSourceMonkeyIdle = nullptr;
		delete spriteSourceMonkeyJump;
		spriteSourceMonkeyJump = nullptr;
		delete spriteSourceMonkeyWalk;
		spriteSourceMonkeyWalk = nullptr;
		delete spriteSourceFontSheet;
		spriteSourceFontSheet = nullptr;
		MeshLibrary::DeleteAll();
		SpriteSourceLibrary::DeleteAll();
		TileSetLibrary::DeleteAll();
	}

	void Level1Scene::MovementController()
	{
		Transform* transform = entityMonkey->Get<Transform>();
		const Vector2D& position = transform->Translation();
		Physics* physics = entityMonkey->Get<Physics>();

		TileMap* tilemap = entityTileMap->Get<TileMap>();
		/*bool iscollide = tilemap->CheckCollisionAt(transform->Translation().x+32, transform->Translation().y+32, 1, 1);*/
		/*bool iscollide = tilemap->CheckCollisionAt(transform->Translation().x, transform->Translation().y, 30, 30);
		if (iscollide) {
			entityMonkey->Get<Sprite>()->Alpha(0.5f);
		}
		else
		{
			entityMonkey->Get<Sprite>()->Alpha(1.0f);
		}*/

		const Vector2D& velocity = physics->Velocity();
		if (DGL_Input_KeyDown(VK_LEFT))
		{	
			physics->Velocity({ -moveVelocity, velocity.y });
			if(monkeyState != Jump)
			{
				SetMonkeyState(entityMonkey, Walk);
			}
		}
		else if (DGL_Input_KeyDown(VK_RIGHT))
		{
			physics->Velocity({ moveVelocity, velocity.y });
			if (monkeyState != Jump)
			{
				SetMonkeyState(entityMonkey, Walk);
			}
		}
		else
		{
			physics->Velocity({ 0.0f, velocity.y });
			if (monkeyState != Jump)
			{
				SetMonkeyState(entityMonkey, Idle);
			}
			//transform->Translation({ position.x + 200, groundHeight + 100 });
		}
		if(DGL_Input_KeyTriggered(VK_UP))
		{
			physics->Velocity({ velocity.x, jumpVelocity });
			physics->Acceleration(gravityNormal);
			if(monkeyState != Jump)
			{
				SetMonkeyState(entityMonkey, Jump);
			}
		}
		/*if (DGL_Input_KeyTriggered(VK_DOWN))
		{
			transform->Translation({ position.x + 200, groundHeight + 100 });
		}*/
		if(position.y < groundHeight)
		{
			transform->Translation({ position.x,groundHeight });
			physics->Velocity({ velocity.x, 0.0f });
			physics->Acceleration(gravityNone);
			SetMonkeyState(entityMonkey, Idle);
			//numLives -= 1;
			//if (numLives <= 0)
			//{
			//	//Shutdown();
			//	//Unload();
			//	SceneSystem::SetPendingScene<Level2Scene>();
			//}				
		}
	}
	void Level1Scene::BounceController(Entity* entity) const
	{
		Transform* transform = entity->Get<Transform>();
		const Vector2D& position = transform->Translation();
		Physics* physics = entity->Get<Physics>();
		const Vector2D& velocity = physics->Velocity();
		if (position.x < -wallDistance)
		{
			transform->Translation({ -wallDistance, position.y });
			physics->Velocity({ -velocity.x, velocity.y });
		}
		else if (position.x > wallDistance)
		{
			transform->Translation({ wallDistance, position.y });
			physics->Velocity({ -velocity.x, velocity.y });
		}
		if (position.y <= groundHeight)
		{
			transform->Translation({ position.x, groundHeight+groundHeight- position.y });
			physics->Velocity({ velocity.x, -velocity.y });
		}
	}
	void Level1Scene::SetMonkeyState(Entity* entity, MonkeyStates state)
	{
		/*MonkeyStates* monkeyState = entity->Get<MonkeyStates>();
		if (monkeyState)
		{
			*monkeyState = state;
		}*/
		if (monkeyState != state)
		{
			monkeyState = state;
			Sprite* sprite = entity->Get<Sprite>();
			Animation* animation = entity->Get<Animation>();
			if (sprite&&animation)
			{
				switch (state)
				{
				case Idle:
					sprite->SetMesh(mesh1x1);
					sprite->SetSpriteSource(spriteSourceMonkeyIdle);
					animation->Play(1,0.0f,false);
					break;
				case Walk:
					sprite->SetSpriteSource(spriteSourceMonkeyWalk);
					sprite->SetMesh(mesh3x3);
					animation->Play(8, 0.05f, true);
					break;
				case Jump:
					sprite->SetSpriteSource(spriteSourceMonkeyJump);
					sprite->SetMesh(mesh1x1);
					animation->Play(1, 0.0f, false);
					break;
				default:
					break;
				}
			}
		}
	}
	bool Level1Scene::IsColliding(const Entity* entityA, const Entity* entityB) const
	{
		Transform* transformA = entityA->Get<Transform>();
		Transform* transformB = entityB->Get<Transform>();
		if (transformA && transformB)
		{
			const Vector2D& posA = transformA->Translation();
			const Vector2D& posB = transformB->Translation();
			float squareDistance = posA.SquareDistance(posB);
			return squareDistance <= CheckSquareDistance;
		}
		return false;
	}
#pragma endregion Private Functions

}	// namespace