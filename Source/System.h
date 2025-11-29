//------------------------------------------------------------------------------
//
// File Name:	System.h
// Author(s):	Doug Schilling (dschilling)
// Course:		CS529F25
// Project:		Project 0
// Purpose:		Base interface class for all engine systems.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string>

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
	class System : public Object
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		System(const std::string& name);

		// All systems need a virtual destructor to have their destructor called 
		virtual ~System(void) override = 0;

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Provide a string name for debugging purposes.
		//
		// @return string = The name of the system.
		const std::string& Name() const { return name; }

		// @brief Initialize the system.
		virtual bool Initialize() override { return true; };

		// @brief Update the system each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		virtual void Update(float dt) override {};

		// @brief Render the system each frame.
		virtual void Render() const override {};

		// @brief Read the properties associated with a system from the stream.
		virtual void Read(Stream& stream) {};

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
		// The name of the system, for debugging purposes.
		std::string name;
	};

}	// namespace