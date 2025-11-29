//------------------------------------------------------------------------------
//
// File Name:	Scene.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Class for managing the entities within a scene.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string>

#include "EntityContainer.h"
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

	// Typedefs:
	class Entity;

	// Class Definition:
	class Scene : public Object
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Scene(const std::string& name);

		// All objects need a virtual destructor to have their destructor called 
		virtual ~Scene() override = 0;

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Provide a string name for debugging purposes.
		const std::string& Name() const { return name; }

		// @brief Load any large assets required by the scene.
		virtual void Load() = 0;

		// @brief Initialize the scene, including constructing the entities.
		//
		// @return bool = true if initialization successful, otherwise false.
		virtual bool Initialize() override = 0;

		// @brief Update the Object each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		virtual void Update(float dt) override = 0;

		// @brief Render the Object each frame.
		// @brief [NOTE: Modern engines handle rendering in a more complicated way.]
		// @brief [NOTE: Some Objects are rendered only when debug drawing is enabled.]
		virtual void Render() const override = 0;

		// @brief Shutdown the scene, destroying any remaining entities.
		virtual void Shutdown() = 0;

		// @brief Unload any large assets loaded for the scene.
		virtual void Unload() = 0;

		// @brief Read the properties associated with a scene from the stream.
		virtual void Read(Stream& stream) {};

		// @brief Restart the active scene.
		void Restart();

		// Methods for accessing the Entity container:

		// @brief Add an entity to the scene.
		// @brief [HINT: The container has a function for this.]
		// 
		// @param entity = Pointer to the entity to be added.
		void AddEntity(Entity* entity);

		// @brief Find an entity within the scene.
		// @brief [HINT: The container has a function for this.]
		//
		// @param findName = Name of the entity to be found.
		//
		// @return Entity* = Pointer to the first entity with a matching name, otherwise nullptr.
		Entity* FindEntity(std::string findName) const;

		// @brief Update all entities within the scene.
		void UpdateEntities(float dt) { entities.Update(dt); }

		// @brief Check for collisions between all entities with an attached Collider* (e.g. ColliderCircle) component.
		void CheckCollisions() { entities.CheckCollisions(); }

		// @brief Render all entities within the scene.
		void RenderEntities() const { entities.Render(); }

		// @brief Delete all entities within the scene.
		void DeleteEntities() { entities.DeleteAll(); }

		// Public Event Handlers
	public:
		// Windows message event handler.
		//virtual bool HandleMessage(const Message& message) = 0;

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// @brief The name of the scene, for debugging purposes.
		std::string name;

		// @brief A container of entities contained with the scene.
		EntityContainer entities;
	};

}	// namespace