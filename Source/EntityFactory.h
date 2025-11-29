//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Static class for building new entities using deserialization.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string_view>

#include "EntityContainer.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class Entity;

	// Typedefs:

	// Class Definition:
	class EntityFactory
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	private:
		// @brief The EntityFactory is entirely static, so the constructor has been made private.
		EntityFactory(void);

		// Public Static Functions:
	public:
		// @brief Build a new entity using deserialization.
		// 
		// @brief Specific Steps (UPDATED):
		// @brief   Attempt to get an archetype entity from the archetypes container.
		// @brief   If the archetype does not exist,
		// @brief     Create a filePath by concatenating "./Data/Archetypes/", entityName, and ".json".
		// @brief     Create a stream using the filePath.
		// @brief     If (the stream is valid) AND (the stream Contains("Entity")),
		// @brief       Create a new instance of Entity.
		// @brief       Read the contents of the entity from the stream.
		// @brief       Add the new archetype entity to the archetypes container.
		// @brief   If the archetype existed previously or was created successfully,
		// @brief     Return a clone of the archetype entity.
		// @brief   Return nullptr.
		//
		// @param entityName = The name of the entity to be created.
		// 
		// @return Entity* = Pointer to the new _cloned_ entity, nullptr if unsuccessful.
		static Entity* Build(std::string_view entityName);

		// @brief Delete all entities in the archetypes container.
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
		// @brief A container of entity archetypes.
		static EntityContainer archetypes;

		// Private Variables:
	private:
	};

}	// namespace