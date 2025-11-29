//------------------------------------------------------------------------------
//
// File Name:	Scene.cpp
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 0
// Purpose:		Class for managing the entities within a scene.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <string>

#include "Scene.h"
#include "SceneSystem.h"
#include "Object.h"

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

	Scene::Scene(const std::string& name)
		: Object()
		, name(name)
	{
	}

	//--------------------------------------------------------------------------

	Scene::~Scene(void)
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

	void Scene::Restart()
	{
		SceneSystem::Restart();
	}

	// Methods for accessing the Entity container:

// @brief Add an entity to the scene.
// @brief [HINT: The container has a function for this.]
// 
// @param entity = Pointer to the entity to be added.
	void Scene::AddEntity(Entity* entity)
	{
		entities.Add(entity);
	}

	// @brief Find an entity within the scene.
	// @brief [HINT: The container has a function for this.]
	//
	// @param findName = Name of the entity to be found.
	//
	// @return Entity* = Pointer to the first entity with a matching name, otherwise nullptr.
	Entity* Scene::FindEntity(std::string findName) const
	{
		return entities.FindByName(findName);
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace