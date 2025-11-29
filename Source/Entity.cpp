//------------------------------------------------------------------------------
//
// File Name:	Entity.cpp
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
#include "Entity.h"
#include <string>
#include <typeinfo>
#include <vector>
#include "stream.h"
#include "Component.h"
#include "Object.h"
#include "Sprite.h"
#include "Transform.h"
#include "Physics.h"
#include "Animation.h"
#include "ObjectFactory.h"
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

	Entity::Entity(void)
	{
	}

	//--------------------------------------------------------------------------
	Entity::Entity(const Entity* other)
	{
		name = other->name;
		for (auto component : components)
		{
			delete component;
		}
		components.clear();
		for (auto component : other->components)
		{
			Add(component->Clone());
		}
	}


	Entity::~Entity(void)
	{
		for (auto component : components)
		{
			delete component;
		}
		components.clear();
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
			// @brief Initialize all attached components.
		// @brief [NOTE: Track the success of each component initialization.]
		// @brief [NOTE: Return false if any component failed to initialize successfully.]
		//
		// @return bool = true if all components were initialized successfully, otherwise false.
	bool Entity::Initialize()
	{
		for (auto component : components)
		{
			if (!component->Initialize())
			{
				return false;
			}
		}
		return true;
	}

	// @brief Update all attached components.
	//
	// @param dt = Delta time (in seconds) of the last frame.
	void Entity::Update(float dt)
	{
		for (auto component : components)
		{
			component->Update(dt);
		}
		//if (IsDestroyed())
		//{
		//	// Handle destruction logic here
		//	this->~Entity();
		//}
	}

	// @brief Render all attached components.
	// @brief [NOTE: Modern engines handle rendering in a more complicated way.]
	// @brief [NOTE: Some components require rendering only when debug drawing is enabled.]
	void Entity::Render() const
	{
		for (auto component : components)
		{
			component->Render();
		}
	}

	// @brief Add a new component to the entity.
	// @brief Specific Steps:
	// @brief   Check for valid pointer (optional).
	// @brief   Add the new component to the components container.
	// @brief   Add this entity as a parent of the component.
	//
	// @param component = the new component to be added.
	void  Entity::Add(Component* component)
	{
		if (component == nullptr)
		{
			LoggingSystem::Error("Entity::Add: Attempted to add a null component.");
			return;
		}
		components.push_back(component);
		component->Parent(this);
	}

	// @brief Get the requested component from the entity.
	//
	// @return T* = Pointer to the requested component, otherwise nullptr.
	//template <typename T>
	//T* Get()
	//{
	//	// Search through all of the attached components.
	//	for (auto component : components)
	//	{
	//		// If the current component's type matches the desired type,
	//		if (typeid(*component) == typeid(T))
	//		{
	//			// Return the matching component.
	//			return static_cast<T*>(component);
	//		}
	//	}
	//	return nullptr;
	//}

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
	void Entity::Read(Stream& stream)
	{
		
		if (!stream.IsValid())
			return;
			
		stream.PushNode("Entity");
		stream.Read("Name", this->name);

			
			auto tryLoadComponent = [this, &stream](const std::string& componentName)
			{
					if (stream.Contains(componentName))
					{
						ObjectFactory& factory = ObjectFactory::GetInstance();
						Component* component = dynamic_cast<Component*>(factory.Create(componentName));
						if (component)
						{
							component->Read(stream);
							Add(component);
						}
						else
						{
							LoggingSystem::Debug("Entity::Read: Failed to create component: {}", componentName);
						}
					}
			};
			stream.ReadObject("Components", tryLoadComponent);
		
		stream.PopNode();
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace