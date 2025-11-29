//------------------------------------------------------------------------------
//
// File Name:	TileSet.cpp
// Author(s):	21222
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
#include "TileSet.h"
#include "Stream.h"
#include "SpriteSource.h"
#include "SpriteSourceLibrary.h"
#include "Mesh.h"
#include "MeshLibrary.h"
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

	TileSet::TileSet(void)
		: tileWidth(32)
		, tileHeight(32)
	{
	}

	//--------------------------------------------------------------------------

	TileSet::~TileSet(void)
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
	void TileSet::Read(Stream& stream)
	{
		if (!stream.IsValid())
			return;

		stream.PushNode("TileSet");

		stream.Read("Name", name);

		stream.Read("TileWidth", tileWidth);
		stream.Read("TileHeight", tileHeight);

		std::string meshName;
		if (stream.Read("Mesh", meshName) && meshName != "")
		{
			//mesh = MeshLibrary::Build(meshName);
			mesh = MeshLibrary::BuildQuad(1,1);
		}

		// read multiple SpriteSources
		if (stream.Contains("SpriteSources"))
		{
			stream.ReadArray("SpriteSources", [this, &stream]() {
				std::string spriteSourceName;
				stream.Read("Name", spriteSourceName);

				if (spriteSourceName != "")
				{
					const SpriteSource* spriteSource = SpriteSourceLibrary::Build(spriteSourceName);
					if (spriteSource)
					{
						spriteSources.push_back(spriteSource);
					}
				}
				});
		}

		stream.PopNode();
	}

	const SpriteSource* TileSet::GetSpriteSource(unsigned index) const
	{
		if (index >= spriteSources.size() || index == 0)
			return nullptr;
		return spriteSources[index - 1];
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace