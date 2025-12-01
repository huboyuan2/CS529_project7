//------------------------------------------------------------------------------
//
// File Name:	TileMap.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 2
// Purpose:		This component class is responsible for ...
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "TileMap.h"
#include "Component.h"
#include "Entity.h"
#include "DGL.h"
#include "Transform.h"
#include "Stream.h"
#include "LoggingSystem.h"
#include "Physics.h"
//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	TileMap::TileMap(void)
		: Component()
	{
	}

	TileMap::TileMap(const TileMap* other)
		: Component(other)
		, tileMapData(other ? other->tileMapData : nullptr)
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

	TileMap::~TileMap(void)
	{
	}

	void TileMap::Read(Stream& stream)
	{
		if (!stream.IsValid())
			return;

		stream.PushNode("TileMap");

		std::string mapDataName;
		if (stream.Read("TileMapData", mapDataName) && mapDataName != "")
		{
			TileMapData* loadedData = new TileMapData();
			Stream mapStream("./Data/TileMaps/" + mapDataName + ".json");
			if (mapStream.IsValid())
			{
				loadedData->Read(mapStream);
				/*Transform* transform =Parent()->Get<Transform>();
				loadedData->SetBaseX(transform->Translation().x);
				loadedData->SetBaseY(transform->Translation().y);*/
				tileMapData = loadedData;
			}
		}

		stream.PopNode();
		/*Transform* transform = Parent()->Get<Transform>();
		if (transform)
		{
			tileMapData->SetBaseX(transform->Translation().x);
			tileMapData->SetBaseY(transform->Translation().y);
		}*/
		
	}

	void TileMap::Render() const
	{
		Transform* transform = Parent() ? Parent()->Get<Transform>() : nullptr;
		if (!transform || !tileMapData)
			return;

		const TileSet* tileSet = tileMapData->GetTileSet();
		if (!tileSet)
			return;

		const Mesh* mesh = tileSet->GetMesh();
		if (!mesh)
			return;

		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		Matrix2D baseMatrix = transform->GetMatrix();

		// 获取 Tile 的实际尺寸（缩放后）
		float tileWorldWidth = tileSet->GetTileWidth() / 32.0f;  // 转换为世界单位
		float tileWorldHeight = tileSet->GetTileHeight() / 32.0f;

		for (unsigned row = 0; row < tileMapData->GetRows(); ++row)
		{
			for (unsigned col = 0; col < tileMapData->GetCols(); ++col)
			{
				unsigned tileIndex = tileMapData->GetTileAt(row, col);
				if (tileIndex == 0)
					continue;

				const SpriteSource* spriteSource = tileSet->GetSpriteSource(tileIndex);
				if (!spriteSource)
					continue;

				spriteSource->SetTextureOffset(0);
				Matrix2D offset;

				// fix:add 0.5 tile offset for the mesh centering
				offset.Translate(
					(col + 0.5f) * tileWorldWidth,   // add 0.5 tile offset for centering
					(row + 0.5f) * tileWorldHeight
				);

				Matrix2D tileMatrix = baseMatrix * offset;

				spriteSource->UseTexture();
				DGL_Graphics_SetCB_TransformMatrix(&tileMatrix);

				mesh->Render();
			}
		}
	}
	bool TileMap::CheckCollisionAt(float worldX, float worldY, float width, float height)
	{
		if (!tileMapData)
			return false;

		int collisionFlags = tileMapData->IsAreaPassable(worldX, worldY, width, height);

		if (TileMapData::HasCollision(collisionFlags))
		{
			LoggingSystem::Verbose("Collision: {} hot points",
				TileMapData::GetCollisionCount(collisionFlags));

			if (collisionFlags & HP_TOP_LEFT)
				LoggingSystem::Verbose("  - Top Left colliding");
			if (collisionFlags & HP_TOP_RIGHT)
				LoggingSystem::Verbose("  - Top Right colliding");
			if (collisionFlags & HP_BOTTOM_LEFT)
				LoggingSystem::Verbose("  - Bottom Left colliding");
			if (collisionFlags & HP_BOTTOM_RIGHT)
				LoggingSystem::Verbose("  - Bottom Right colliding");

			return true;
		}

		return false;
	}

	int TileMap::CheckAndResolveCollision(Entity* entity, float width, float height)
	{
		if (!entity || !tileMapData)
			return false;

		Transform* transform = entity->Get<Transform>();
		Physics* physics = entity->Get<Physics>();

		if (!transform || !physics)
			return false;

		const Vector2D& oldPos = physics->OldTranslation();
		const Vector2D& newPos = transform->Translation();

		// 获取碰撞标志
		int collisionFlags = tileMapData->IsAreaPassable(newPos.x, newPos.y, width, height);

		if (TileMapData::HasCollision(collisionFlags))
		{
			// 执行碰撞响应
			ResolveCollision(transform, physics, oldPos, newPos, width, height, collisionFlags);
			//return true;
		}
		return collisionFlags;
		//return false;
	}
	void TileMap::ResolveCollision(
		Transform* transform,
		Physics* physics,
		const Vector2D& oldPos,
		const Vector2D& newPos,
		float width,
		float height,
		int collisionFlags
	) const
	{
		Vector2D finalPos = newPos;
		Vector2D velocity = physics->Velocity();

		// 根据碰撞标志判断碰撞方向
		bool xBlocked = false;
		bool yBlocked = false;

		// 左墙碰撞（左侧热点碰撞且向左移动）
		if (TileMapData::IsTouchingLeftWall(collisionFlags) && velocity.x < 0.0f)
		{
			xBlocked = true;
			finalPos.x = oldPos.x;
			velocity.x = 0.0f;
		}

		// 右墙碰撞（右侧热点碰撞且向右移动）
		if (TileMapData::IsTouchingRightWall(collisionFlags) && velocity.x > 0.0f)
		{
			xBlocked = true;
			finalPos.x = oldPos.x;
			velocity.x = 0.0f;
		}

		// 地面碰撞（底部热点碰撞且向下移动）
		if (TileMapData::IsStanding(collisionFlags) && velocity.y > 0.0f)
		{
			yBlocked = true;
			finalPos.y = oldPos.y;
			velocity.y = 0.0f;

			LoggingSystem::Verbose("Player is STANDING");
		}

		// 天花板碰撞（顶部热点碰撞且向上移动）
		if (TileMapData::IsTouchingCeiling(collisionFlags) && velocity.y < 0.0f)
		{
			yBlocked = true;
			finalPos.y = oldPos.y;
			velocity.y = 0.0f;

			LoggingSystem::Verbose("Player hit CEILING");
		}

		// 应用修正
		transform->Translation(finalPos);
		physics->Velocity(velocity);
	}
#pragma endregion Public Functions
	 
	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace
