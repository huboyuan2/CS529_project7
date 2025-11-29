//------------------------------------------------------------------------------
//
// File Name:	TileSetLibrary.cpp
// Author(s):	21222
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template class for a new object.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "TileSetLibrary.h"
#include "Object.h"
#include "Stream.h"
#include "TileSet.h"

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

	std::unordered_map<std::string, const TileSet*> TileSetLibrary::tileSets;

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	TileSetLibrary::TileSetLibrary(void)
		: Object()
	{
	}

	//--------------------------------------------------------------------------

	TileSetLibrary::~TileSetLibrary(void)
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
	const TileSet* TileSetLibrary::Build(const std::string& tileSetName)
	{
		
		auto it = tileSets.find(tileSetName);
		if (it != tileSets.end())
		{
			return it->second;
		}

		//build bew TileSet
		std::string filePath = "./Data/TileSets/" + tileSetName + ".json";
		Stream stream(filePath);

		if (stream.IsValid() && stream.Contains("TileSet"))
		{
			TileSet* newTileSet = new TileSet();
			newTileSet->Read(stream);
			tileSets[tileSetName] = newTileSet;
			return newTileSet;
		}

		return nullptr;
	}

	const TileSet* TileSetLibrary::Find(const std::string& tileSetName)
	{
		auto it = tileSets.find(tileSetName);
		return (it != tileSets.end()) ? it->second : nullptr;
	}

	void TileSetLibrary::DeleteAll()
	{
		for (auto& pair : tileSets)
		{
			delete pair.second;
		}
		tileSets.clear();
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace