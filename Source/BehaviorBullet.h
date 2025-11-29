//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This derived class is responsible for the behavior associated
//   with a "template" entity.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Behavior.h"

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
	class BehaviorBullet : public Behavior
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		BehaviorBullet(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		BehaviorBullet(const BehaviorBullet* other);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Read the properties of a BehaviorBullet component from a stream.
		// @brief [NOTE: The base Behavior variables must be read using Behavior::Read().]
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		BehaviorBullet* Clone() const override { return new BehaviorBullet(this); }

		// Behavior Finite-State Machine (FSM) functions.
		void onInit() override;
		void onUpdate(float dt) override;
		void onExit() override;
		static void CollisionHandler(Entity*, const Entity*);
		// Private Constants:
	private:
		typedef enum
		{
			cInvalid = -1,	// Default state for the behavior FSM.
			cIdle,			// Starting state for the behavior FSM.

		} States;

		// Private Static Variables:
	private:

		// Private Variables:
	private:
	};

}	// namespace