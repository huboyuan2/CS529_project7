//------------------------------------------------------------------------------
//
// File Name:	TileMapData.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template for a new .cpp file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "TileMapData.h"
#include "Stream.h"
#include "SpriteSource.h"
#include "SpriteSourceLibrary.h"
#include "TileSet.h"
#include "TileSetLibrary.h"
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

	TileMapData::TileMapData(void)
		: rows(0)
		, cols(0)
		, tileSet(nullptr)
	{
	}

	TileMapData::~TileMapData(void)
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
	void TileMapData::Read(Stream& stream)
	{
		if (!stream.IsValid())
			return;

		stream.PushNode("TileMapData");


		stream.Read("Name", name);

		stream.Read("Rows", rows);
		stream.Read("Cols", cols);
		stream.Read("Scale", scale);
		stream.Read("MapBaseX", mapBaseX);
		stream.Read("MapBaseY", mapBaseY);
		std::string tileSetName;
		if (stream.Read("TileSet", tileSetName) && tileSetName != "")
		{
			tileSet = TileSetLibrary::Build(tileSetName);
		}

		//Read From a One dimensional Array
		if (stream.Contains("TileData"))
		{
			tileData.resize(rows * cols);
			stream.PushNode("TileData");

			stream.ReadArray("Tiles", [&, index = 0]() mutable {
				if (index < tileData.size())
				{
					unsigned tileIndex;
					stream.Read("Index", tileIndex);
					tileData[index++] = tileIndex;
				}
				});

			stream.PopNode();
		}

		stream.PopNode();
	}
	bool TileMapData::IsPassable(unsigned row, unsigned col) const
	{
		if (tileSet == nullptr)
			return true;
		if (row >= rows || col >= cols)
			return false;
		unsigned tileIndex = tileData[row * cols + col];
		return tileIndex == 0;
	/*	const SpriteSource* spriteSource = tileSet->GetSpriteSource(tileIndex);
		if (spriteSource == nullptr)
			return true;
		return spriteSource->IsPassable();*/
	}
	bool TileMapData::IsPassableAtWorldPos(float worldX, float worldY) const
	{
		float localX = worldX - mapBaseX;
		float localY = worldY - mapBaseY;
	
		unsigned col = static_cast<unsigned>(localX / (GetTileSet()->GetTileWidth() * scale));
		unsigned row = static_cast<unsigned>(localY / (GetTileSet()->GetTileHeight() * scale));

		return IsPassable(row, col);
	}

	int TileMapData::IsAreaPassable(float worldX, float worldY, float width, float height) const
	{
		float halfWidth = width * 0.5f;
		float halfHeight = height * 0.5f;

		int collisionFlags = HP_NONE;

		// 检测四个热点
		// 左上角
		if (!IsPassableAtWorldPos(worldX - halfWidth, worldY - halfHeight))
		{
			collisionFlags |= HP_TOP_LEFT;
		}

		// 右上角
		if (!IsPassableAtWorldPos(worldX + halfWidth, worldY - halfHeight))
		{
			collisionFlags |= HP_TOP_RIGHT;
		}

		// 左下角
		if (!IsPassableAtWorldPos(worldX - halfWidth, worldY + halfHeight))
		{
			collisionFlags |= HP_BOTTOM_LEFT;
		}

		// 右下角
		if (!IsPassableAtWorldPos(worldX + halfWidth, worldY + halfHeight))
		{
			collisionFlags |= HP_BOTTOM_RIGHT;
		}

		return collisionFlags;
	}
	int TileMapData::GetCollisionCount(int flags)
	{
		int count = 0;
		if (flags & HP_TOP_LEFT) ++count;
		if (flags & HP_TOP_RIGHT) ++count;
		if (flags & HP_BOTTOM_LEFT) ++count;
		if (flags & HP_BOTTOM_RIGHT) ++count;
		return count;
	}
	unsigned TileMapData::GetTileAt(unsigned row, unsigned col) const
	{
		if (row >= rows || col >= cols)
			return 0;
		return tileData[row * cols + col];
	}

	void TileMapData::SetTileAt(unsigned row, unsigned col, unsigned tileIndex)
	{
		if (row >= rows || col >= cols)
			return;
		tileData[row * cols + col] = tileIndex;
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace