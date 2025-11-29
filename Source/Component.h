//------------------------------------------------------------------------------
//
// File Name:	Component.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Intermediate class for all components.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <dragon/platform_dependencies.h>

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
	class Entity;
	class Stream;

	// Typedefs:

	// Class Definition:
	class Component : public Object
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Component(void);

		// @brief Copy-constructor for the base component class.
		// @brief [NOTE: Set the parent pointer to nullptr.]
		Component(const Component* other);

		// @brief All systems need a virtual destructor to have their destructor called 
		virtual ~Component(void) override = 0;

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		virtual Component* Clone() const = 0;

		// @brief Initialize the component.
		// @brief [NOTE: Called when a new entity is initialized after creation.]
		// @brief [NOTE: Many components won't require this step; others might.]  
		//
		// @return bool = true if initialization successful, otherwise false.
		bool Initialize() override { return true; };

		// @brief Update the component each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override {};

		// @brief Render the component each frame.
		// @brief [NOTE: Modern engines handle rendering in a more complicated way.]
		// @brief [NOTE: Some components are rendered only when debug drawing is enabled.]
		void Render() const override {};

		// @brief Read the properties associated with a component from the stream.
		virtual void Read(Stream& stream) override = 0;

		// @brief Set the component's parent entity.
		//
		// @param parent = Pointer to the parent entity.
		ALWAYS_INLINE void Parent(Entity* parent) { this->parent = parent; }

		// @brief Get the component's parent entity.
		//
		// @return Entity* = Pointer to the parent entity.
		ALWAYS_INLINE Entity* Parent() const { return parent; }

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
		// @brief Pointer to the component's parent entity.
		Entity* parent{ nullptr };
	};

}	// namespace