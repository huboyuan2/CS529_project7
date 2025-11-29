//------------------------------------------------------------------------------
//
// File Name:	Engine.h
// Author(s):	Doug Schilling (dschilling)
// Course:		CS529F25
// Project:		Project 0
// Purpose:		The core engine is a container of systems.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <vector>

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
	class System;

	// Typedefs:

	// Class Definition:
	class Engine : public Object
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Engine(void);

		// All Engines need a virtual destructor to have their destructor called 
		~Engine(void) override;

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Add a new system to the engine.
		// @brief (Note: Throw an assert if the function is passed a nullptr.)
		//
		//	 @param system = Pointer to the System to be added.
		void AddSystem(System* system);

		// @brief Initialize all systems managed by the engine.
		//
		//   @return bool Returns true if all systems were initialized successfully, otherwise false.
		virtual bool Initialize() override;

		// @brief Update all systems managed by the engine.
		//
		//	 @param dt = Delta time (in seconds) of the last frame.
		virtual void Update(float dt) override;

		// @brief Render all systems managed by the engine.
		virtual void Render() const override;

		// @brief Read the properties associated with the engine from the stream.
		void Read(Stream& stream) override {};

		// @brief Shutdown all systems managed by the engine.
		// @brief (NOTE: Delete the systems in reverse order to avoid possible dependency issues.)
		void Shutdown();

		// Public Event Handlers
	public:
		// Message event handler.
		//virtual bool HandleMessage(const Message& message) = 0;

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// Container of all systems managed by the engine.
		std::vector<System*> systems;
	};

}	// namespace