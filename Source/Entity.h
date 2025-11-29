//------------------------------------------------------------------------------
//
// File Name:	Entity.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template class for a new object.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string>
#include <string_view>
#include <typeinfo>
#include <vector>

#include "Component.h"
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
	class Stream;

	// Typedefs:

	// Class Definition:
	class Entity : public Object
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Entity(void);

		// @brief Create a copy of a given entity.
		// @brief [NOTE: This copy-constructor must perform a deep copy of the attached components.]
		Entity(const Entity* other);

		// @brief Delete all attached components.
		~Entity(void) override;

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Initialize all attached components.
		// @brief [NOTE: Track the success of each component initialization.]
		// @brief [NOTE: Return false if any component failed to initialize successfully.]
		//
		// @return bool = true if all components were initialized successfully, otherwise false.
		bool Initialize() override;

		// @brief Update all attached components.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// @brief Render all attached components.
		// @brief [NOTE: Modern engines handle rendering in a more complicated way.]
		// @brief [NOTE: Some components require rendering only when debug drawing is enabled.]
		void Render() const override;

		// @brief Add a new component to the entity.
		// @brief Specific Steps:
		// @brief   Check for valid pointer (optional).
		// @brief   Add the new component to the components container.
		// @brief   Add this entity as a parent of the component.
		//
		// @param component = the new component to be added.
		void Add(Component* component);

		// @brief Get the requested component from the entity.
		//
		// @return T* = Pointer to the requested component, otherwise nullptr.
		template <typename T>
		T* Get() const
		{
			// Search through all of the attached components.
			for (auto component : components)
			{
				T* result = dynamic_cast<T*>(component);
				if (result != nullptr)
				{
					return result;
				}
			}
			return nullptr;
		}

		// @brief Get the name of the entity.
		//
		// @return string = The name of the entity.
		const std::string& Name() const { return name; }

		// @brief Set the name of the entity.
		//
		// @param newName = The new name to be assigned to the entity.
		void Name(std::string_view newName) { name = newName; }

		// @brief Mark the entity as destroyed; to be deleted after being updated.
		void Destroy() { isDestroyed = true; }

		// @brief Determine if the the entity has been marked as destroyed.
		//
		// @return bool = The current value in the isDestroyed variable.
		bool IsDestroyed() const { return isDestroyed; }

		// @brief Compare the name of the entity against a given name.
		//
		// @param compare = The name to be compared against the entity's name.
		//
		// @return bool = True if the names match, otherwise false.
		bool IsNamed(std::string_view compare) const { return name == compare; }

		// @brief Read the properties associated with an entity from the stream.
		// @brief Read the contents of an entity from the stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "Entity" object (PushNode).
		// @brief   Read the entity's name from the stream.
		// @brief   If the stream contains "Components",
		// @brief     Traverse down the tree to the "Components" array (PushNode).
		// @brief       If the stream contains "Transform",
		// @brief         Create a new instance of Transform.
		// @brief         Read the contents of the component from the stream.
		// @brief         Add the component to the entity.
		// @brief       Repeat the previous 4 steps with "Sprite".
		// @brief       Repeat the previous 4 steps with "Physics".
		// @brief     Return to the previous location in the tree (PopObject).
		// @brief   Return to the original location in the tree (PopObject).
		// 
		// @param stream = The stream used to read the data.
		void Read(Stream& stream);

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
		// @brief The name of the entity.
		// @brief [NOTE: This may or may not match the name of the associated archetype file.]
		std::string name;

		// @brief Marks the entity as destroyed; to be deleted after being updated.
		bool isDestroyed{ false };

		// @brief A container for any attached components.
		std::vector<Component*> components;
	};

}	// namespace