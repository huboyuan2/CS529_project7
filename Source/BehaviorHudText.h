//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.h
// Author(s):	Boyuan Hu
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
	class BehaviorHudText : public Behavior
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		BehaviorHudText(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		BehaviorHudText(const BehaviorHudText* other);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Read the properties of a BehaviorHudText component from a stream.
		// @brief [NOTE: The base Behavior variables must be read using Behavior::Read().]
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		BehaviorHudText* Clone() const override { return new BehaviorHudText(this); }

		// Behavior Finite-State Machine (FSM) functions.
		void onInit() override;
		void onUpdate(float dt) override;
		void onExit() override;
		void UpdateText();
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
		unsigned scoreSystemId=0;
		unsigned displayValue=0;
		std::string labelString;
		std::string displayString;
	};

}	// namespace