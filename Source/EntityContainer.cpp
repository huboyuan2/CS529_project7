//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.cpp
// Author(s):	Boyuan Hu
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
#include "EntityContainer.h"
#include "Entity.h"
#include "Collider.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"
#include <string_view>
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

	EntityContainer::EntityContainer(void)
	{
		entities.reserve(100);
	}

	//--------------------------------------------------------------------------

	/*EntityContainer::~EntityContainer(void)
	{
	}*/

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
			// @brief Update all entities in the container.
		// @brief [ADDITIONAL REQUIREMENT: After an entity has been updated,
		// @brief   if it is marked as "destroyed", then it must be removed
		// @brief   from the container and deleted.]
		//
		// @param dt = Delta time (in seconds) of the last frame.
	void EntityContainer::Update(float dt)
	{
		for (Entity* entity : entities)
		{
			entity->Update(dt);
		}
		entities.erase(
			std::remove_if(entities.begin(), entities.end(),
				[](Entity* entity) {
					if (entity->IsDestroyed())
					{
						delete entity;
						return true;
					}
					return false;
				}),
			entities.end()
		);
	}
	// @brief Add a new entity to the container.
		// @brief Specific Steps:
		// @brief   Initialize the entity.
		// @brief   Add the entity to the container.
		//
		// @param entity = The entity to be added to the container.
	void EntityContainer::Add(Entity* entity)
	{	
		entity->Initialize();
		entities.push_back(entity);
	}
	// @brief Render all entities in the container.
	void EntityContainer::Render() const
	{
		for (const auto& entity : entities)
		{
			entity->Render();
		}
	}
	// @brief Check for collisions between all entities with an attached collider component.
		// @brief Recommended Steps (High-Level):
		// @brief    Search through the container, looking for any entities that have an attached Collider* component.
		// @brief    When an entity with a collider component is found,
		// @brief      Search through the remainder of the container, again looking for Collider* components.
		// @brief      For each unique pair of entities with attached colliders,
		// @brief        Call the function, ColliderCheck, passing pointers to the two colliders.
	void EntityContainer::CheckCollisions() const
	{
		std::vector<int> colliderlist;
		for (int i = 0; i < entities.size(); i++)
		{
			Collider* collid = entities[i]->Get<Collider>();
			if (collid)
			{
				colliderlist.push_back(i);
			}
		}
		for (int i = 0; i < colliderlist.size(); i++)
		{
			for (int j = i + 1; j < colliderlist.size(); j++)
			{
				Collider* collider1 = entities[colliderlist[i]]->Get<Collider>();
				Collider* collider2 = entities[colliderlist[j]]->Get<Collider>();
				if (collider1 && collider2)
				{
					const ColliderLine* line2= dynamic_cast<const ColliderLine*>(collider2);
					if (line2)
					{
						collider2->CheckCollision(collider1);
					}
					collider1->CheckCollision(collider2);
				}
			}
		}
	}



	// @brief Find an entity in the container that has a matching name.
	// @brief [NOTE: This function returns only the first matching entity.]
	//
	// @param findName = The name of the entity being sought.
	//
	// @return Entity* = Pointer to the first entity with a matching name.
	Entity* EntityContainer::FindByName(std::string_view findName) const
	{
		for (const auto& entity : entities)
		{
			if (entity->Name() == findName)
			{
				return entity;
			}
		}
		return nullptr;
	}

	// @brief Delete all entities in the container.
	void EntityContainer::DeleteAll()
	{
		/*for (const auto& entity : entities)
		{
			entity->Destroy();
		}*/
		//hbytest
		for (const auto& entity : entities)
		{
			if(entity!=nullptr)
			delete entity;
		}
		entities.clear();
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace