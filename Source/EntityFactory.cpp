//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.cpp
// Author(s):	Boyuan HU
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template for a new .cpp file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "EntityFactory.h"
#include <string_view>
#include "Stream.h"
#include "Entity.h"

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
	EntityContainer EntityFactory::archetypes;
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

	EntityFactory::EntityFactory(void)
	{
	}

	//--------------------------------------------------------------------------

	/*EntityFactory::~EntityFactory(void)
	{
	}*/

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions
	void EntityFactory::DeleteAll()
	{
		archetypes.DeleteAll();
	}
#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

#pragma region Public Functions
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
	Entity* EntityFactory::Build(std::string_view entityName)
	{
		Entity* archetype = archetypes.FindByName(entityName);
		if (archetype != nullptr)
		{
			return new Entity(archetype);
		}
		else {
			std::string filePath = "./Data/Archetypes/" + std::string(entityName) + ".json";
			Stream stream(filePath);

			if (stream.IsValid() && stream.Contains("Entity"))
			{
				Entity* newEntity = new Entity();
				newEntity->Read(stream);
				archetypes.Add(newEntity);
				//hbytest
				return new Entity(newEntity);
			}
			return nullptr;
		}
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace