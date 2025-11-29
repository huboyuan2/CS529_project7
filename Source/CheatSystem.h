//------------------------------------------------------------------------------
//
// File Name:	CheatSystem.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 3
// Purpose:		This system is responsible for switching scenes when specific keys are pressed.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <typeinfo>

#include "System.h"

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
	class CheatSystem : public System
	{
		// Public Constants and Enums:
	public:

		// Private Structure Definitions:
	private:

		// Constructors/Destructors:
	public:
		CheatSystem(void);

		// All systems need a virtual destructor to have their destructor called 
		~CheatSystem(void) override;

		// Public Static Functions:
	public:

		// Public Functions:
	public:

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief Update the system each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// Private Static Constants:
	private:

		// Private Static Variables:
	private:
		static CheatSystem* instance;

		// Private Variables:
	private:
	};

}	// namespace