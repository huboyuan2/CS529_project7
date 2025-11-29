//------------------------------------------------------------------------------
//
// File Name:	SpriteSourceLibrary.cpp
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
#include "SpriteSourceLibrary.h"
#include "SpriteSource.h"
#include "stream.h"
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
	std::unordered_map<std::string, const SpriteSource*> SpriteSourceLibrary::spriteSources;
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

	SpriteSourceLibrary::SpriteSourceLibrary(void)
	{
	}

	//--------------------------------------------------------------------------

	SpriteSourceLibrary::~SpriteSourceLibrary(void)
	{
	}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions

	// @brief Build the specified mesh or return an previously created instance of the mesh.
		// @brief Specific Steps:
		// @brief   Attempt to find the requested spriteSource.
		// @brief   If the spriteSource doesn't already exist,
		// @brief     Create a filePath by concatenating "./Data/SpriteSources/", spriteSourceName, and ".json".
		// @brief     Create a stream using the filePath.
		// @brief     If (the stream is valid) AND (the stream Contains("SpriteSource")),
		// @brief       Create a new instance of SpriteSource.
		// @brief       Read the contents of the SpriteSource from the stream.
		// @brief       Add the SpriteSource to the library.
		// @brief   Return the requested SpriteSource, if successful.
		//
		// @param meshName = The name of the SpriteSource to be created.
		//
		// @return SpriteSource* = Pointer to a new SpriteSource, if successful, otherwise nullptr.
	const SpriteSource* SpriteSourceLibrary::Build(const std::string& spriteSourceName)
	{
		if (spriteSources.contains(spriteSourceName))
		{
			return spriteSources[spriteSourceName];
		}
		else
		{
			SpriteSource* newspriteSource = new SpriteSource();
			std::string spriteSourcespath = "./Data/spriteSources/" + std::string(spriteSourceName) + ".json";
			Stream stream(spriteSourcespath);
			if (!stream.IsValid())
				return nullptr;
			if (stream.Contains("SpriteSource"))
			{
				newspriteSource->Read(stream);
				spriteSources.insert({ std::string(spriteSourceName), newspriteSource });
			}
			return newspriteSource;
		}
		return nullptr;
	}

	// @brief Attempt to find the requested SpriteSource.
	// @brief [NOTE: This function has been made public for testing purposes.]
	//
	// @param spriteSourceName = The name of the SpriteSource to find.
	//
	// @return const SpriteSource* = Pointer to the SpriteSource, if found, otherwise nullptr.
	const SpriteSource* SpriteSourceLibrary::Find(const std::string spriteSourceName)
	{
		if (spriteSources.contains(spriteSourceName))
		{
			return spriteSources[spriteSourceName];
		}
		else return nullptr;
	}

	// @brief Delete all SpriteSources in the library.
	// @brief [HINT: Make sure to erase or clear the container when done deleting the SpriteSources.]
	void SpriteSourceLibrary::DeleteAll()
	{

		for (auto spriteSource : spriteSources)
		{
			delete(spriteSource.second);
		}
		spriteSources.clear();
	}
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

#pragma endregion Private Functions

}	// namespace