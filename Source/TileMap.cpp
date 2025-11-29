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
				tileMapData = loadedData;
			}
		}

		stream.PopNode();
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
				offset.Translate(col * tileSet->GetTileWidth()/32, row * tileSet->GetTileHeight()/32);
				Matrix2D tileMatrix = baseMatrix * offset;

				spriteSource->UseTexture();
				DGL_Graphics_SetCB_TransformMatrix(&tileMatrix);

				mesh->Render();
			}
		}
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace
