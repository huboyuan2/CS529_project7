//------------------------------------------------------------------------------
//
// File Name:	Behavior.cpp
// Author(s):	Boyuan Hu
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
#include "Behavior.h"
#include "Stream.h"
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

	Behavior::Behavior(void)
	{
	}

	//--------------------------------------------------------------------------

	/*Behavior::~Behavior(void)
	{
	}*/

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
		// @brief Update the behavior FSM each frame.
		// @brief Specific Steps:
		// @brief   If the state is changing,
		// @brief     Invoke the OnExit function.
		// @brief     Change the current state;
		// @brief     Invoke the OnInit function.
		// @brief   Invoke the OnUpdate function.
		// @param dt = Delta time (in seconds) of the last frame.
	void Behavior::Update(float dt)
	{
		if(IsStateChanging())
		{
			onExit();
			stateCurr = stateNext;
			onInit();
		}
		onUpdate(dt);
	}

	// @brief Read the properties of a Behavior component from a stream.
	// @brief [HINT: StateCurr, StateNext, Timer.]
	//
	// @param stream = The data stream used for reading.
	void Behavior::Read(Stream& stream)
	{
		if (!stream.IsValid())
		{
			return;
		}
		stream.PushNode("Behavior");
		// Read the velocity value from the stream.
		stream.Read("StateCurr", stateCurr);

		// Read the acceleration value from the stream.
		stream.Read("StateNext",stateNext);
		stream.Read("Timer", timer);
		// Return to the previous location in the tree.
		stream.PopNode();
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace