//------------------------------------------------------------------------------
//
// File Name:	SpriteSourceLibrary.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 5
// Purpose:		This class is responsible for managing a library of sprite sources.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string>
#include <unordered_map>

#include "Object.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class SpriteSource;
	class Stream;

	// Typedefs:

	// Class Definition:
	class SpriteSourceLibrary : public Object
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		SpriteSourceLibrary(void);

		// All objects need a virtual destructor to have their destructor called 
		virtual ~SpriteSourceLibrary(void) override;

		// Public Static Functions:
	public:
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
		static const SpriteSource* Build(const std::string& spriteSourceName);

		// @brief Attempt to find the requested SpriteSource.
		// @brief [NOTE: This function has been made public for testing purposes.]
		//
		// @param spriteSourceName = The name of the SpriteSource to find.
		//
		// @return const SpriteSource* = Pointer to the SpriteSource, if found, otherwise nullptr.
		static const SpriteSource* Find(const std::string spriteSourceName);

		// @brief Delete all SpriteSources in the library.
		// @brief [HINT: Make sure to erase or clear the container when done deleting the SpriteSources.]
		static void DeleteAll();

		// Public Functions:
	public:

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:
		static std::unordered_map<std::string, const SpriteSource*> spriteSources;

		// Private Variables:
	private:
	};

}	// namespace