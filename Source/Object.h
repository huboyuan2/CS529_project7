//------------------------------------------------------------------------------
//
// File Name:	Object.h
// Author(s):	Doug Schilling (dschilling)
// Course:		CS529F25
// Project:		Project 0
// Purpose:		Interface class for all objects used in the engine (Systems, Scenes, Entities, etc.).
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

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
	class Object
	{
		// Public Constants and Enums:
	public:

		// Private Constants and Enums:
	private:

		// Constructors/Destructors:
	public:
		Object(void);

		Object(const Object* other) {}

		// All objects must provide their own virtual destructor. 
		virtual ~Object() = 0;

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Initialize the object.
		//
		// @return bool True if the initialization was successful, otherwise False.
		virtual bool Initialize() = 0;

		// @brief Update the object each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		virtual void Update(float dt) = 0;

		// @brief Render the object each frame.
		virtual void Render() const = 0;

		// @brief Read the properties associated with an object from the stream.
		virtual void Read(Stream& stream) = 0;

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Private Static Variables:
	private:

		// Protected Variables:
	protected:

		// Private Variables:
	private:
	};

}	// namespace
