//------------------------------------------------------------------------------
//
// File Name:	Behavior.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This intermediate class drives the Finite-State Machine (FSM) for
//   all derived Behaviors.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Component.h"

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
	class Behavior : public Component
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	protected:
		Behavior(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		Behavior(const Behavior* other);

		~Behavior(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Update the behavior FSM each frame.
		// @brief Specific Steps:
		// @brief   If the state is changing,
		// @brief     Invoke the OnExit function.
		// @brief     Change the current state;
		// @brief     Invoke the OnInit function.
		// @brief   Invoke the OnUpdate function.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// @brief Read the properties of a Behavior component from a stream.
		// @brief [HINT: StateCurr, StateNext, Timer.]
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief Determine if the FSM should change states.
		//
		// @return bool = True if the state is changing, otherwise false.
		bool IsStateChanging() const { return stateCurr != stateNext; }

		// Behavior Finite-State Machine (FSM) function pointers.
		virtual void onInit() = 0;
		virtual void onUpdate(float dt) = 0;
		virtual void onExit() = 0;

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Protected Variables:
	protected:
		// @brief the current state of the behavior's FSM (default: -1 = invalid).
		int stateCurr{ -1 };

		// @brief the pending state of the behavior's FSM (default: -1 = invalid).
		int stateNext{ 0 };

		// @brief A general purpose timer useful for many basic behaviors.
		float timer{ 0.0f };

		// Private Variables:
	private:
	};

}	// namespace