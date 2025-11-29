//------------------------------------------------------------------------------
//
// File Name:	StubScene.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 0
// Purpose:		Template class for a new scene.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Scene.h"

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

	// Class Definition:
	class StubScene : public Scene
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		StubScene(void);

		// All objects need a virtual destructor to have their destructor called 
		~StubScene(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:

		// Public Event Handlers
	public:
		// Windows message event handler.
		//virtual bool HandleMessage(const Message& message) = 0;

		// Private Functions:
	private:
		// @brief Load any large assets required by the scene.
		void Load();

		// Initialize the scene, including constructing the entities.
		//
		// @return bool = true if initialization successful, otherwise false.
		bool Initialize() override;

		// @brief Update the scene each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// @brief Render the scene each frame.
		void Render() const override;

		// @brief Shutdown the scene, destroying any remaining entities.
		void Shutdown() override;

		// @brief Unload any large assets loaded for the scene.
		void Unload() override;

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
	};

}	// namespace