//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This container is responsible for managing entities.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string_view>
#include <vector>

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
	class EntityContainer
	{
		// Public Constants and Enums:
	public:
		EntityContainer();

		// Constructors/Destructors:
	public:

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Update all entities in the container.
		// @brief [ADDITIONAL REQUIREMENT: After an entity has been updated,
		// @brief   if it is marked as "destroyed", then it must be removed
		// @brief   from the container and deleted.]
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt);

		// @brief Render all entities in the container.
		void Render() const;

		// @brief Add a new entity to the container.
		// @brief Specific Steps:
		// @brief   Initialize the entity.
		// @brief   Add the entity to the container.
		//
		// @param entity = The entity to be added to the container.
		void Add(Entity* entity);

		// @brief Find an entity in the container that has a matching name.
		// @brief [NOTE: This function returns only the first matching entity.]
		//
		// @param findName = The name of the entity being sought.
		//
		// @return Entity* = Pointer to the first entity with a matching name.
		Entity* FindByName(std::string_view findName) const;

		// @brief Check for collisions between all entities with an attached collider component.
		// @brief Recommended Steps (High-Level):
		// @brief    Search through the container, looking for any entities that have an attached Collider* component.
		// @brief    When an entity with a collider component is found,
		// @brief      Search through the remainder of the container, again looking for Collider* components.
		// @brief      For each unique pair of entities with attached colliders,
		// @brief        Call the function, ColliderCheck, passing pointers to the two colliders.
		void CheckCollisions() const;

		// @brief Delete all entities in the container.
		void DeleteAll();

		// @brief Determines if the entity container is empty.
		// @brief [NOTE: This function has been added for testing purposes.]
		bool IsEmpty() const { return (entities.size() == 0); }

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		std::vector<Entity*> entities;
	};

}	// namespace